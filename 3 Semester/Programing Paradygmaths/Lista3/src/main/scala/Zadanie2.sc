def coPrimes(a: Int, n: Int): List[Int] = {
  def areCoprime(num1: Int, num2: Int): Boolean = {
    // 1 jest względnie pierwsza z każdą liczbą
    if (num1 == 1 || num2 == 1) {
      true
    } else {
      val limit = if (num1 < num2) num1 else num2

      val commonDivisors = for {
        i <- List.range(2, limit + 1)
        if num1 % i == 0 && num2 % i == 0
      } yield i

      commonDivisors.isEmpty
    }
  }
  val x = if (a >= 0) then a else -a
  val result = for {
    b <- List.range(1, n + 1)
    if areCoprime(x, b)
  } yield b

  result
}

val test = coPrimes(10,10)
val test2 = coPrimes(-2,10)
val test3 = coPrimes(2,10)
val test4 = coPrimes(0,10)
val test5 = coPrimes(1,10)