set.seed(123)

# a) i) Symulacja 600 rzutow przeksztalcajac rozklad jednostajny
#  *6 i zaokraglamy w gore (ceiling) by uzyskać liczby calkowite 1-6
rzuty_a = ceiling(runif(600, 0, 1) * 6) 

# ii) Średnia i wariancja z próby
srednia = mean(rzuty_a)
wariancja = var(rzuty_a)

# iii) Rozkład częstości
rozklad = table(rzuty_a)
print(rozklad)

# Porównanie z dyskretnym rozkładem jednostajnym
roznica = rozklad - 100
print(roznica)


# iv) Przeksztalcenie w ramke danych i wariancja czestosci
ramka = as.data.frame(rozklad)
print(ramka)
wariancja_czestosci = var(ramka$Freq)
print(wariancja_czestosci)

# b) Symulacja za pomocą funkcji sample
# Losowanie ze zwracaniem (replace = TRUE)
rzuty_b = sample(1:6, 600, replace = TRUE)

# rozklad_b = table(rzuty_b)
# print(rozklad_b)

