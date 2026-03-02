import scala.annotation.tailrec

@tailrec
def createEmptyLists(nLists: Int, acc: List[List[Int]]): List[List[Int]] =
  if (nLists == 0) acc else createEmptyLists(nLists - 1, (List(nLists)) :: acc)

createEmptyLists(5, Nil)