parametrosCompilacao=-Wall -lm
nomePrograma=myht

all: $(nomePrograma)

$(nomePrograma): main.o libHT.o
	gcc -o $(nomePrograma) main.o libHT.o $(parametrosCompilacao)

main.o: main.c
	gcc -c main.c $(parametrosCompilacao)

libHT.o: libHT.h libHT.c
	gcc -c libHT.c $(parametrosCompilacao)

clean:
	rm -f *.o *.gch $(nomePrograma)