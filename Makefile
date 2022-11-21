CC=gcc
LIBS=-lGL -lGLU -lglut  -LGL -lX11 -lX11 -lm
LIBSDIR= -I/usr/X11R6/include -L/usr/lib -L/usr/X11R6/lib
all :tp4-5
tp4-5:tp4-5
	${CC} tp4-5.c -o exe ${LIBS} ${LIBSDIR}

clean :
	rm -f tp4-5 \#*\#
