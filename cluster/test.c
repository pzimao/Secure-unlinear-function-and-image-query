#include<stdio.h>
#include<malloc.h>
#define ALLOC 128 


int main(){
    char * src="x.txt";
    //test(src);
    FILE * fp=fopen(src, "r");
    if(fp==NULL){
        printf("open error !\r\n");
    }
    float * data=malloc(sizeof(float)*3);
    double a=0;
    int n=0;
    while(!feof(fp)){
        int num=fscanf(fp,"%lf",&a);
        //当fscanf读不到有效字符会返回-1,也就是EOF
        if(num==1){
            *(data+n)=a;
            n++;    
        }
        printf("%d",num);
       
    }
    printf("%d\r\n",n);
    fclose(fp);

    for(int i=0;i<n;i++){
        printf("%f\r\n",data[i]);
    }

    return 0;
}