
## 1:4 === 1, 2, 3, 4
## obiekt <- c(elementy)
a <- c(1, 4, 6, 13, -10, 8)
a

## obiekt <- seq(od, do, by=(co ile), length.out=(ile elementow))
b <- seq(1,101,2)
b

## powielanie === rep(obiekt, times/each (ilokrotnie powielimy dany obiekt lub ilukrotnie jego elementy))
c <- rep(c(4,7,9), each = 3)
c

d <- c("czy", "to", "jest", "wektor", NA)
d
e <- c("czy", "to", "jest", "wektor", "NA")
e

f <- rep(c(4,7,9), times = 6)
f

info <- function(x){
  c(length(x), typeof(x), min(x), max(x))
}


"DŁUGOŚĆ, TYP, MIN, MAX" 
info(a)
info(b)
info(c)
info(d)
info(e)
info(f)

d
sort(d) ##?? Przy sortowaniu zjada nam wartość null LOOL
d <- sort(d)
d
e <- sort(e)
e

A_plus_F <- a + f
A_plus_F

A_razy_F <- a * f
A_razy_F

A_plus_C <- a + c
A_plus_C

A_plus_10 <- a + 10
A_plus_10

A_razy_15 <- a * 15
A_razy_15

n_ty_element <- b[26]
n_ty_element

od_do_wektora <- f[6:10]
od_do_wektora

wieksze_od_bool <- b>50

wieksze_od <- b[b>50]
wieksze_od

ktore_indexy_wieksze <- which(b>50)
ktore_indexy_wieksze

ile_wiekszych <- sum(wieksze_od_bool)


## matrix(dane, nrow, ncol)
M_A <- matrix(c(3,4,1,5,2,3), 2)
M_A


pom1_B <- c(-1, 3, -5)
pom2_B <- c(2, -4, 6)

M_B <- cbind(pom1_B, pom2_B)
M_A

M_pom1C <- matrix(c(7,3), ncol=2)
M_pom2C <- matrix(c(2,1), nrow=1)

M_C <- rbind(M_pom1C, M_pom2C)
M_C

M_D <- matrix(c(1,3,5,2,5,7,4,7,11), 3)
M_D

##M_A_plus_B <- M_A + M_B
##M_A_plus_B

M_A_plus_BT <- M_A + t(M_B)
M_A_plus_BT


M_A_iloczyn_B <- M_A %*% M_B
M_A_iloczyn_B

M_A_razy_A <- M_A * M_A
M_A_razy_A

M_D_Odwrotna <- solve(M_D)
M_D_Odwrotna

M_D_iloczyn_Do <- M_D %*% M_D_Odwrotna
M_D_iloczyn_Do

## A^-1 * A = Jednostkowa
## CX = A
## C^-1CX = C^-1A
## X = C^-1A

Macierz_przyklad_A <- solve(M_C) %*% M_A
Macierz_przyklad_A

Macierz_przyklad_B <- M_A %*% solve(M_D)
Macierz_przyklad_B