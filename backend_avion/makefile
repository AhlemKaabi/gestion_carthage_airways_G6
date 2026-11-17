avion: avion.o main_avion.o
	gcc avion.o main_avion.o -o avion
avion.o: avion.c avion.h
	gcc -c -g -Wall avion.c avion.h
avion_main.o: avion.h main_avion.c
	gcc -c -g -Wall avion.h main_avion.c

