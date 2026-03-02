
?read.csv

waga_dane <- read.csv("waga1.csv", header = TRUE, sep = ";")
waga_dane



head(waga_dane, 5)


str(waga_dane)



sredni_wzrost <- mean(waga_dane$Wzrost)
sredni_wzrost

srednia_waga_przed <- mean(waga_dane$Waga_przed)
srednia_waga_przed



wzrost_metry <- waga_dane$Wzrost / 100

waga_dane$Wskaznik_BMI <- (waga_dane$Waga_przed / (wzrost_metry)^2)

head(waga_dane)




waga_kobiety_wysokie_bmi <- subset(waga_dane, plec == 1 & Wskaznik_BMI > 25)
waga_kobiety_wysokie_bmi



waga_mezczyzni <- subset(waga_dane, plec == 0)
waga_mezczyzni

ile_a <- subset(waga_dane, Wzrost > 175)
ile_aaaa <- nrow(ile_a)
ile_aaaa

ile_wyzszych_niż_175 <- sum(waga_dane$Wzrost > 175)
ile_wyzszych_niż_175
