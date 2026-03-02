# Parametry
a <- 4
b <- 12

# 1. P(X < 7)
# Dla zmiennych ciągłych P(X < k) to to samo co P(X <= k)
prob_u1 <- punif(7, min = a, max = b)
prob_u1

# 2. P(5 < X < 11) => P(X < 11) - P(X < 5)
prob_u2 <- punif(11, min = a, max = b) - punif(5, min = a, max = b)
prob_u2

# 3. P(X > 10) => 1 - P(X < 10)
prob_u3 <- 1 - punif(10, min = a, max = b)
prob_u3

prob_u3b <- punif(10, min = a, max = b, lower.tail = FALSE)
prob_u3b


# 4. Wyznaczyc x  taki ze P(X > x) = 0.6
# P(X > x) = 0.6  =>  1 - P(X <= x) = 0.6  =>  P(X <= x) = 0.4

x_szukane <- qunif(0.4, min = a, max = b)
x_szukane

x_szukane_b <- qunif(0.6, min = a, max = b, lower.tail = FALSE)
x_szukane_b
