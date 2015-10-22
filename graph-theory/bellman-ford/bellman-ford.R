library('igraph')

# Graph generation and properties.
randomGraph <- function(n=10) {
  m <- matrix(sample(0:3, n*n, replace=T), nrow=n)
  m[lower.tri(m)] <- t(m)[lower.tri(m)]
  m[m == 0] <- Inf
  diag(m) <- Inf
  
  distance <- rep(Inf, n)
  predecessor <- rep(NA, n)
  
  list(m=m, n=n, d=distance, p=predecessor)
}

edges <- function(m) {
  n <- ncol(m)
  r <- c()
  for (i in 1:n)
    for (j in i:n)
      if (j > i && 0 != m[i,j] && m[i,j] < Inf)
        r <- rbind(r, c(i,j))
  r
}

plotGraph <- function(G) {
  h <- g$m
  h[h == Inf] <- 0
  igraph <- graph.adjacency(h, mode='undirected', weighted=T, diag=F)
  plot(igraph, edge.label=E(igraph)$weight)
}

# Bellman-Ford.
initializeSingleSource <- function(G, s) {
  for (i in 1:G$n) {
    G$d[i] <- Inf
    G$p[i] <- NA
  }
  G$d[s] = 0
  return(G)
}

relax <- function(G, u, v) {
  if (G$d[v] > G$d[u] + G$m[u,v]) {
    G$d[v] <- G$d[u] + G$m[u,v]
    G$p[v] <- u
  }
  return(G)
}

bellman.ford <- function(G, s) {
  G <- initializeSingleSource(G, s)
  for (i in 1:(G$n - 1)) {
    e <- edges(G$m)
    for (row in 1:nrow(e))
      G <- relax(G, e[row,1], e[row,2])
  }
  
  e <- edges(G$m)
  ret <- TRUE
  for (row in ncol(e))
    if (G$d[e[row,1]] > G$d[e[row,2]] + G$m[e[row,1],e[row,2]])
      ret <- FALSE
  
  list(graph=G, ret=ret)
}

# Simulation, results and plot.
g <- randomGraph(5)
print((res <- bellman.ford(g, 1)))
plotGraph(g)