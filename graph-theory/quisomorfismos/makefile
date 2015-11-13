.PHONY: all clean

all: basicos.o grafo.o main.o
	gcc -o quisomorfos grafo.o main.o basicos.o

clean: 
	find . -maxdepth 1 -name "*.o" -exec rm {} \;
	if [ -e quisomorfos ]; then rm quisomorfos; fi


#-----  Objetos  -----#
basicos.o: basicos.c

grafo.o: grafo.c

main.o: main.c

