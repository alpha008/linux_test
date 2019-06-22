DIR=./source
STALIB=../staticlib
DYNAMICLIB=../dynamic
BIN=app
SHARE=
CFLAGE=-Wall -c -std=c++11 
INCLUDE=-I./include \
	-I../staticlib/include\
	-I../dynamic/include
LFLAG=-L../staticlib/libstatic\
	   -L../dynamic/libdynamic
LIBS=-lstatic_test -ldynamictest
CC=g++
AR=ar -cr
CO=$(AR)

SRC=$(wildcard $(DIR)/*.cpp)
OBJ=$(patsubst %.cpp,%.o,$(SRC))

all:$(BIN)
$(BIN):$(OBJ)
	$(CC) $^ -o $@ $(LFLAG) $(LIBS)
	rm -rf ./source/*.o
$(DIR)/%.o:$(DIR)/%.cpp
	make -C $(STALIB)
	make -C $(DYNAMICLIB)
	$(CC) -c $(INCLUDE) $(CFLAGE) $<  -o  $@
.PHONY:clean
clean:
	rm $(OBJ)
	rm -rf ../dynamic/libdynamic
	rm -rf ../staticlib/libstatic
