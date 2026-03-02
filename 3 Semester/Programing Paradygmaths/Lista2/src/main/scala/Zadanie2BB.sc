import scala.annotation.tailrec

def splitNTailRec[A](list: List[A], n: Int): List[List[A]] = {
  if (n <= 0) throw new IllegalArgumentException("N must be greater than 0")

  @tailrec
  def createEmptyLists(nLists: Int, acc: List[List[A]]): List[List[A]] =
    if (nLists == 0) acc else createEmptyLists(nLists - 1, Nil :: acc)

  val initialLists = createEmptyLists(n, Nil)

  def addToList(actListIndex: Int, inputLists: List[List[A]], element: A, currentIndex: Int): List[List[A]] =
    inputLists match {
      case Nil => Nil
      case h_list :: t_lists =>
        val restOfLists = addToList(actListIndex + 1, t_lists, element, currentIndex)
        if (actListIndex == currentIndex) {
          (element :: h_list) :: restOfLists
        } else {
          h_list :: restOfLists
        }
    }

  @tailrec
  def split(remainingList: List[A], acc: List[List[A]], currentIndex: Int): List[List[A]] = {
    remainingList match {
      case Nil => acc
      case h :: t =>
        val newAcc = addToList(0, acc, h, currentIndex)
        val nextIndex = (currentIndex + 1) % n
        split(t, newAcc, nextIndex)
    }
  }
  split(list, initialLists, 0)
}

val test = List(0,1,2,3,4,5,6,7,8,9,10,11,12)

splitNTailRec(test, 4)
