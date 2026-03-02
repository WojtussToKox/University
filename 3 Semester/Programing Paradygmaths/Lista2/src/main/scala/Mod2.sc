import scala.annotation.tailrec

def splitNRec[A](list: List[A], a: Int, b: Int): List[A] = {

  def builder(list: List[A], actIndex: Int, result: List[A]): List[A] =
  list match {
    case Nil => result

    case head :: tail =>
      if (actIndex < a) then {
        head :: builder(tail, actIndex + 1, result)
      } else if (actIndex >= a && actIndex <= b) then {
        builder(tail, actIndex + 1, head :: result)
      } else {
        result ::: (head :: tail)
      }
  }
  
    builder(list, 0, Nil)

}

val test = List(1,2,3,4,5,6,7,8,9)

splitNRec(test, 2, 4)

// now output val res0: List[Int] = List(1, 2, 6, 7, 8, 9, 5, 4, 3)
// proper outpuy val res0: List[Int] = List(1, 2, 5, 4, 3, 6, 7, 8, 9)