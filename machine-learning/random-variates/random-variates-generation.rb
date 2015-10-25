# Methods:
# - Inverse method.
# - Acceptance-Rejection method.
# - Monte Carlo
# - Parametric bootstrap
# - Importance sampling
# - Markov chain monte carlo
#

# Array#sum is something needed.
class Array
  def sum
    #self.inject { |sum,x| sum + x }
    self.inject(0, &:+)
  end

  def prod
    self.inject(0, &:*)
  end
end

# Bernoulli.
def rbernoulli(prob)
  rand < prob ? 1 : 0
end

# Binomial, a simple sum of Bernoulli samples.
def rbinomial(mean, prob)
  ((1..mean).map { rbernoulli(prob) }).sum
end

# Poisson sampling.
def rpois(lambd)
  l = Math.exp(-lambd)
  k = 0
  p = 1
  begin
    k += 1
    p *= rand 
  end while p > l
  k - 1
end

# Exponential sampling.
def rexp(rate)
  -Math.log(rand) / rate
end

# Gamma sampling.
def rgamma(k, lambd)
  ((1..k).map { rexp(lambd) }).sum
end

# N(0,1) sampling from the Box-Muller theorem, in two flavours.
# Note: Feel free to exchange the cos by sin.
def rnormal(mean, sd)
  mean + (Math.sqrt(-2 * Math.log(rand)) * Math.cos(2 * Math::PI * rand)) * sd
end

# Beta.
# NOTE: NOT WORKING!
def rbeta(alpha, beta)
  alpha = alpha.to_f
  beta = beta.to_f

  log10 = Math.log(10)

  a = alpha + beta
  if [alpha, beta].min <= 1
    b = [1 / alpha, 1 / beta].max
  else
    b = Math.sqrt((a - 2) / (2 * alpha * beta - a))
  end
  c = alpha + 1/b

  begin
    u1, u2 = rand, rand
    v = b * Math.log(u1 / (1 - u1))/logbase
    w = alpha * Math.exp(v)
  end while a * Math.log(a / (beta + w))/logbase + c * v - Math.log(4)/logbase < Math.log(u1*u1*u2)/logbase

  w / (beta + w)
end

# Negative binomial.

# F.

# Weibull.
# NOTE: TEST.
def rweibull(alpha, beta)
  beta.to_f * (- Math.log(rand))**(1 / alpha.to_f)
end

# Hypergeometric.

# Geometric.

# Chi-squared.

# Erlang.
# NOTE: TEST.
def rerlang(k, beta)
  -(beta.to_f / k) * Math.log((k.times.collect { rand }).prod)
end
