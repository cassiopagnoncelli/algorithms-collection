CC       = g++
CPPFLAGS = -lm -ansi -g -ggdb -ansi -Wall -Wextra -Wformat -Wdeprecated \
	-Wdeprecated-declarations -Wdiv-by-zero -Winline -Woverflow \
	-Woverlength-strings -Wlogical-op -Wpragmas -Wshadow -Wredundant-decls \
	-Wstrict-aliasing -Wstrict-overflow -Wundef -Wunknown-pragmas -Wswitch \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wcast-qual -Wconversion
#------------------------------------------------------------------------------
.PHONY: all clean

all: bubble

clean:
	@$(RM) -v bubble

#------------------------------------------------------------------------------
bubble: bubble.cc
	@$(CC) $(CFLAGS) -o bubble bubble.cc
