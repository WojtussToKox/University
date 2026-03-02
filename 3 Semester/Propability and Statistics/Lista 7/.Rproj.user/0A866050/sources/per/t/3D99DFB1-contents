# H_0: P_1 = P_2 = ... = P_6 = 1/6 (Kostka jest symetryczna; rozkład wyników jest jednostajny).
# H_1: Przynajmniej jedno prawdopodobieństwo jest inne (Kostka nie jest symetryczna).

# --- DANE ---
wyniki <- c(1, 2, 3, 4, 5, 6)
frekwencja <- c(171, 200, 168, 213, 226, 222)
n <- sum(frekwencja) 

# Jeśli kostka jest symetryczna, p = 1/6 dla każdej ściany.
oczekiwane <- rep(n / 6, 6) 
print(data.frame(Wynik=wyniki, Obserwowane=frekwencja, Oczekiwane=oczekiwane))


chi_sq_stat <- sum((frekwencja - oczekiwane)^2 / oczekiwane)
cat("Wartość statystyki Chi-kwadrat:", chi_sq_stat, "\n")

# Stopnie swobody df = k - 1 = 6 - 1 = 5
p_val <- 1 - pchisq(chi_sq_stat, df=5)
print(p_val)

test_chi <- chisq.test(frekwencja)
print(test_chi)

# Odrzucamy na poziomie istotności 1% (0,001 < p < 0,01). Mamy mocne dowody przeciwko H_0.
# Oznacza to, kostka jest niesymetryczna (fałszywa).