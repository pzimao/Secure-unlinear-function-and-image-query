#include <stdio.h>
#include <stdlib.h>
#include <obliv.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "../common/util.h"
#include "dbg.h"
#include <unistd.h>
#include "BN.h"


void check_mem(float* x, float* y, int party) 
{
    if (party == 1) {
        if (x == NULL) {
            log_err("Memory allocation failed\n");
            clean_errno();
            exit(1);
        }
    }
    if (party == 2) {
        if (y == NULL) {
            log_err("Memory allocation failed\n");
            clean_errno();
            exit(1);
        }
    }
}

int main(int argc, char *argv[]) 
{   
    float a=12.0;
    printf("%s",a);
    printf("BN\n");
    printf("=================\n\n");
    // Check args
    if (argc == 4) {
        // Initialize protocols and obtain connection information
        const char *remote_host = strtok(argv[1], ":");//分割字符串
        const char *port = strtok(NULL, ":");
        ProtocolDesc pd;
        protocolIO io;
        // Make connection between two shells
        // Modified ocTestUtilTcpOrDie() function from obliv-c/test/oblivc/common/util.c
        log_info("Connecting to %s on port %s ...\n", remote_host, port);
        if(argv[2][0] == '1') {
            if(protocolAcceptTcp2P(&pd,port)!=0) {
                log_err("TCP accept from %s failed\n", remote_host);
                exit(1);
            }
        } else {
            if(protocolConnectTcp2P(&pd,remote_host,port)!=0) {
                log_err("TCP connect to %s failed\n", remote_host);
                exit(1);
            }
        }

        // Final initializations before entering protocol
        cp = (argv[2][0]=='1'? 1 : 2);
        setCurrentParty(&pd, cp); // only checks for a '1'
        io.src = argv[3]; // filename
        //lap = wallClock();

        // Execute Yao's protocol and cleanup
        //execYaoProtocol(&pd, linReg, &io);
       
        execYaoProtocol(&pd,BN_layer, &io);
        cleanupProtocol(&pd);
        double runtime = wallClock() - lap; // stop clock here 
        sleep(200);
        // Print results and gate count
        //Slog_info("Total time: %lf seconds\n", runtime);
        // log_info("Yao Gate Count: %u\n", yaoGateCount());
    } else {
        log_info("Usage: %s <hostname:port> <1|2> <filename>\n" 
                 "\tHostname usage:\n" 
                 "\tlocal -> 'localhost' remote -> IP address or DNS name\n", argv[0]);
    }
    return 0;
}


//动态分配二维数组
void load_dataU(protocolIO *io, float** x, float** y, int party) 
{
    //test(src);
    FILE * fp=fopen(io->src, "r");
    if(fp==NULL){
        printf("open error !\r\n");
        exit(1);
    }
    double a=0;
    io->n = 0;
    while(!feof(fp)){
        int num=fscanf(fp,"%lf",&a);
        //当fscanf读不到有效字符会返回-1,也就是EOF
        float a_float = (float) a;
        
        if(num==1){

            if(party==1){
                //printf("x[%d]:%f",io->n,a_float);
                *(*x+io->n)=a_float;
                
            }else{
                //printf("y[%d]:%f",io->n,a_float);
                *(*y+io->n)=a_float;
            }
           io->n++;     
        }
       
    }
    fclose(fp);
}