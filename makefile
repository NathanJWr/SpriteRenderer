sr.out: sr.o
	gcc -Wall -Werror -o sr.out sr.o -lSDL2 -lSDL2_image 

sr.o: sr.c
	gcc -Wall -Werror -c -o sr.o sr.c -lSDL2 -lSDL2_image

clean:
	rm -f *.out *.o
