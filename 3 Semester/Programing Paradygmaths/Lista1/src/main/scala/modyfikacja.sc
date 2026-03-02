def zigZag[T](lista: List[T], n: Int): List[T] = {

  def build(forward: Boolean, orgList: List[T], list: List[T], i: Int, result: List[T]): List[T] = {
    if (i > n) then result
    else if (list.isEmpty) then
      build(!forward, orgList, orgList, i + 1, result)
    else if (forward) then
      build(forward, orgList, list.tail, i, result :+ list.head)
    else
      build(forward, orgList, list.init, i, result :+ list.last)
  }

  build(true, lista, lista, 1, Nil)
}

val lista = List(1,2,3)

zigZag(lista, 5)