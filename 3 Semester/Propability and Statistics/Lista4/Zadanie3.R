set.seed(2137)

generuj_z_rozkladu_dyskretnego <- function() {
  u <- runif(1)
  
  # Sprawdzamy od największego prawdopodobieństwa (k=2, p=0.5)
  if (u < 0.5) {
    return(2)      
  } else if (u < 0.75) { 
    return(1)       # P=0.25 (przedział [0.5, 0.75))
  } else if (u < 0.9) {
    return(0)       # P=0.15 (przedział [0.75, 0.90))
  } else {
    return(3)       # P=0.10 (reszta)
  }
}

# Generowanie 1000 liczb
liczba_generacji <- 1000
wyniki_dyskretne <- numeric(liczba_generacji)

for(i in 1:liczba_generacji) {
  wyniki_dyskretne[i] <- generuj_z_rozkladu_dyskretnego()
}

# Weryfikacja (proporcje powinny być bliskie zadanym prawdopodobieństwom)
prop.table(table(wyniki_dyskretne))
