#pragma once
#define MAXN 20
typedef struct protocolIO{
    char* s;//输入
    int size;//输入的大小
    char l[MAXN];//输出

} protocolIO;


int get_common(void* args);//功能函数

const char* mySide();//返回边名称，即是哪一方
