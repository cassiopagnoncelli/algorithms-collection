# Flags do compilador
CFLAGS = -ansi\
	 -pipe\
	 -ggdb3\
	 -fstack-protector-all\
	 -Wall\
	 -Wextra\
	 -Wbad-function-cast\
	 -Wcast-align\
	 -Wcast-qual\
	 -Wconversion\
	 -Wfloat-equal\
	 -Wformat-y2k\
	 -Winit-self\
	 -Winline\
	 -Winvalid-pch\
	 -Wmissing-declarations\
	 -Wmissing-field-initializers\
	 -Wmissing-format-attribute\
	 -Wmissing-include-dirs\
	 -Wmissing-noreturn\
	 -Wmissing-prototypes\
	 -Wnested-externs\
	 -Wnormalized=nfc\
	 -Wold-style-definition\
	 -Wpacked\
	 -Wpadded\
	 -Wpointer-arith\
	 -Wredundant-decls\
	 -Wshadow\
	 -Wsign-compare\
	 -Wstack-protector\
	 -Wstrict-aliasing=2\
	 -Wstrict-prototypes\
	 -Wundef\
	 -Wunsafe-loop-optimizations\
	 -Wvolatile-register-var\
	 -Wwrite-strings\
	 -g

# Nome do programa de saida
OUT = busca

.PHONY: all clear

# Gera objetos e o executavel
all: interface.o avl-tree.o
	cc $(CFLAGS) -o $(OUT) interface.o avl-tree.o
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;

# Remove objetos, temporarios e o executavel
clear:
	find . -name "*.o" -exec rm {} \;
	find . -name "*~" -exec rm {} \;
	rm -f core
	if [ -e $(OUT) ]; then rm $(OUT); fi


avl-tree.o: avl-tree.c

interface.o: interface.c

