KNN := -DEUCLIDIANA          # para usar cálculo de distância euclidiana
                              # (método padrão).
#KNN := -DMANHATTAN           # para usar cálculo de distância Manhattan.
#KNN := -DCHEBYSCHEV          # para usar cálculo de distância Chebyschev.
#KNN := -DMINKOWSKI=6         # para usar cálculo de distância Minkowski
                              # (parâmetro deve ser um inteiro positivo; basta
                              # valorar MINKOWSKI com o parâmetro desejado.)
                              # Repare que Minkowski é uma generalização das
                              # distâncias Manhattan (p=1), euclidiana (p=2) e
                              # Chebyschev (quando p coincide com a quantidade
                              # de características). 



#--- flags de implementação ---------------------------------------------------
CC       := g++
CPPFLAGS := -g -ansi -pedantic -pthread -Wall -Wextra -Wformat -Wdeprecated \
	-Wdeprecated-declarations -Wdiv-by-zero -Winline -Woverflow \
	-Wnon-virtual-dtor -Woverlength-strings -Wlogical-op -Wpragmas \
	-Wshadow -Wredundant-decls -Wstrict-aliasing -Wstrict-overflow \
	-Wstrict-null-sentinel -Wundef -Wunknown-pragmas -Wswitch \
	-Wswitch-default -Wswitch-enum -Wcast-align -Wcast-qual -Wconversion \
	-O2 -lm $(KNN)
SRCDIR  := src
BINDIR  := bin
COUT    := $(BINDIR)/knn
OPTIM   := $(BINDIR)/otimizador


#--- `all' e `clean' não geram executável de mesmo nome. ----------------------
.PHONY: all clean

all: knn_main otimizador

clean:
	@$(RM) -v $(COUT) $(OPTIM) $(SRCDIR)/*.o

#--- arquivos objetos ---------------------------------------------------------
knn_core.o: $(SRCDIR)/knn_core.cc
	@$(CC) $(CPPFLAGS) -o $(SRCDIR)/knn_core.o -c $(SRCDIR)/knn_core.cc

knn_main: $(SRCDIR)/knn_main.cc $(SRCDIR)/knn_core.o
	@$(CC) $(CPPFLAGS) -o $(COUT) $(SRCDIR)/knn_main.cc $(SRCDIR)/knn_core.o
	@if test -e $(COUT); then echo "Executável $(COUT) pronto."; fi

otimizador: $(SRCDIR)/otimizador.cc $(SRCDIR)/knn_core.o
	@$(CC) $(CPPFLAGS) -o $(OPTIM) $(SRCDIR)/otimizador.cc $(SRCDIR)/knn_core.o
	@if test -e $(OPTIM); then echo "Executável $(OPTIM) pronto."; fi
