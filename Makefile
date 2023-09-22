$(shell mkdir -p lib bin obj)

CC = gcc
CFLAGS = -O2 -march=native
LIBS = -lboats -lmultiplayer -lprinters -lshipai -ltextutils -lutils

battleship: main.o boats.so multiplayer.so printers.so shipai.so textutils.so utils.so
	$(CC) $(CFLAGS) obj/main.o -o bin/battleship -Wl,-rpath,./lib/ -L./lib/ $(LIBS)
	rm *.o
	rm -f obj/

debug: main.o boats.so multiplayer.so printers.so shipai.so textutils.so utils.so
	$(CC) $(CFLAGS) obj/main.o -o bin/battleship -DDEBUG -Wl,-rpath,./lib/ -L./lib/ $(LIBS)
	rm *.o
	rm -f obj/

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o obj/main.o

boats.so: boats.c
	$(CC) $(CFLAGS) -fPIC -c boats.c -o obj/boats.o
	$(CC) $(CFLAGS) -shared -o lib/libboats.so obj/boats.o

multiplayer.so: multiplayer.c
	$(CC) $(CFLAGS) -fPIC -c multiplayer.c -o obj/multiplayer.o
	$(CC) $(CFLAGS) -shared -o lib/libmultiplayer.so obj/multiplayer.o

printers.so: printers.c
	$(CC) $(CFLAGS) -fPIC -c printers.c -o obj/printers.o
	$(CC) $(CFLAGS) -shared -o lib/libprinters.so obj/printers.o

shipai.so: shipai.c
	$(CC) $(CFLAGS) -fPIC -c shipai.c -o obj/shipai.o
	$(CC) $(CFLAGS) -shared -o lib/libshipai.so obj/shipai.o

textutils.so: textutils.c
	$(CC) $(CFLAGS) -fPIC -c textutils.c -o obj/textutils.o
	$(CC) $(CFLAGS) -shared -o lib/libtextutils.so obj/textutils.o

utils.so: utils.c
	$(CC) $(CFLAGS) -fPIC -c utils.c -o obj/utils.o
	$(CC) $(CFLAGS) -shared -o lib/libutils.so obj/utils.o

install:
	echo "To be implemented"

clean:
	rm -rf bin/
	rm -rf lib/
	rm -rf obj/


