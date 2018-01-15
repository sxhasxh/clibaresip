test:test.o
	gcc test.o -o test -lpthread
test.o:pthread_client.c
	gcc -c pthread_client.c -o test.o 
clean:
	rm *.o test
