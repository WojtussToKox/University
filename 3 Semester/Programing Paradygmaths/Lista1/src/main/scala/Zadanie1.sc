val krotka = ((1.3, 2.0), (3.1, 4.2))

def fiddle22(tuple: ((Double, Double), (Double, Double))) : ((Double, Double),(Double, Double)) = {
  val ((x1, x2), (x3, x4)) = tuple
  ((x4, x1), (x2, x3))
}

fiddle22(krotka)