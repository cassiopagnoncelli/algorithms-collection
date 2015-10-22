library('igraph')

# Graph generation and properties.
randomGraph <- function(n=10, thres=0.8) {
  v <- as.integer(runif(n*n, 1, 10.1))
  v[v < thres*n] <- 0
  m <- matrix(v, nrow=n)
  diag(m) <- 0
  m[lower.tri(m)] <- 0
  m
}

# E(G) in a listed form.
edges <- function(m, sort_by_weight=F) {
  n <- ncol(m)
  r <- data.frame(src=c(), dst=c(), weight=c())
  for (i in 1:n)
    for (j in i:n)
      if (j > i && 0 != m[i,j] && m[i,j] < Inf)
        r <- rbind(r, data.frame(src=i, dst=j, weight=m[i,j]))
  
  if (sort_by_weight)
    r[with(r, order(weight)),]
  else
    r
}

# Plot a graph.
plotGraph <- function(m) {
  igraph <- graph.adjacency(m, mode='directed', weighted=T, diag=F)
  plot(igraph, edge.label=E(igraph)$weight)
}

# A ← {}
# for each vertex v
#   make-set v
# 
# sort edges into nondecreasing order by weight
# 
# for each edge (u,v) taken in nondecreasing order
#   if find-set(u) != find-set(v)
#     A = A U {(u,v)}
#     union(u, v)
# 
# return A

differentVectors <- function(u, v) {
  if (length(u) != length(v))
    return(TRUE)
  
  u <- u[!is.na(u)]
  v <- v[!is.na(v)]
  
  if (length(u) != length(v))
    return(TRUE)
  
  if (length(u) == 0)
    return(TRUE)
  
  for (i in 1:length(u))
    if (u[i] == v[i])
      return(TRUE)
  
  return(FALSE)
}

union <- function(L, u, v) {
  L[[paste('v', u, sep='')]] <- c(
    L[[paste('v', u, sep='')]],
    L[[paste('v', v, sep='')]])
  
  L[[paste('v', v, sep='')]] <- NA
  
  L
}

kruskal <- function(m) {
  n <- nrow(m)
  
  A <- data.frame(src=c(), dst=c())
  for (i in 1:n)
    L[[paste('v', i, sep='')]] <- NA
  
  e <- edges(m, sort_by_weight=TRUE)
  for (i in 1:nrow(e)) {
    u <- e$src[i]
    v <- e$dst[i]
    Su <- L[[paste('v', e$src[i], sep='')]]
    Sv <- L[[paste('v', e$dst[i], sep='')]]
    if (differentVectors(Su, Sv)) {
      A <- rbind(A, data.frame(src=u, dst=v))
      L <- union(L, u, v)
    }
  }
  
  A
}

# Report.
g <- randomGraph(6)
cat('MST is made of the edges')
print(kruskal(g))
plotGraph(g)
