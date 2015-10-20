# Libraries.
library(arules)
library(arulesViz)
library(datasets)

# Dataset.
data(Groceries)

# Plot most frequent items.
itemFrequencyPlot(Groceries, topN=20, type='absolute')
summary(Groceries)

# Analysing all transactions.
rules <- apriori(Groceries, parameter=list(supp=0.001, conf=0.8, maxlen=8))
options(digits=2)

info(rules)
inspect(rules[1:10])
summary(rules)

rules <- sort(rules, by='lift', decreasing=T)

subset.matrix <- is.subset(rules, rules)    # Eliminating redundancies.
subset.matrix[lower.tri(subset.matrix, diag=T)] <- NA
redundant <- colSums(subset.matrix, na.rm=T) >= 1
rules.pruned <- rules[!redundant]
rules <- rules.pruned

plot(rules, measure=c('support', 'lift'), shading='confidence')
plot(rules, method='graph', interactive=T)
plot(rules, method="paracoord", control=list(reorder=TRUE))

# Analysing transactions leading to whole milk only.
rules <- apriori(data=Groceries,
                 parameter=list(supp=0.001, conf=0.8, maxlen=3),
                 appearance=list(default='lhs', rhs='whole milk'),
                 control=list(verbose=F))
rules <- sort(rules, decreasing=T, by='confidence')

inspect(head(rules))  # strongest rules are the ones with higher confidence

subset.matrix <- is.subset(rules, rules)    # Eliminating redundancies.
subset.matrix[lower.tri(subset.matrix, diag=T)] <- NA
redundant <- colSums(subset.matrix, na.rm=T) >= 1
rules.pruned <- rules[!redundant]
rules <- rules.pruned

plot(rules, measure=c('support', 'lift'), shading='confidence')
plot(rules, method='graph', interactive=T)

# Analysing transactions originating in whole milk.
rules <- apriori(data=Groceries,
                 parameter=list(supp=0.001, conf=0.15, maxlen=2),
                 appearance=list(default='rhs', lhs='whole milk'))
rules <- sort(rules, decreasing=T, by='confidence')

inspect(head(rules))  # strongest rules are the ones with higher confidence

subset.matrix <- is.subset(rules, rules)    # Eliminating redundancies.
subset.matrix[lower.tri(subset.matrix, diag=T)] <- NA
redundant <- colSums(subset.matrix, na.rm=T) >= 1
rules.pruned <- rules[!redundant]
rules <- rules.pruned

plot(rules, measure=c('support', 'lift'), shading='confidence')
plot(rules, method='graph', interactive=T)