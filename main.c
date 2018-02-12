#include "data_analyse.h"
#include "mysocket.h"

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<errno.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 



int end_flag ;


int main(int argc, char** argv) 
{ 

    pthread_t id_1;
    int ret;
    int sfd;

    char *senddata = NULL;
    senddata = (char *)malloc(BUF_SIZE);
    strcpy(senddata,"/about");
    senddata[strlen(senddata)] = 0x0a;
    senddata[strlen(senddata)+1] = 0x0;

    sfd = voip_client_init();

    end_flag = 1;

    ret=pthread_create(&id_1,NULL,(void  *) voip_client_read,NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
        return -1;  
    }  
    while(1)
    {   
        voip_client_send_from_stdin();
    } 

    end_flag = 0; 
    pthread_join(id_1,NULL); 
    close(sfd); 
    return 0;
}






