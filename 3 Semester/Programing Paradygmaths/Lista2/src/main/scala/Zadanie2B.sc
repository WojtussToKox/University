import scala.annotation.tailrec

def splitNTailRec[A](list: List[A], n: Int): List[List[A]] = {
  if (n <= 0) throw new IllegalArgumentException("N must be greater than 0")

  @tailrec
  def createEmptyLists(nLists: Int, acc: List[List[A]]): List[List[A]] =
    if (nLists == 0) acc else createEmptyLists(nLists - 1, Nil :: acc)

  val initialLists = createEmptyLists(n, Nil)

  @tailrec
  def split(remainingList: List[A], acc: List[List[A]], currentIndex: Int): List[List[A]] = {
    remainingList match {
      case Nil => acc

      case h :: t =>
        val nextIndex = (currentIndex + 1) % n

        val newAcc = acc.zipWithIndex.map {
          case (subList, index) if index == currentIndex => h :: subList // Dodaj element na głowę podlisty
          case (subList, _) => subList // Pozostaw inne podlisty bez zmian
        }
        split(t, newAcc, nextIndex)
    }
  }
  split(list, initialLists, 0)
}

val test = List(0,1,2,3,4,5,6,7,8,9,10,11,12,13)

splitNTailRec(test, 4)
