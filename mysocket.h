#define MAXLINE 4096 
#define BARESIP_PORT 5555 
#define BUF_SIZE 4096


int voip_client_init();

int voip_client_send(const char *str);

int voip_client_send_from_stdin();

void voip_client_recv();






