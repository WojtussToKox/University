
bakteria <- read.csv("bakteria.csv", sep=";", dec=",")

head(bakteria)

plot(bakteria$czas, bakteria$masa,
     main = "Wzrost masy bakterii w czasie",
     xlab = "Czas (t)",
     ylab = "Masa bakterii (Y)",
     pch = 19,       # Pełne kółka
     col = "blue",   # Kolor punktów
     las = 1         # Poziome etykiety osi Y
)
grid()


# Aby sprowadzić model wykładniczy Y = a * e^(bt) do liniowego,
# logarytmujemy go stronami: ln(Y) = ln(a) + b * t




bakteria$log_masa <- log(bakteria$masa)

model_log <- lm(log_masa ~ czas, data = bakteria)

print(summary(model_log))

# Dodanie krzywej regresji do wykresu (wizualizacja modelu)
czas_seq <- seq(min(bakteria$czas), max(bakteria$czas), length.out=100)
masa_pred_smooth <- exp(predict(model_log, newdata=data.frame(czas=czas_seq)))
lines(czas_seq, masa_pred_smooth, col="red", lwd=2)
legend("topleft", legend=c("Dane", "Model wykładniczy"), 
       col=c("blue", "red"), pch=c(19, NA), lty=c(NA, 1), lwd=c(NA,2))


# Przykład: Oszacujmy masę dla czasu t = 11 (poza zakresem danych)

nowe_dane <- data.frame(czas = 11)
nowe_dane
prognoza_log <- predict(model_log, newdata = nowe_dane)

# Przekształcamy wynik funkcją wykładniczą (exp), aby wrócić do masy
prognoza_masa <- exp(prognoza_log)

cat("Dla czasu t = 11, przewidywana masa bakterii wynosi:", round(prognoza_masa, 3), "\n")
