set.seed(2137)

# i) 100 realizacji z rozkładu Bin(10; 0,3)
# Wynik to ilość sukcesów w 10 próbach
bin = rbinom(100, 10, 0.3) # 100 eksperymentów x 10 rzutów x 0.3 prawdop.
print(table(bin))

# ii) 50 realizacji z rozkładu Geom(0,4)
# Wynik to ilosc porazek przed sukcesem
geom = rgeom(50, 0.4) # 50 realizacji x 0.4 prawdop.
print(table(geom))