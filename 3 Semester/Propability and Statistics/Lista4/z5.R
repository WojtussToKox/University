set.seed(123)

# a) i) Algorytm (funkcja)
# losuje realizację z tego rozkładu za pomocą metody odwracania dystrybuanty

odwr_gen = function(n) {
  u = runif(n) # losowanie wartości dystryb. z rozkładu jednostajnego
  x = 2 * sqrt(u) # przekształcenie odwrotne: F(x)= u = 0.25 x^2 -> x = 2 sqrt(u)
  return(x)
}

# ii) Wygenerowanie 200 realizacji
realizacje_a = odwr_gen(200)

# b)
przyj_odrz_gen = function(n) {
  zaakceptowane = numeric(n) # wektor na wyniki
  licznik = 0
  
  # Dopóki nie mamy n zaakceptowanych liczb
  while(licznik < n) {
    x_prop = runif(1, 0, 2) # Losowa pozycja na osi X (od 0 do 2)
    y_test = runif(1, 0, 1) # Losowa wysokość (od 0 do 1)
    
    # Warunek akceptacji
    # Sprawdzamy czy punkt (x,y) jest pod krzywą g(x) = 0.5x
    if (y_test <= 0.5 * x_prop) {
      licznik = licznik + 1
      zaakceptowane[licznik] = x_prop
    }
  }
  return(zaakceptowane)
}

# ii) Wygenerowanie 200 realizacji
realizacje_b = przyj_odrz_gen(200)
