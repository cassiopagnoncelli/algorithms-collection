.PHONY: all clean

all: escorpiao.o libescorpiao.o
	gcc -o escorpiao escorpiao.o libescorpiao.o

clean:
	@find . -maxdepth 1 -name "*.o" -exec rm {} \;
	@if [ -e escorpiao ]; then rm escorpiao; fi


escorpiao.o: escorpiao.c

libescorpiao.o: libescorpiao.c
