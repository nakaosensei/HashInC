hash:
	gcc -c hash.c
	gcc main.c hash.o -o main
	./main 10

clean:
	rm *.o
	rm main
