set.seed(2137)

# --- a) Metoda transformacji (z rozkładu jednostajnego) ---
liczba_rzutow <- 600
wektor_u <- runif(liczba_rzutow)

# Przekształcenie: podłoga(6 * U) + 1 daje liczby {1,2,3,4,5,6}
rzuty_transformacja <- floor(wektor_u * 6) + 1


# Statystyki opisowe
srednia_probkowa <- mean(rzuty_transformacja)
wariancja_probkowa <- var(rzuty_transformacja)

cat("Metoda transformacji:\n")
cat("Średnia z próby:", srednia_probkowa, "(Teoretyczna: 3.5)\n")
cat("Wariancja z próby:", wariancja_probkowa, "(Teoretyczna: 35/12 ≈ 2.917)\n\n")

# Rozkład częstości i ramka danych
tabela_czestosci <- table(rzuty_transformacja)
ramka_czestosci <- as.data.frame(tabela_czestosci)

ramka_czestosci

# Wariancja częstości (wariancja kolumny 'Freq')
wariancja_czestosci <- var(ramka_czestosci$Freq)
cat("\nWariancja częstości wystąpień:", wariancja_czestosci, "\n")

# --- b) Metoda 'sample' (losowanie ze zbioru) ---
rzuty_sample <- sample(1:6, size = 600, replace = TRUE)
cat("Średnia (metoda sample):", mean(rzuty_sample), "\n")

