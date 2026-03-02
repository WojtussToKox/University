set.seed(2137)

# --- i) Metoda odwracania dystrybuanty ---
# Wzór analityczny: x = 2 * sqrt(u)

generuj_odwracanie <- function(n) {
  u <- runif(n)      
  x <- 2 * sqrt(u)  #Podstaw do funkcji odwrotnej
  return(x)
}

# Generowanie 200 realizacji
dane_odwracanie <- generuj_odwracanie(200)

# Weryfikacja (opcjonalnie)
hist(dane_odwracanie, freq=FALSE, main="Metoda Odwracania Dystrybuanty")
curve(0.5*x, add=TRUE, col="red", lwd=2)


# ) Własny algorytm (pojedyncza realizacja)
generuj_przez_akceptacje <- function() {
  while(TRUE) {
    kandydat_x <- runif(1, min = 0, max = 2) # Losowa współrzędna X
    test_y <- runif(1, min = 0, max = 1)     # Losowa współrzędna Y (poziom)
    
    gestosc_w_punkcie <- 0.5 * kandydat_x
    
    # Warunek akceptacji: czy punkt trafił pod wykres?
    if (test_y <= gestosc_w_punkcie) {
      return(kandydat_x)
    }
    # Jeśli nie, pętla while powtarza proces
  }
}

# ii) Generowanie 200 realizacji

dane_akceptacja <- numeric(200)

for(i in 1:liczba) {
  dane_akceptacja[i] <- generuj_przez_akceptacje()
}

# Wykres weryfikujący
hist(dane_akceptacja, freq=FALSE, breaks=15, 
     main="Metoda Przyjęcia i Odrzucenia", col="lavender")
curve(0.5*x, add=TRUE, col="red", lwd=2)