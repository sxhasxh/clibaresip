/*************************************************************************
  > File Name: a_client.c
  > Author: 
  > Mail: 
  > Created Time: 2017年12月25日 星期一 17时24分23秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<errno.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#define MAXLINE 4096 
#define BARESIP_PORT 5555 
#define BUF_SIZE 4096

int voip_client_send(const char *str);
void voip_client_recv();
int voip_client_init();

int sockfd;
char recvline[BUF_SIZE];

int main(int argc, char** argv) 
{ 

    pthread_t id_1;
    int ret;

    char *senddata = NULL;
    senddata = (char *)malloc(BUF_SIZE);
    strcpy(senddata,"/about");
    senddata[strlen(senddata)] = 0x0a;
    senddata[strlen(senddata)+1] = 0x0;

    voip_client_init();

    ret=pthread_create(&id_1,NULL,(void  *) voip_client_recv,NULL);  
    if(ret!=0)  
    {  
        printf("Create pthread error!\n");  
        return -1;  
    }  
    while(1)
    {   
        voip_client_send(senddata);
        sleep(3);
    }  
    pthread_join(id_1,NULL); 
    close(sockfd); 
    return 0;
}
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


}
int voip_client_send(const char *str)
{
    if( send(sockfd, str, strlen(str), 0) < 0 ) 
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
            memset(recvline, 0, BUF_SIZE);  
        }  
    }
}




