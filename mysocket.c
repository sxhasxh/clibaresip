#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<errno.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include "mysocket.h"


char recvline[BUF_SIZE],sendline[BUF_SIZE];
int sockfd;


int voip_client_init()
{
    struct sockaddr_in servaddr;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    { 
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno); 
    } 
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(BARESIP_PORT); 
    if( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0 )
    { 
        printf("inet_pton error \n"); 
    } 
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
    { 
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno); 
        exit(0);  
    } 
    return sockfd;

}


int voip_client_send(const char *str)
{
    if( send(sockfd, str, strlen(str), 0) < 0 ) 
    {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno); 
    }
}

int voip_client_send_from_stdin()
{
    fgets(sendline, BUF_SIZE, stdin); 
    if( send(sockfd, sendline, strlen(sendline), 0) < 0 ) 
    {
        printf("send msg error: %s(errno: %d)\n", strerror(errno), errno); 
    }
}


void voip_client_recv()
{  
    int  num; 
    while(1)
    {
        if ((num = recv(sockfd, recvline, BUF_SIZE, 0))<0)  
        {  
            perror("recv error!");  
        }  
        else if (num>0)  
        {  
            printf("%s", recvline);  
            data_analyse(recvline);
            memset(recvline, 0, BUF_SIZE);  
        }  
    }
}
