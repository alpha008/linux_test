#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

typedef struct client_data {
    int fd;
    time_t tt;
    char buf[512];
    void* data;
}client_data;
typedef struct tw_timer {
    //处于时间轮第几转，即时间轮转多少转
    //此定时器可以处于当前转，若再加上槽
    //即可确定此定时器所处时间轮位置
    int rotation;

    //处于当前时间轮转的第几个槽
    int slot;

    //定时器到时执行的回调函数
    void* (*cb_func)( void* param );

    //用户数据，触发回调任务函数的参数
    struct client_data c_data;

    //这里只需要单向不循环链表即可
    //struct tw_timer* prev;
    struct tw_timer* next;
}tw_timer;
typedef struct timer_manager {
    //时间轮当前槽，每经过一个间隔时间，加一实现轮转动，
    //超过总槽数即归零表示当前轮转完
    int cur_slot;

    //时间轮一转的总槽数，总槽数越大槽链表越短，效率越高
    int slot_num_r;

    //相邻时间槽间隔时间，即时间轮转到下一个槽需要时间，
    //间隔时间越短，精度越高，例如10s，表示定时器支持10s
    //间隔定时器添加，最小支持1s
    int slot_interval;

    //每个时间槽链表头结点，即一个槽管理一条链表，链表
    //添加相同槽数的结点，但转数可能不同
    struct tw_timer* slots_head[512];
}timer_manager;

timer_manager tmanager;

void* ontime_func( void* param )
{
    client_data* data = (client_data*)param;
    time_t tt = time(NULL);
    printf("\n----------------------------------------------------\n");
    printf("\tontime,interval:%d\n", (int)(tt - data->tt));
    printf("\told time:%s", ctime(&data->tt));
    printf("\t%s", data->buf);
    printf("\tcur time:%s", ctime(&tt));
    //getchar();
    printf("----------------------------------------------------\n");

    return NULL;
}
int add_timer( timer_manager* tmanager,
    int timeout, client_data* c_data )
{
    if ( timeout < 0 || !tmanager )
        return -1;

    int tick = 0;           //转动几个槽触发
    int rotation = 0;       //处于时间轮第几转
    int slot = 0;           //距离当前槽相差几个槽

    if ( timeout < tmanager->slot_interval )
        tick = 0;
    else
        tick = timeout / tmanager->slot_interval;

    rotation = tick / tmanager->slot_num_r;
    slot = ( tmanager->cur_slot + tick % tmanager->slot_num_r )
                % tmanager->slot_num_r - 1;

    printf("addtimer-->timeout:%d, rotation:%d,slot:%d\n",
        timeout, rotation, slot);

    tw_timer* tmp_t = (tw_timer*)malloc(sizeof(tw_timer));
    tmp_t->rotation = rotation;

    char buf[100] = {0};
    time_t tt = time(NULL) + timeout;

    sprintf( buf, "set time:%s", ctime(&tt));
    memset( tmp_t->c_data.buf, 0, sizeof(tmp_t->c_data.buf));
    strcpy( tmp_t->c_data.buf, buf );
    tmp_t->slot = slot;
    tmp_t->c_data.tt = time(NULL);
    tmp_t->cb_func = ontime_func;

    if ( !tmanager->slots_head[slot] )
    {
        tmanager->slots_head[slot] = tmp_t;
        tmp_t->next = NULL;
        //printf("[line]:%d\n", __LINE__);
        return 0;
    }
    //printf("[line]:%d\n", __LINE__);
    tmp_t->next = tmanager->slots_head[slot]->next;
    tmanager->slots_head[slot]->next = tmp_t;

    return 0;
}
int del_all_timer( timer_manager* tmanager )
{
    //清除、释放所有定时器，懒得写了
}
int tick( timer_manager* tmanager )
{
    if ( !tmanager )
        return -1;

    tw_timer* tmp = tmanager->slots_head[tmanager->cur_slot];
    tw_timer* p_tmp;

    while ( tmp )
    {
        //rotation减一，当前时间轮转不起作用
        //假设这个tmp指向第0个槽的头，链中某个结点的rotaion为下一圈，
        //即rotation=1，所以这个定时器不起作用，而因为cur_slot不断
        //走动，tmp在当前转不可能再指向这个定时器，下一圈cur_slot
        //为0时能继续判断这个定时器，故实现了定时器处于不同转的判断
        if ( tmp->rotation > 0 )
        {
            tmp->rotation--;
            p_tmp = tmp;
            tmp = tmp->next;
        }
        else
        {
            //否则定时器到时，触发回调函数
            tmp->cb_func( &tmp->c_data );

            //删除此定时器结点
            //吃了没用双向链表的亏，写这么low
            if ( tmp == tmanager->slots_head[tmanager->cur_slot] )
            {
                //printf("[line]:%d\n", __LINE__);
                tmanager->slots_head[tmanager->cur_slot] = tmp->next;
                p_tmp = tmp;
                tmp = tmp->next;
                free( p_tmp );
                p_tmp = NULL;
                p_tmp = tmp;
                //printf("[line]:%d\n", __LINE__);
            }
            else
            {
                p_tmp->next = p_tmp->next->next;
                free( tmp );
                tmp = NULL;
                tmp = p_tmp->next;
            }
        }
    }
    //更新时间轮，转动一个槽，转一圈又从开始转
    tmanager->cur_slot = ++tmanager->cur_slot % tmanager->slot_num_r;

    return 0;
}
int init_t_manager( timer_manager* tmanager,
    int slot_num_r, int slot_interval )
{
    tmanager->cur_slot = 0;
    tmanager->slot_num_r = slot_num_r;
    tmanager->slot_interval = slot_interval;

    return 0;
}
//自己试着写的调用层代码
void alarm_handler( int sig )
{
    time_t tt = time(NULL);
    //printf("timer tick:%s", ctime(&tt));

    int ret = tick( &tmanager );
    if ( ret < 0 )
        printf("tick error\n");

    alarm( tmanager.slot_interval );
}
int main()
{
    time_t tt = time(NULL);

    signal( SIGALRM, alarm_handler );

    //init_t_manager( &tmanager, 60, 10 );
    init_t_manager( &tmanager, 60, 1 );

    add_timer( &tmanager, 6, NULL );
    add_timer( &tmanager, 11, NULL );
    add_timer( &tmanager, 22, NULL );
    add_timer( &tmanager, 33, NULL );
    add_timer( &tmanager, 44, NULL );
    add_timer( &tmanager, 55, NULL );
    add_timer( &tmanager, 66, NULL );
    add_timer( &tmanager, 77, NULL );
    add_timer( &tmanager, 88, NULL );
    add_timer( &tmanager, 99, NULL );
    add_timer( &tmanager, 111, NULL );
    add_timer( &tmanager, 122, NULL );
    add_timer( &tmanager, 133, NULL );
    add_timer( &tmanager, 144, NULL );

    printf("start time:%s\n", ctime(&tt));
    alarm( tmanager.slot_interval );

    while ( 1 )
        sleep( 5 );

    return 0;
}
