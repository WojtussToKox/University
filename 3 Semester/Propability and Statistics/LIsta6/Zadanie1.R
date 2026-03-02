#H_0: p_1 = p_2 (Prawdopodobieństwo posiadania wyższego wykształcenia jest takie samo dla kobiet i mężczyzn; 
#                 wykształcenie nie zależy od płci).

#H_1: p_1 =/= p_2 (Prawdopodobieństwo różni się pomiędzy grupami; wykształcenie zależy od płci).

# --- DANE ---
n_kobiet <- 520
k_kobiet <- 220 # sukcesy
n_mezczyzn <- 480
k_mezczyzn <- 165 # sukcesy

# --- i) TEST Z DLA PROPORCJI ---
p1 <- k_kobiet / n_kobiet
p2 <- k_mezczyzn / n_mezczyzn
p_pool <- (k_kobiet + k_mezczyzn) / (n_kobiet + n_mezczyzn) # proporcja zbiorcza

# Statystyka Z
Z_stat <- (p1 - p2) / sqrt(p_pool * (1 - p_pool) * (1/n_kobiet + 1/n_mezczyzn))
p_value_z <- 2 * (1 - pnorm(abs(Z_stat))) # test dwustronny

cat("Statystyka Z:", Z_stat, "\n")
cat("P-value:", p_value_z, "\n\n")

# --- ii) POLECENIE prop.test ---
res_prop <- prop.test(x = c(k_kobiet, k_mezczyzn), n = c(n_kobiet, n_mezczyzn), correct = FALSE)
print(res_prop)

# --- iii) & iv) TABLICA ROZDZIELCZA I TESTY CHISQ ORAZ FISHERA ---
# Tworzymy tablicę: Wiersze (Płeć), Kolumny (Wykształcenie: 0-nie, 1-tak)
# Kobiety: 220 tak, 300 nie (bo 520-220)
# Mężczyźni: 165 tak, 315 nie (bo 480-165)

dane_tablica <- matrix(c(300, 220, 315, 165), nrow = 2, byrow = TRUE)
rownames(dane_tablica) <- c("Kobieta", "Mężczyzna")
colnames(dane_tablica) <- c("Brak wyższego (0)", "Wyższe (1)")

print("--- TABLICA ROZDZIELCZA ---")
print(dane_tablica)

# Test Chi-kwadrat
print(chisq.test(dane_tablica))

# Test Fishera
print(fisher.test(dane_tablica))

#Decyzja: Odrzucamy hipotezę zerową H_0 na poziomie istotności 5%.
#Interpretacja: Mamy dowody przeciwko H_0. 
#Oznacza to, że statystycznie rzecz biorąc, wykształcenie zależy od płci 
#(w tej próbie odsetek kobiet z wyższym wykształceniem jest istotnie wyższy).




#H_0: sr1 = sr2 (Średni wzrost kobiet i mężczyzn jest taki sam).
#H_1: sr1 =/= sr2 (Średni wzrost różni się w zależności od płci).

# --- DANE ---
n1 <- 520; m1 <- 166; s2_1 <- 100
n2 <- 480; m2 <- 174; s2_2 <- 121

# --- TEST Z DLA ŚREDNICH ---
# Obliczenie błędu standardowego różnicy
se <- sqrt(s2_1/n1 + s2_2/n2)

# Statystyka Z
Z_stat_wzrost <- (m1 - m2) / se
p_value_wzrost <- 2 * (1 - pnorm(abs(Z_stat_wzrost)))

cat("--- WYNIKI TESTU Z (WZROST) ---\n")
cat("Statystyka Z:", Z_stat_wzrost, "\n")
cat("P-value:", p_value_wzrost, "\n")

#Decyzja: Odrzucamy hipotezę zerową H_0 na poziomie istotności 0,1%.
#Interpretacja: Mamy bardzo mocne dowody przeciwko H_0. Średni wzrost istotnie zależy od płci.

