
#include <string.h>
#include <stdio.h>

static int mystrtok_r(const char *str, char *delim, char **save_str );

const char str_accept_call[] = "ola_incoming_call";     //来电话
const char str_reject_call[] = "ola_rejecting_call";    //拒接电话
const char str_cancle_call[] = "ola_cancle_call";       //对方取消电话
const char str_connec_call[] = "ola_connecting_call";   //打电话时电话正在接通
const char str_hangup_call[] = "ola_hangup_call";       //挂断电话
const char str_estblh_call[] = "ola_established_call";  //电话已接通

int data_analyse(const char * data)
{

    int i = 0;
    int str_count = 0;
    char *save_data[20];
    char * p = NULL;
    p = strstr(data , str_accept_call);//not find return null;else return point
    if(p)
    {
        str_count = mystrtok_r(data, ";", save_data);
/*        for(i = 0; i < str_count; i++)
        {
            printf("%s \n",save_data[i]);
        
        }
*/        printf("**********来电话了*************  \n");
        printf("电话来自：%s \n",save_data[4]); 
    }
    p = strstr(data , str_connec_call);
    if(p)
    {
        str_count = mystrtok_r(data, ";", save_data);
        for(i = 0; i < str_count; i++)
        {
//            printf("%s \n",save_data[i]);
        
        }
        printf("**********电话正在连接*********  \n");
   
    }   
    p = strstr(data , str_hangup_call);
    if(p)
    {
        str_count = mystrtok_r(data, ";", save_data);
        for(i = 0; i < str_count; i++)
        {
  //          printf("%s \n",save_data[i]);
        
        }
        printf("**********挂断电话*************  \n");
   
    }
    p = strstr(data , str_estblh_call);
    if(p)
    {
        str_count = mystrtok_r(data, ";", save_data);
        for(i = 0; i < str_count; i++)
        {
//            printf("%s \n",save_data[i]);
        
        }
       printf("**********电话接通了***********  \n");
   
    }
    p = strstr(data , str_cancle_call);
    if(p)
    {
        str_count = mystrtok_r(data, ";", save_data);
        for(i = 0; i < str_count; i++)
        {
//            printf("%s \n",save_data[i]);
        
        }
      printf("**********对方取消通话*********  \n");
   
    }
    p = strstr(data , str_reject_call);
    if(p)
    {
        str_count = mystrtok_r(data, ";", save_data);
        for(i = 0; i < str_count; i++)
        {
//            printf("%s \n",save_data[i]);
        
        }
     printf("**********您拒接了*************  \n");
    }

}



static int mystrtok_r(const char *str, char *delim, char **save_str )
{
    int in=0;
    char *buf=(char *)str;  
    char *inner_ptr=NULL;  
    int j=0;

    while((save_str[in]=strtok_r(buf, delim, &inner_ptr))!=NULL)   
    {  
           in++;  
           buf=NULL;  
       }  
//    printf("Here we have %d strings \n",in);  
   
    return in;
}







