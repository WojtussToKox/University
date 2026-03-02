
a <- seq(300,0,-3)
a
# wektory musza miec taki sam typ danych wiec tutaj jest lista
b <- list("one", "two", "three", "four", 5)
b

c <- c("one", "two", "three", "four", "5")
c

pom <- c(3,1,6)
d <- rep(pom, times = 4)
d

e <- rep(pom, each = 4)
e

f <- c(5,1,4,7)
f

"DŁUGOŚĆ, TYP, MIN, MAX, SUMA" 
info <- function(x){
  c(length(x), typeof(x), min(x), max(x), sum(x))
}

info(a)
#info(b)
#info(c)
info(d)
info(e)
info(f)

#b <- sort(b)
#b
e <- sort(e)
e

D_plus_F <- d + f
D_plus_F

d
e
d*e
iloczyn_skalarny <- sum(d*e)
iloczyn_skalarny

n_element <- a[35]
n_element

od_do <- a[67:85]
od_do

mniejsze_od_100_bool <- a<100
mniejsze_od_100_bool

mniejsze_od_100 <- a[a<100]
mniejsze_od_100

ktore_indexy <- which(a<100)
ktore_indexy

## matrix(dane, nrow, ncol)
M_A <- matrix(c(-3,4,1,-5,-2,3), 2)
M_A


pom1_B <- c(1, 3, 5)
pom2_B <- c(2, -4, 6)

M_B <- cbind(pom1_B, pom2_B)
M_B

M_pom1C <- matrix(c(7,-3), ncol=2)
M_pom2C <- matrix(c(-2,1), nrow=1)

M_C <- rbind(M_pom1C, M_pom2C)
M_C

M_D <- matrix(c(1,3,5,2,5,3,4,7,2), 3)
M_D


##M_A_plus_B <- M_A + M_B
##M_A_plus_B

M_AT_plus_B <- t(M_A) + M_B
M_AT_plus_B


M_B_iloczyn_A <- M_B %*% M_A
M_B_iloczyn_A

M_B_razy_B <- M_B * M_B
M_B_razy_B

M_C_Odwrotna <- solve(M_C)
M_C_Odwrotna

M_C_iloczyn_Co <- M_C %*% M_C_Odwrotna
M_C_iloczyn_Co


## A^-1 * A = Jednostkowa
## XC = B
## XCC^-1 = BC^-1
## X = BC^-1

Macierz_przyklad_A <- M_B %*% solve(M_C)  
Macierz_przyklad_A

Macierz_przyklad_B <- solve(M_D) %*% M_B  
Macierz_przyklad_B