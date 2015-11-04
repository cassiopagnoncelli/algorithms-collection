CC       = g++
CPPFLAGS = -lm -ansi -g -ggdb -ansi -Wall -Wextra -Wformat -Wdeprecated \
	-Wdeprecated-declarations -Wdiv-by-zero -Winline -Woverflow \
	-Woverlength-strings -Wlogical-op -Wpragmas -Wshadow -Wredundant-decls \
	-Wstrict-aliasing -Wstrict-overflow -Wundef -Wunknown-pragmas -Wswitch \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wcast-qual -Wconversion
#------------------------------------------------------------------------------
.PHONY: all clean

all: insertion

clean:
	@$(RM) -v insertion

#------------------------------------------------------------------------------
insertion: insertion.cc
	@$(CC) $(CFLAGS) -o insertion insertion.cc
