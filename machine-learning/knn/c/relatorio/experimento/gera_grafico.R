#!/usr/bin/R

entrada <- "hist_minkowski_6_1"
saida <- "grafico_minkowski_6_1"
titulo <- "k-NN usando distância Minkowski(p=6)\n(dados normalizados)"
maximo <- "(taxa de acertos máxima é de 0.882 quando k=1)"

x <- read.table(file=entrada, header=FALSE)
postscript(file=saida, horizontal=F, pagecentre=F, paper="special",width=8.33,height=5.56)
plot(x, xlab="Valor de k", ylab="Taxa de acerto", type="h", main=titulo, sub=maximo)
dev.off()
