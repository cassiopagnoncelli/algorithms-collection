# Criterion of finding the best K in K-means algorithm.
best_k <- function(v) { sqrt(sum(v * v)) * (1 + log(length(v))) }

# Sample data.
x <- c(rnorm(50, 10, 10),
       rnorm(30, 25, 10),
       rnorm(30, 70, 9),
       rnorm(50, 90, 10),
       rnorm(50, 40, 10))
y <- c(rnorm(50, 90, 5),
       rnorm(30, 35, 10),
       rnorm(30, 70, 5),
       rnorm(50, 5, 8),
       rnorm(50, 0, 10))
df <- data.frame(x, y)

plot(df)

# K-means result
max.k <- 5
kcriteria <- c()

for (k in 1:max.k) {
  res <- kmeans(df, centers=k)
  rmse <- c()
  for (i in 1:k) {
    cluster <- scale(df[res$cluster == i,], scale=F)[,]
    error <- as.vector(apply(cluster, 1, function(x) { sum(x * x) }))
    rmse <- c(rmse, sqrt(sum(error^2) / length(error)))
  }
  kcriteria <- c(kcriteria, best_k(rmse))
  print(rmse)
}

bestk <- which.min(kcriteria)

# Report
k <- bestk
res <- kmeans(df, centers=k)
colors.v <- c('green', 'blue', 'red', 'magenta', 'cyan', 'violet',
              'slateblue', 'seagreen', 'yellow', 'brown', 'pink')

plot(df[res$cluster == 1,],
     t='p', pch=1, col=colors.v[1], lwd=0.6,
     xlim=c(min(df[,1]), max(df[,1])),
     ylim=c(min(df[,2]), max(df[,2])),
     main='K-means auto-clustering')

if (k >= 2)
  for (i in 2:k)
    lines(df[res$cluster == i,], t='p', pch=i, col=colors.v[i], lwd=0.6)

lines(res$centers, lwd=4, pch=10, col='black', t='p')

print(kcriteria)
print(bestk)
