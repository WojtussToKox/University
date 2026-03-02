set.seed(123)

# Optymalizacja - działamy na całych wektorach
generuj_dyskretne_opt = function(n) {
  u = runif(n)       # Losujemy n liczb z rozkładu jednostajnego U[0,1]
  wyniki = numeric(n) # Tworzymy wektor o dłgości n
  
  
  wyniki[u < 0.5] = 2 
  wyniki[u >= 0.5 & u < 0.75] = 1 
  wyniki[u >= 0.75 & u < 0.9] = 0 
  wyniki[u >= 0.9] = 3 
  
  return(wyniki)
}

dyskretne_losowe = generuj_dyskretne_opt(1000)

tabela_empiryczna = table(dyskretne_losowe) / 1000

print("Wyniki symulacji:")
print(tabela_empiryczna)

print("Wartości teoretyczne:")
print(c("0"=0.15, "1"=0.25, "2"=0.50, "3"=0.10))