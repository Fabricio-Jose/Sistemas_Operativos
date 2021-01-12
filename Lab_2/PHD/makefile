padre:
	gcc src/padre.c -o bin/padre
	./bin/padre

hijo:
	gcc src/hijo.c -lrt  -o bin/hijo
	./bin/hijo

nieto:
	gcc src/nieto.c -lrt -o bin/nieto
	./bin/nieto

all:
	gcc src/hijo.c -lrt -o bin/hijo
	gcc src/nieto.c -lrt  -o bin/nieto
	gcc src/padre.c -o bin/padre
	./bin/padre

clean:
	rm -f bin/padre
	rm -f bin/hijo
	rm -f bin/nieto
