CFLAGS = -g -Wall `pkg-config --cflags gtk+-2.0`
LIBS = `pkg-config --libs gtk+-2.0`

demo_theme: demo_theme.o
	gcc demo_theme.o -o demo_theme $(LIBS)

demo_theme.o: demo_theme.c ../couleurs.h
	gcc -c demo_theme.c $(CFLAGS)

clean:
	rm -f *.o demo_theme
