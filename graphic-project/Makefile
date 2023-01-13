CC=gcc
CFLAGS=-Wall -g
LIBS=-lGL -lGLU -lglut  -LGL -lX11 -lX11 -lm
LIBSDIR= -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib
all:projet
header.o:header/header.h
		$(CC) $(CFLAGS) -c header/header.h ${LIBS} ${LIBSDIR}
main.o:src/main.c header.o
	$(CC) $(CFLAGS) -c src/main.c header.o ${LIBS} ${LIBSDIR}
b-spline.o:src/b-spline_3.c
	$(CC) $(CFLAGS) -c src/b-spline_3.c ${LIBS} ${LIBSDIR}
projet:main.o b-spline_3.o bezier.o
	$(CC) $(CFLAGS) main.o b-spline_3.o
clean :
	rm -f projet *.o \#*\#
