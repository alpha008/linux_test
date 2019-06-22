void TestLib()
{
	printf("hello world\n");
	mainfunc();
    stafunc();
    dyfunc();
#ifdef _MACRO
	printf("macro test\n");
#endif

#ifdef _ZJX
	printf("ZJX test\n");
#endif
}