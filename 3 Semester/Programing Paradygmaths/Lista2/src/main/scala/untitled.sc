import scala.annotation.tailrec

def countInLists[T] (lists: List[List[T]]): List[Int] = {
  @tailrec
  def count(lists: List[List[T]], res: List[Int]): List[Int] =
    lists match {
      case Nil => res.reverse
      case head::tail => count(tail, head.length::res)
    }
  count(lists, Nil)
}

val test = List(List(1,2,3), List(1,1,1,1,1), List(1), List())
countInLists(test)


