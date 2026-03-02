import scala.annotation.tailrec

def splitNTailRec[A](list: List[A], n: Int): List[List[A]] = {
  if (n <= 0) throw new IllegalArgumentException("N must be greater than 0")

  // tworzy n pustych list
  @tailrec
  def createEmptyLists(nLists: Int, acc: List[List[A]]): List[List[A]] =
    if (nLists == 0) acc else createEmptyLists(nLists - 1, Nil :: acc)

  val initialLists = createEmptyLists(n, Nil)

  // dodaje element do listy o indeksie wantedIndex
  @tailrec
  def findSubListAndAdd(acc: List[List[A]], wantedIndex: Int, value: A, pos: Int ,newAcc: List[List[A]]): List[List[A]] = {
    acc match {
      // BEZ UZYCIA REVERSE TUTAJ SIE TAK SYPIE PROGRAM ZE NIE MAM POJECIA O CO CHODZI
      case Nil => newAcc
      case h :: t =>
        if (pos == wantedIndex)
          findSubListAndAdd(t, wantedIndex, value, pos + 1, (value :: h) :: newAcc)
        else
          findSubListAndAdd(t, wantedIndex, value, pos + 1, h :: newAcc)
    }
  }

  // główna funkcja dzieląca listę na n podlist
  @tailrec
  def split(remainingList: List[A], acc: List[List[A]], currentIndex: Int): List[List[A]] = {
    remainingList match {
      case Nil => acc
      case h :: t =>

        val nextIndex = (currentIndex + 1) % n
        split(t, findSubListAndAdd(acc, currentIndex, h, 0, Nil), nextIndex)
    }
  }

  split(list, initialLists, 0)
}

val test = List(0,1,2,3,4,5,6,7,8,9,10,11,12,13)
println(splitNTailRec(test, 5))