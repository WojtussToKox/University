val lista1 = List(1,1,1,1,1,1,1,1,1,1,1,1,1,1,1)
val lista2 = List(1,2,1,2,2,2,2,1,2,2,2,1,1,1)

def hits[T](l1:List[T], l2:List[T], index: Int = 0) : List[Int] = {
  if (l1.isEmpty | l2.isEmpty) then Nil
  else
    val h1 = l1.head
    val h2 = l2.head
    val t1 = l1.tail
    val t2 = l2.tail

    val result = hits(t1, t2, index + 1)

    if (h1 == h2) then index :: result else result
}

hits(lista1, lista2)