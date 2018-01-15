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
int main(int argc, char** argv) 
{ 
    int sockfd, num; 
    char recvline[BUF_SIZE], sendline[BUF_SIZE];
    struct sockaddr_in servaddr;
    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
    { 
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno); 
        exit(0);  
    } 
    memset(&servaddr, 0, sizeof(servaddr)); 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(BARESIP_PORT); 
    if( inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr) <= 0 )
    { 
        printf("inet_pton error for %s\n",argv[1]); 
        exit(0);  
    } 
    if( connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0 )
    { 
        printf("connect error: %s(errno: %d)\n",strerror(errno),errno); 
        exit(0);  
    } 
    while(1){   
        printf("send msg to server: \n"); 
        fgets(sendline, BUF_SIZE, stdin); 
        if( send(sockfd, sendline, strlen(sendline), 0) < 0 ) 
        {
            printf("send msg error: %s(errno: %d)\n", strerror(errno), errno); 
            exit(0);  
        }

        if ((num = recv(sockfd, recvline, BUF_SIZE, 0))<0)  
        {  
            perror("recv error!");  
            exit(1);  
        }  
        else if (num>0)  
        {  
            printf("%s", recvline);  
            memset(recvline, 0, BUF_SIZE);  
        }  

    }  

    close(sockfd); 
    return 0;
}





