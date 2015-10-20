# TODO:
# Generalize to one-class, multi-class, regression and timeseries landscapes.
#

library('MASS')
library('ks')
library('e1071')   # svm
library('nnet')
library('plyr')

# Dataset.
n <- 400
df <- rbind(
  data.frame(x1=rnorm(n, 7, 1), x2=rnorm(n, 7, 1.5), y=rep('A', n)),
  data.frame(x1=rnorm(n, 4, 1), x2=rnorm(n, 4, 1),   y=rep('B', n)))

plot(df$x1, df$x2, col=1 + as.integer(df$y), xlab='x1', ylab='x2')

# Classifiers.
# - SVM.
fit1 <- svm(y ~ x1 + x2, data = df)
plot(fit1, data=df)

pred1 <- fitted(fit1)   # ==predict(fit, df)
table(pred1, df$y)

c1.correct <- df[df$y==as.factor(pred1),]
c1.wrong <- df[df$y!=as.factor(pred1),]

# - Neural net.
fit2 <- nnet(y ~ x1 + x2, data = df, size=2)
print(fit2)
summary(fit2)

pred2 <- revalue(as.factor(round(predict(fit2, df))), c('0'='A','1'='B'))
table(pred2, df$y)

c2.correct <- df[df$y==as.factor(pred2),]
c2.wrong <- df[df$y!=as.factor(pred2),]

# Test set and assess how classifiers perform.
n <- 1000
test <- rbind(
  data.frame(x1=rnorm(n/2, 7, 1), x2=rnorm(n/2, 7, 1.5), y=rep('A', n/2)),
  data.frame(x1=rnorm(n/2, 4, 1), x2=rnorm(n/2, 4, 1),   y=rep('B', n/2)))

table.c1 <- table(predict(fit1, test), test$y)
table.c2 <- table(revalue(as.factor(round(predict(fit2, test))), c('0'='A','1'='B')), test$y)

# Local boosting ensemble.
# Idea is
# 1. for each classifier c_i, compute hits' and misclassifications' pdfs H_i and M_i
# 2. in order to classify a point p(x1, x2), use the classifier that gives
#    the highest H_i(p)-M_i(p).
c1.correct.pdf <- kde(c1.correct[,1:2], Hpi(c1.correct[,1:2]))
c1.wrong.pdf <- kde(c1.wrong[,1:2], Hpi(c1.wrong[,1:2]))
c1.confidence <- function(points) { 
  predict(c1.correct.pdf, x=points) - predict(c1.wrong.pdf, x=points)
}

c2.correct.pdf <- kde(c2.correct[,1:2], Hpi(c2.correct[,1:2]))
c2.wrong.pdf <- kde(c2.wrong[,1:2], Hpi(c2.wrong[,1:2]))
c2.confidence <- function(points) { 
  predict(c2.correct.pdf, x=points) - predict(c2.wrong.pdf, x=points)
}

options(digits=3)
cselection <- data.frame(c1=c1.confidence(test[,1:2]), c2=c2.confidence(test[,1:2]))
cselection <- data.frame(cselection, selection=apply(pick, 1, function(x) { ifelse(x[1] > x[2], 'c1', 'c2') }))
sel <- cselection$selection
sel.c1 <- which(sel == 'c1')
sel.c2 <- which(sel == 'c2')

c1.pred <- predict(fit1, test[sel.c1, 1:2])
c2.pred <- revalue(as.factor(round(predict(fit2, test[sel.c2, 1:2]))), c('0'='A','1'='B'))

pred <- c(c1.pred, c2.pred)
actual <- c(test[sel.c1,'y'], test[sel.c2,'y'])
table.boost <- table(pred, actual)

misclassifications <- cselection[as.integer(which(pred != actual)),]
misclassifications <- data.frame(misclassifications, max=apply(misclassifications, 1, function(x){ as.double(x[x[3]]) }))
could_be_avoided <- misclassifications[which(misclassifications$max < 0),]

table.c1; sum(diag(table.c1)) / sum(table.c1)
table.c2; sum(diag(table.c2)) / sum(table.c2)
table.boost; sum(diag(table.boost)) / sum(table.boost)
could_be_avoided
