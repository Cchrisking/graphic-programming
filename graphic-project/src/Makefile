CC=gcc
CFLAGS= -Wall -g
LIBS=-lGL -lGLU -lglut  -LGL -lX11 -lX11 -lm
LIBSDIR= -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib
all:b-spline_3
b-spline_3:main.o b-spline_3.o
	$(CC) $(CFLAGS) main.c b-spline_3.c -o exe ${LIBS} ${LIBSDIR}
clean :
	rm -f all \#*\#
