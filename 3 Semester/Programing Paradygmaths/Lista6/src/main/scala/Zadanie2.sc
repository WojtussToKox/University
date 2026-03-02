def pascalGiftI(n: Int, r: Int): Array[Int] = {
  val arr = Array.fill(n)(1)
  var i = 1
  while (i <= r) {
    var j = 1
    while (j < n) {
      arr(j) = arr(j) + arr(j - 1)
      j += 1
    }
    i += 1
  }
  arr
}


pascalGiftI(5, 0)
pascalGiftI(3, 1)
pascalGiftI(4, 2)
pascalGiftI(4, 3)