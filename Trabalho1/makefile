parametrosCompilacao=-Wall #-Wshadow
nomePrograma=myavl

all: $(nomePrograma)

$(nomePrograma): main.o libAVL.o
	gcc -o $(nomePrograma) main.o libAVL.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

libAVL.o: libAVL.h libAVL.c
	gcc -c libAVL.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)