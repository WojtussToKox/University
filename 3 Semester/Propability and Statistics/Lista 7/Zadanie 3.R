mieszkania <- read.csv("mieszkania.csv", sep=";", dec=".")

head(mieszkania)

mieszkania$Cena_m2 <- mieszkania$Cena / mieszkania$Metraz


# H_0: Cena za m2 ma rozkład normalny.
# H_1: Cena za m2 nie ma rozkładu normalnego.

# a) Test Shapiro-Wilka dla ceny za m2
shapiro_cena <- shapiro.test(mieszkania$Cena_m2)
print(shapiro_cena)

# Odrzucamy na poziomie istotności 0,1% (p < 0,001). Mamy bardzo mocne dowody przeciwko H_0.
# Oznacza to, cena za m2 nie ma rozkładu normalnego.



# H_0: Metraż mieszkań ma rozkład normalny.
# H_1: Metraż mieszkań nie ma rozkładu normalnego.


# b) Test Shapiro-Wilka dla metrażu
shapiro_metraz <- shapiro.test(mieszkania$Metraz)
print(shapiro_metraz)


# Odrzucamy na poziomie istotności 1% (p < 0,001). Mamy bardzo mocne dowody przeciwko H_0.
# Oznacza to, metraż mieszkań nie ma rozkładu normalnego.