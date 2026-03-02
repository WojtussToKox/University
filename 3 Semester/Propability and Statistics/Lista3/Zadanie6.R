# Parametry
n_k <- 180
p_k <- 1/6

# 1. P(X = 27)
prob_k1 <- dbinom(27, size = n_k, prob = p_k)
prob_k1

# 2. P(X >= 32) => 1 - P(X <= 31)
prob_k2 <- 1 - pbinom(31, size = n_k, prob = p_k)
prob_k2

# 2. P(X >= 32) => P(X > 31)
prob_k2b <- pbinom(31, size = n_k, prob = p_k, lower.tail = FALSE)
prob_k2b

# 3. P(X < 29) => P(X <= 28)
prob_k3 <- pbinom(28, size = n_k, prob = p_k)
prob_k3


# 4. P(25 <= X <= 33) => P(X <= 33) - P(X <= 24)
prob_k4 <- pbinom(33, size = n_k, prob = p_k) - pbinom(24, size = n_k, prob = p_k)
prob_k4