object = main.o mysocket.o data_analyse.o

test:$(object)
	gcc  -o test $(object) -lpthread
main.o:
mysocket.o:
data_analyse.o:data_analyse.c
	gcc -c data_analyse.c -o data_analyse.o








clean:
	rm *.o test
