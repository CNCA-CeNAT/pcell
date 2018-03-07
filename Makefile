CC = gcc
CFLAGS = -Wall -g -O -pg
STATIC = 

#STATIC = -static

LIBS = -lforms -L/usr/X11R6/lib -lX11 -lXext -lXpm -lm -pg

convection:
	$(CC) $(CFLAGS) $(STATIC) convection_main.c -o convection $(LIBS)

clean:
	rm -rf convection *.o *~ \#*

clean_data:
	rm -rf *.DAT *.pbm *.ppm

