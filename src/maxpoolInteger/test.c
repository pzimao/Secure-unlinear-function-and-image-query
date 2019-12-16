#include<stdio.h>
#include<malloc.h>
#include <time.h>
#define ALLOC 128 


int main(){
    
    srand((unsigned int)time(NULL));
    int num=10000;
    char * src_x="/home/liufei/documents/2019/obliv-c-obliv-c/test/oblivc/maxpoolInteger/x.dat";
    char * src_y="/home/liufei/documents/2019/obliv-c-obliv-c/test/oblivc/maxpoolInteger/y.dat";
    FILE * fp1=fopen(src_x,"wb");
    FILE * fp2=fopen(src_y,"wb");
    for(int i=0;i<num;i++){
        int a=rand()%100;
        int b=rand()%100;
        fprintf(fp1,"%d ",a);
        fprintf(fp2,"%d ",b);
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}
