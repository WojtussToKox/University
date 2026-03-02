set.seed(123)

# --- 1. Rozkład Jednostajny [0,1] ---
liczba_jednostajnych <- 5000
dane_jednostajne <- runif(liczba_jednostajnych, min = 0, max = 1)

# Ustawienie obszaru wykresów: 1 wiersz, 2 kolumny
par(mfrow=c(1,2))

# i) Histogram
hist(dane_jednostajne, freq = FALSE, 
     main = "Histogram - Rozkład Jednostajny", 
     xlab = "Wartość", col = "lightblue", border = "white")

# ii) Estymator jądrowy
plot(density(dane_jednostajne), 
     main = "Estymator jądrowy - Jednostajny", 
     lwd = 2, col = "blue")



# --- 2. Rozkład Normalny N(100, 15) ---
liczba_normalnych <- 3000
srednia_teoretyczna <- 100
odchylenie_teoretyczne <- 15
dane_normalne <- rnorm(liczba_normalnych, mean = srednia_teoretyczna, sd = odchylenie_teoretyczne)

# Reset i nowe wykresy
par(mfrow=c(1,2))

# i) Histogram
hist(dane_normalne, freq = FALSE, 
     main = "Histogram - Rozkład Normalny", 
     xlab = "Wartość", col = "lightgreen", border = "white")

# ii) Estymator jądrowy
plot(density(dane_normalne), 
     main = "Estymator jądrowy - Normalny", 
     lwd = 2, col = "darkgreen")