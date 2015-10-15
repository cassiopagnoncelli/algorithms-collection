CC     = @gcc
CFLAGS = -lm -ansi \
	-g -ggdb -ansi -Wall -Wextra -Wformat -Wdeprecated \
	-Wdeprecated-declarations -Wdiv-by-zero -Winline -Woverflow \
	-Woverlength-strings -Wlogical-op -Wpragmas -Wshadow -Wredundant-decls \
	-Wstrict-aliasing -Wstrict-overflow -Wundef -Wunknown-pragmas -Wswitch \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wcast-qual -Wconversion
#------------------------------------------------------------------------------
.PHONY: all clean

all: priority_queue

clean:
	@$(RM) -v priority_queue *.o

#------------------------------------------------------------------------------
priority_queue: priority_queue.c heap.o

heap.o: heap.c
