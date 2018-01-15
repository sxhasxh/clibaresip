//rececive data from 
//sip:101@10.100.9.233: Incoming call from: 103 sip:103@192.168.150.108 - (press 'a' to accept)
//sip:103@192.168.150.108: session closed: Connection reset by peer
//sip:101@10.100.9.233: Incoming call from: 103 sip:103@192.168.150.108 - (press 'a' to accept)
//b
//call: rejecting incoming call from sip:103@192.168.150.108 (486 Rejected)

#include <string.h>

#include <stdio.h>

int data_analyse(const char * data)
{

    const char str_accept[] = "- (press 'a' to accept)";
   // const char str_incoming[] = "- (press 'a' to accept)";
   const char str_reset_by_peer[] = "session closed: Connection reset by peer";
   const char str_rejecting_incoming_call[] = "rejecting incoming call ";

    char * p = NULL;
    p = strstr(data , str_accept);
    if(p)
        printf("**********来电话了*********  \n");
    p = strstr(data , str_reset_by_peer);
    if(p)
        printf("**********对方挂电话了*********  \n");
    p = strstr(data , str_rejecting_incoming_call);
    if(p)
        printf("**********您拒接了*********  \n");




}











