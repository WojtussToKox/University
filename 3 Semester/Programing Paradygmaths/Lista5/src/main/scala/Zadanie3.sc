
def permutationsL[A](list: LazyList[A]): LazyList[LazyList[A]] = list match {
  // Permutacja listy pustej to lista zawierająca jedną pustą listę
  case LazyList() => LazyList(LazyList())

  case head #:: tail =>
    for {
      p <- permutationsL(tail)
      n <- 0 to p.length
    } yield {
      val (pre, post) = p.splitAt(n)
      pre #::: (head #:: post)
    }
}

val lista = LazyList(1, 2, 3)
val wynik = permutationsL(lista)
wynik.foreach(permutation => println(permutation.toList))

val test = permutationsL(lista).take(100)
test.foreach(permutation => println(permutation.toList))


val lista2 = LazyList(1, 2, 3, 4)
val wynik2 = permutationsL(lista2).take(2)
wynik2.foreach(permutation => println(permutation.toList))

val lista3 = LazyList()
val wynik3 = permutationsL(lista3)
wynik3.foreach(permutation => println(permutation.toList))
