TARGET=jogo.exe
CC=gcc
ALLEGRO=C:\allegro\include
STATIC=liballegro_monolith.dll.a
LD=gcc
OBJS=jogo.o
all: $(OBJS)
	$(LD) -I $(ALLEGRO) -o $(TARGET) $(OBJS)  $(STATIC)
	$(TARGET)
jogo.o: jogo.c
	$(CC) -I $(ALLEGRO) -c jogo.c -o jogo.o
