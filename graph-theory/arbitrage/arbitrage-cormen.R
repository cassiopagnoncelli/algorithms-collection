library('combinat')
library('permute')

# Find an arbitrage opportunity.
findarb <- function(m) {
  n <- nrow(m)
  p <- allPerms(n)
  bestop <- 1
  while (ncol(p) > 2) {
    for (row in 1:nrow(p)) {
      nodes <- p[row,]
      op <- m[nodes[ncol(p)], nodes[1]]
      for (k in 2:length(nodes)) op <- op * m[nodes[k-1], nodes[k]]
      if (op > 1) print(nodes)
      bestop <- max(bestop, op)
    }
    p <- unique(p[,-2])
  }
  print(bestop)
}

# Example
m <- rbind(
  c(Inf, 1.34177, 0.85909, 104.608, 1.23576, 1.31251),
  c(0.7452842, Inf, 0.64033605, 77.959, 0.92085, 0.97852145),
  c(1.1640224, 1.56168, Inf, 121.745, 1.43811, 1.52776),
  c(0.0095595, 0.01282726, 0.00821389, Inf, 0.01181268, 0.01255241),
  c(0.80922186, 1.0859532, 0.6953571, 84.629, Inf, 1.06274443),
  c(0.761899, 1.02195, 0.65455307, 79.666, 0.94096, Inf))

findarb(m)