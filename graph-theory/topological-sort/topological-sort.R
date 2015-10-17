library('igraph')

# Graph generation and properties.
randomGraph <- function(n=10) {
  m <- matrix(as.integer(sample(0:10, n*n, replace=T) >= 9), nrow=n)
  diag(m) <- 0
  m
}

# E(G) in a listed form.
edges <- function(m) {
  n <- ncol(m)
  r <- c()
  for (i in 1:n)
    for (j in i:n)
      if (j > i && 0 != m[i,j] && m[i,j] < Inf)
        r <- rbind(r, c(i,j))
  r
}

# Plot a graph.
plotGraph <- function(m) {
  igraph <- graph.adjacency(m, mode='directed', weighted=T, diag=F)
  plot(igraph, edge.label=E(igraph)$weight)
}

# L ← Empty list that will contain the sorted elements
# S ← Set of all nodes with no incoming edges
#
# while S is non-empty do
#   remove a node n from S
#   add n to tail of L
#   for each node m with an edge e from n to m do
#     remove edge e from the graph
#     if m has no other incoming edges then
#       insert m into S
#
# if graph has edges then
#   return error (graph has at least one cycle)
# else 
#   return L (a topologically sorted order)

noIncomingEdges <- function(m) {
  n <- nrow(m)
  nie <- c()
  for (i in 1:n)
    if (sum(m[,i]) == 0)
      nie <- c(nie, i)
  nie
}

toposort <- function(g) {
  l <- c()
  s <- noIncomingEdges(g)
  
  while (length(s) > 0) {
    n <- s[1]; s <- s[-1]
    l <- c(l, n)
    for (m in which(g[n,] != 0)) {
      g[n,m] <- 0
      if (sum(g[,m]) == 0)
        s <- c(s, m)
    }
  }
  
  if (sum(g) != 0)
    return(FALSE)
  else
    return(l)
}

# Report.
g <- randomGraph(6)
print(toposort(g))
plotGraph(g)
