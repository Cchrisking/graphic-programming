CC=gcc
LIBS=-lGL -lGLU -lglut  -LGL -lX11 -lX11 -lm
LIBSDIR= -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib
all :tp3v3
tp3v3:tp3v3
	${CC} tp3v3.c -o exe ${LIBS} ${LIBSDIR}

clean :
	rm -f tp3v3 \#*\#
