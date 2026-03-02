set.seed(123)

# a) 5000 realizacji z rozkładu jednostajnego na przedziale [0,1]
wartosc_jednostajny = runif(5000, 0, 1) # (min = 0, max = 1)

# b) 3000 realizacji z rozkładu normalnego 
wartosc_normalny = rnorm(3000, 100, 15) # (srednia = 100, odchylenie = 15)

# c) Estymator gęstości (histogram i estymator jądrowy)
# Wykres dla rozkładu jednostajnego
par(mfrow=c(1,2)) # Ustawienie okna - 1 wiersz 2 kolumny (dwa wykresy obok)
# prob = TRUE (zmiana osi Y na gęstość prawdop., żeby słupki i linia do siebie pasowały)
hist(wartosc_jednostajny, main = "Histogram - rozkład jednostajny", prob = TRUE) # Histogram - zakres na kawałki i pokazuje ile liczb wpadło do danego kawałka
lines(density(wartosc_jednostajny), col = "red", lwd = 2) # estymator - wygładzenie hsitogramu

# Wykres dla rozkładu normalnego
hist(wartosc_normalny, main = " Histogram - rozkład normalny", prob = TRUE)
lines(density(wartosc_normalny), col = "blue", lwd = 2)