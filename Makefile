$(shell mkdir -p lib)
$(shell mkdir -p bin)


all: battleship
exec: main.c
	gcc main.c -o exec

battleship: main.c
	gcc main.c -o bin/battleship

install:
	echo "To be implemented"

clean:
	rm -rf exec
	rm -rf bin/
	rm -rf lib/



