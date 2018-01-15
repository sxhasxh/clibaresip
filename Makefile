object = pthread_client.o data_analyse.o

test:$(object)
	gcc  -o test $(object) -lpthread
pthread_client.o:pthread_client.c
	gcc -c pthread_client.c -o pthread_client.o 
data_analyse.o:data_analyse.c
	gcc -c data_analyse.c -o data_analyse.o








clean:
	rm *.o test
