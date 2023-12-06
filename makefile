CC = gcc
CFLAGS = -Wall -Wextra

all: download

download: main.o url.o
	$(CC) $(CFLAGS) -o download main.o url.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

url.o: url.c
	$(CC) $(CFLAGS) -c url.c

clean:
	rm -f download main.o url.o

