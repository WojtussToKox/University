dane = read.csv2("waga1.csv")

# === Z2 ===
# H0: średni wzrost studentów = 170 (mu = 170)
# H1: średni wzrost studentów != 170

t.test(dane$Wzrost, mu = 170, alternative = "two.sided")
# Odrzucamy H0 i przyjmujemy H1. Mamy silne dowody
# na to, że średni wzrost studentów różni się istotnie od 170 cm

# === Z3 ===
# Przedział ufności dla średniego wzrostu (90%)

t.test(dane$Wzrost, conf.level = 0.90)$conf.int

# Z 90% ufnością możemy stwierdzić, że przedział (162.61, 167.17) pokrywa 
# prawdziwą wartość średniego wzrostu populacji studentów.

# === Z4 ===
# H0: średni wzrost studentek = 160 (mu = 160)
# H1: średni wzrost studentek != 160

wzrost_kobiet = dane$Wzrost[dane$plec == 1] # Filtrowanie kobiet
t.test(wzrost_kobiet, mu= 160)
# Nie ma podstaw do odrzucenia H0 - na podstawie danych nie możemy stwierdzić,
# że średni wzrost studentek w próbie istotnie różni się od 160 cm. (p-val = 0.3574)

# === Z5 ===
t.test(wzrost_kobiet, conf.level = 0.98)$conf.int
# Z 98% ufnością możemy stwierdzić, że przedział (154.04, 162.64) pokrywa 
# prawdziwą wartość średniego wzrostu populacji studentek.

# === Z6 ===
# H0: proporcja studentów (mężczyzn) wyższych niż 180cm wynosi 0.25 (p = 0.25)
# H1: proporcja ta jest różna od 0.25 (p != 0.25)

wzrost_mezczyzn = dane$Wzrost[dane$plec == 0]
n_mezczyzn = length(wzrost_mezczyzn)
k_wyzszych = sum(wzrost_mezczyzn > 180)

prop.test(k_wyzszych, n_mezczyzn, p = 0.25)
# Nie ma podstaw do odrzucenia H0. Nie mamy dowodów by twierdzić, że 
# odsetek wysokich studentów rózni sie od 25%

# === Z7 ===
prop.test(k_wyzszych, n_mezczyzn, conf.level = 0.96)$conf.int
# Z 96% ufnością możemy stwierdzić, że rzeczywisty odsetek studentów (mężczyzn)
# o wzroście powyżej 180 cm mieści się w przedziale od 11,2% do 35,8%.
