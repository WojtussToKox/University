
val listaPar = List(("a", 1), ("b", 2), ("c", 3), ("d", 4))

def insert[T] (lista:List[(T, Int)], element: T ): List[(T, Int)] = {
  if lista.isEmpty then
    List((element, 1))
  else
    val (head, tail) = (lista.head, lista.tail)
    val (e, licz) = head
    if (e == element)
      (e, licz + 1) :: tail
    else
      head :: insert(tail, element)
}

insert(listaPar, "c")
insert(listaPar, "e")