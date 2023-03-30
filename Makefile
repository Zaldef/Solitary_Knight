TARGET=Solitary_Knight.exe
CC=gcc
ALLEGRO=C:\allegro\include
STATIC=liballegro_monolith.dll.a
LD=gcc
OBJS=Solitary_Knight.o
all: $(OBJS)
	$(LD) -I $(ALLEGRO) -o $(TARGET) $(OBJS)  $(STATIC)
	$(TARGET)
Solitary_Knight.o: Solitary_Knight.c
	$(CC) -I $(ALLEGRO) -c Solitary_Knight.c -o Solitary_Knight.o
