# Parametry
n <- 6
p <- 0.5

# 1. P(X = 5) - Prawdopodobieństwo punktowe
prob_1 <- dbinom(5, size = n, prob = p)
prob_1

# 2. P(X >= 3)
# W R pbinom liczy P(X <= k), więc P(X >= 3) to 1 - P(X <= 2)
# Lub ustawić lower.tail na false i liczy P(X > k) -> P(X > 2)
prob_2 <- 1 - pbinom(2, size = n, prob = p)
prob_2

prob_2b <- pbinom(2, size = n, prob = p, lower.tail = FALSE)
prob_2b

# 3. P(2 <= X <= 4)
# To jest P(X <= 4) - P(X <= 1)
prob_3 <- pbinom(4, size = n, prob = p) - pbinom(1, size = n, prob = p)
prob_3

# 4. Wykres rozkładu (typ "h" - histogram liniowy)
x_vals <- 0:n
y_vals <- dbinom(x_vals, size = n, prob = p)
plot(x_vals, y_vals, type = "h", lwd = 5, col = "blue",
     main = "Rozkład liczby reszek w 6 rzutach",
     xlab = "Liczba reszek", ylab = "Prawdopodobieństwo")

