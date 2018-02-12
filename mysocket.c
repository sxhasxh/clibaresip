#include "mysocket.h"

#include<stdio.h>
#include<stdlib.h> 
#include<string.h> 
#include<errno.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include <sys/un.h>  
#include <unistd.h>  
#include <netdb.h>  
#include <fcntl.h>  

static int setnonblocking(int sfd) ;

char recvline[BUF_SIZE],sendline[BUF_SIZE];
int sockfd;
struct sockaddr_un address;

extern int end_flag;

int voip_client_init()
{
    int len;
    int result;

    /*创建socket,AF_UNIX通信协议,SOCK_STREAM数据方式*/  
    if ((sockfd = socket(AF_LOCAL, SOCK_STREAM, 0)) < 0) 
    {  
        printf("create socket error: %s(errno: %d)\n", strerror(errno),errno);   
        exit (EXIT_FAILURE);  
    }  

    setnonblocking(sockfd);//将套接字设置为非阻塞；否则read会死等

    address.sun_family = AF_LOCAL;  
    strcpy (address.sun_path, "/data/ola_voip_local_socket");  
    len = sizeof (address);  

    /*向服务器发送连接请求*/  
    result = connect (sockfd, (struct sockaddr *)&address, len);  
    if (result < 0) 
    {  
	printf("connect error: %s(errno: %d)\n",strerror(errno),errno); 
        exit (EXIT_FAILURE);  
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


void voip_client_read()
{  
    int bytes;
    char ch_recv[4096];
    while(end_flag == 1)
    {    
        bytes = read(sockfd,ch_recv,sizeof(ch_recv));//非阻塞，不会死等

        if(bytes > 0)
        {

  //          printf("count_read: %d \n",count_read);
  //          if(count_read > 1000){count_read = 0;}
            ch_recv[bytes] = '\0'; 

      printf("%s",ch_recv);//此处输出就不要加换行符号了，收到什么就输出什么
    //        data_analyse(ch_recv);      
        }
        if(bytes <= 0)
        {
            continue;//此处应该分开讨论，没有数据接着循环，但是如果出错的话，应该关闭文件描述符，此处没写
        }
    }

}

// 设置套接字为不阻塞  
static int setnonblocking(int sfd)  
{  
    int flags, s;  
    //得到文件状态标志  
    flags = fcntl (sfd, F_GETFL, 0);  
    if (flags == -1)  
    {  
        perror ("fcntl");  
    }  

    //设置文件状态标志  
    flags |= O_NONBLOCK;  
    s = fcntl (sfd, F_SETFL, flags);  
    if (s == -1)  
    {  
        perror ("fcntl");  
    }  

    return 0;  
}



