#include<stdio.h>
#include<obliv.oh>
#include<obliv.h>

#include"../common/util.h"  

//引用了该文件中的TCP连接函数ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);

#include"test1.h"

const char* mySide(int currentParty){
    if(currentParty==1) return "Generator";
    else return "Evaluator";

}

int get_common(void* args)

{
    protocolIO *io=args;
    obliv char a[MAXN],b[MAXN];//这里注意不能用指针，未定义的指针会导致内存错误
    obliv int size_a,size_b;
    size_a = feedOblivInt(io->size,1);
    size_b = feedOblivInt(io->size,2);
    feedOblivCharArray(a,io->s,MAXN,1);
    feedOblivCharArray(b,io->s,MAXN,2);
    int n=0;//共同的字符个数
    for(int i=0;i<MAXN;i++){
        obliv if(i<size_a){
            for(int j=0;j<MAXN;j++){
                obliv if(j<size_b){
                    ~obliv(_c){
                        bool d;
                        revealOblivBool(&d,a[i]==b[j],0);
                        if(d){revealOblivChar(&io->l[n],a[i],0);n++;
                        }
                    }//该无条件执行块是为了修改n,因为n为外部定义的数据，在obliv块中被frozon，不能修改
                }
            }

        }

    }

}

int main(int argc,char *argv[]){
    ProtocolDesc pd;
    protocolIO io;
    if(argc<4){
        fprintf(stderr,"%d: static missing\n",argv[1][0]=='1'?1:2);
        return 1;
    }
    // skip input sanitization
    const char* remote_host = (strcmp(argv[2],"--")?argv[2]:NULL);
    io.size=strlen(argv[3]);//输入数据
    if(io.size>MAXN){ 
        fprintf(stderr,"string too big\n");
        return 1;
    }
    io.s=argv[3];
    //sscanf(argv[3],"%s",&io.s);
    for(int i=io.size;i<MAXN;i++)
    io.s[i]=remote_host?'#':'$';
    //protocolUseStdio(&pd);

    ocTestUtilTcpOrDie(&pd,remote_host,argv[1]);//tcp连接

    int currentParty = (remote_host?2:1);

    setCurrentParty(&pd,currentParty);
    
    execYaoProtocol(&pd,get_common,&io);//加密电路协议的执行
    
    cleanupProtocol(&pd);

    fprintf(stderr,"\n%s ",mySide(currentParty));

    fprintf(stderr," Common: %s\n",io.l);

return 0;

}
