$(shell mkdir -p lib)
$(shell mkdir -p bin)
$(shell mkdir -p obj)

$(CC) = gcc
$(CFLAGS) = "-O2"
$(LIBS) = boats.so multiplayer.so printers.so shipai.so textutils.so utils.so

battleship: main.o
	gcc main.c -o bin/battleship
	rm *.o
	rm -f obj/

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o obj/main.o

boats.so: boats.c
	$(CC) $(CFLAGS) -march=native -c boats.c -o obj/boats.o
	$(CC) $(CFLAGS) -shared -o lib/libboats.so obj/boats.o

multiplayer.so: multiplayer.c
	$(CC) $(CFLAGS) -march=native -c multiplayer.c -o obj/multiplayer.o
	$(CC) $(CFLAGS) -shared -o lib/libmultiplayer.so obj/multiplayer.o

printers.so: printers.c
	$(CC) $(CFLAGS) -march=native -c printers.c -o obj/printers.o
	$(CC) $(CFLAGS) -shared -o lib/libprinters.so obj/printers.o

shipai.so: shipai.c
	$(CC) $(CFLAGS) -march=native -c shipai.c -o obj/shipai.o
	$(CC) $(CFLAGS) -shared -o lib/libshipai.so obj/shipai.o

textutils.so: textutils.c
	$(CC) $(CFLAGS) -march=native -c textutils.c -o obj/textutils.o
	$(CC) $(CFLAGS) -shared -o lib/libtextutils.so obj/textutils.o

utils.so: utils.c
	$(CC) $(CFLAGS) -march=native -c utils.c -o obj/utils.o
	$(CC) $(CFLAGS) -shared -o lib/libutils.so obj/utils.o

install:
	echo "To be implemented"

clean:
	rm -rf bin/
	rm -rf lib/
	rm -rf obj/


