test:test.o
	gcc test.o -o test
test.o:a_client.c
	gcc -c a_client.c -o test.o
clean:
	rm *.o test
