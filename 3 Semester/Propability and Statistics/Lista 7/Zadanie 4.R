mieszkania <- read.csv("mieszkania.csv", sep=";")


head(mieszkania)

model_mieszkania <- lm(Cena ~ Metraz, data = mieszkania)

print(summary(model_mieszkania))

wspolczynniki <- coef(model_mieszkania)
cat("Cena =", round(wspolczynniki[1], 2), "+", round(wspolczynniki[2], 2), "* Metraż\n")


plot(mieszkania$Metraz, mieszkania$Cena,
     main = "Cena mieszkania w zależności od metrażu",
     xlab = "Metraż [m2]",
     ylab = "Cena [PLN]",
     pch = 19,       # Pełne kółka
     col = "blue",   # Kolor punktów
     las = 1         # Poziome etykiety osi Y
)
# Dodanie linii regresji do wykresu
abline(model_mieszkania, col = "red", lwd = 2)
grid()


# Reszty to różnice między ceną rzeczywistą a przewidywaną przez model.
reszty <- residuals(model_mieszkania)

# H_0: Reszty mieszkań maja rozkład normalny.
# H_1: Reszty mieszkań nie maja rozkładu normalnego.


test_shapiro <- shapiro.test(reszty)

print(test_shapiro)

# Odrzucamy na poziomie istotności 1% (p < 0,001). Mamy bardzo mocne dowody przeciwko H_0.
# Oznacza to, reszty mieszkań nie maja rozkładu normalnego.


nowe_dane <- data.frame(Metraz = 80)
prognoza <- predict(model_mieszkania, newdata = nowe_dane)

round(prognoza, 3)
