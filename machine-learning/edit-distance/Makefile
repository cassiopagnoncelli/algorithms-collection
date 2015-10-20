CFLAGS = -g -ggdb -ansi -Wall -Wextra -Wformat -Wdeprecated \
	-Wdeprecated-declarations -Wdiv-by-zero -Winline -Woverflow \
	-Woverlength-strings -Wlogical-op -Wpragmas -Wshadow -Wredundant-decls \
	-Wstrict-aliasing -Wstrict-overflow -Wundef -Wunknown-pragmas -Wswitch \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wcast-qual -Wconversion
#------------------------------------------------------------------------------
.PHONY: all clean

all: voce_quis_dizer #testa_edit_distance

clean:
	@$(RM) -v testa_edit_distance voce_quis_dizer edit_distance.o

#------------------------------------------------------------------------------
voce_quis_dizer: voce_quis_dizer.c edit_distance.o
	@$(CC) $(CFLAGS) -o voce_quis_dizer voce_quis_dizer.c edit_distance.o

testa_edit_distance: testa_edit_distance.c edit_distance.o
	@$(CC) $(CFLAGS) -o testa_edit_distance testa_edit_distance.c edit_distance.o

#------------------------------------------------------------------------------
edit_distance.o: edit_distance.c
	@$(CC) $(CFLAGS) -o edit_distance.o -c edit_distance.c
