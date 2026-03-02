import scala.annotation.tailrec

def findTail[A](list: List[A])(value: A): List[Int] = {
  @tailrec
  def findRec(currentList: List[A], index: Int, acc: List[Int]): List[Int] = {
    currentList match {
      case Nil => acc //acc.reverse zwroci rosnaca bo tak to dodajemy na poczatek tego co juz znalezlismy
      case head :: tail if head == value =>
        findRec(tail, index + 1, index :: acc)
      case _ :: tail =>
        findRec(tail, index + 1, acc)
    }
  }
  findRec(list, 0, Nil)
}

def find[A](list: List[A])(value: A): List[Int] = {
  def findRec(currentList: List[A], index: Int): List[Int] = {
    currentList match {
      case Nil => Nil
      case head :: tail if head == value =>
        index :: findRec(tail, index + 1)
      case _ :: tail =>
        findRec(tail, index + 1)
    }
  }
  findRec(list, 0)
}

val testList = List(1, 2, 3, 1, 5, 3)
val testList2 = List(1, 2, 3, 3, 2, 1)
val testList3 = List("A", "B", "C", "B", "B")

val findInNumbersTail: Int => List[Int] = findTail(testList)
val findInNumbers: Int => List[Int] = find(testList)
val findIn123Tail: Int => List[Int] = findTail(testList2)
val findIn123: Int => List[Int] = find(testList2)
val findInLettersTail: String => List[Int] = findTail(testList3)
val findInLetters: String => List[Int] = find(testList3)

findInNumbersTail(3)
findIn123Tail(3)
findInLettersTail("B")
findInNumbers(3)
findIn123(3)
findInLetters("B")