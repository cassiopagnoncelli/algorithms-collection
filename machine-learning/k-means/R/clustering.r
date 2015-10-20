library('mclust')
library('cluster')
library('fpc')

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

# Plotting
fit <- kmeans(df, 4)
plot(df)
clusplot(df, fit$cluster, color=T, shade=T, labels=2, lines=0)
plotcluster(df, fit$cluster)

# Mclust
fit.b <- Mclust(df)
plot(fit.b)
summary(fit.b)