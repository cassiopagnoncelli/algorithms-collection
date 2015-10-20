CC     = gcc
CFLAGS = -lm -g -ggdb -ansi -Wall -Wextra -Wformat -Wdeprecated \
	-Wdeprecated-declarations -Wdiv-by-zero -Winline -Woverflow \
	-Woverlength-strings -Wlogical-op -Wpragmas -Wshadow -Wredundant-decls \
	-Wstrict-aliasing -Wstrict-overflow -Wundef -Wunknown-pragmas -Wswitch \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wcast-qual -Wconversion

.PHONY: all clean
.SILENT: all clean k-means

all: k-means

clean:
	$(RM) -v k-means PONTOS

k-means: k-means.c
	$(CC) $(CFLAGS) -o k-means k-means.c -lm
