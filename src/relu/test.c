#include<stdio.h>
#include<malloc.h>
#include <time.h>
#define ALLOC 128 


int main(){
    
    srand((unsigned int)time(NULL));
    int num=100;
    char * src_x="/home/liufei/documents/2019/obliv-c-obliv-c/test/oblivc/relu/x.dat";
    char * src_y="/home/liufei/documents/2019/obliv-c-obliv-c/test/oblivc/relu/y.dat";
    FILE * fp1=fopen(src_x,"wb");
    FILE * fp2=fopen(src_y,"wb");
    for(int i=0;i<num;i++){
        double a=(double)(rand()%100);
        double b=(double)(rand()%100);
        fprintf(fp1,"%f ",a);
        fprintf(fp2,"%f ",b);
    }
    fclose(fp1);
    fclose(fp2);

    return 0;
}
