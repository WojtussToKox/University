# Dane
n = 100 # Liczebność próby
x_bar = 109 # Średnia z próby
s2 = 225 # Wariancja z próby
s = sqrt(s2) # Odchylenie standardowe
k = 30 # Liczba osob z IQ > 115

# ===== A =====
# i) (H0: p =0.35, H1: p != 0.35)
p0 = 0.35
p_hat = k/n # Proporcja z próby

Z = (p_hat - p0) / sqrt((p0 * (1-p0)) / n) # Statystyka Z
p_val_Z = 2 * (1 - pnorm(abs(Z))) # p-value

cat ("Test Z: Statystyka Z = ", Z, "p-wartość =", p_val_Z, "\n" )

# ii)
prop.test(k, n, p = 0.35, alternative = "two.sided", correct = FALSE)

# Skoro p > 0.05, nie ma podstaw do odrzucenia H0. Oznacza to, że 
# różnica między frakcją w próbie (30%) a wartością zakładaną (35%) nie jest istotna statystycznie.

# ===== B =====
# i)
alpha_b = 0.01 # Poziom istotności (1 - poziom ufnosci)
z_kryt = qnorm(1 - alpha_b/2) # Wartość krytyczna
margin = z_kryt * sqrt((p_hat * (1 - p_hat)) / n) # Margines błędu
ci_norm = c(p_hat - margin, p_hat + margin) # Konstrukcja przedziału
cat("CI (Normal):", ci_norm, "\n")

# ii)
prop.test(k, n, conf.level = 0.99)$conf.int

# Z 99% ufnością szacujemy, że rzeczywisty odsetek studentów z IQ 
# wyższym niż 115 mieści się w przedziale (19,3%, 43,3%)

# ===== C =====
alpha_c = 0.10 # 1 - poziom ufności
z_kryt_c = qnorm(1 - alpha_c/2) # Wartość krytyczna
margin_c = z_kryt_c * (s / sqrt(n)) # Margines błędu = Z_kryt * SEM(błąd stand.)
ci_mean_norm = c(x_bar - margin_c, x_bar + margin_c) # Konstrukcja przedziału
cat("CI dla średniej (Normal 90%):", ci_mean_norm, "\n")
# Z 90% ufnością możemy stwierdzić, że średnie IQ 
# zawiera się w przedziale od (106,5, 111,5)

# ===== D =====
t_kryt = qt(1 - alpha_c/2, df = n - 1) # Wartość krytyczna (t-studenta)
margin_d = t_kryt * (s / sqrt(n)) # Margines błędu
ci_mean_t = c(x_bar - margin_d, x_bar + margin_d) # Konstrukcja przedziału
cat("CI dla średniej (t-Student 90%):", ci_mean_t, "\n")
# Z 90% ufnością średnie IQ 
# studentów mieści się w przedziale (106,5, 111,5)


# ===== E =====
# H0: mu = 115
# H1: mu != 115

mu0 = 115 # Wartość testowana

# i)
Z_mean = (x_bar - mu0) / (s / sqrt(n)) # Statystyka Z
p_val_Z_mean = 2 * (1 - pnorm(abs(Z_mean))) # p-value
cat("Test Z dla średniej: Z =", Z_mean, "p-wartość =", p_val_Z_mean, "\n")

# ii)
T_stat = (x_bar - mu0) / (s / sqrt(n)) # Statystyka T
p_val_T = 2 * (1 - pt(abs(T_stat), df = n - 1)) # p-value
cat("Test T dla średniej: T =", T_stat, "p-wartość =", p_val_T, "\n")

# Wniosek:
# Skoro p < 0.05, odrzucamy H0 i przyjmujemy H1. Mamy bardzo silne dowody 
# statystyczne na to, że średnie IQ studentów istotnie różni się od 115.