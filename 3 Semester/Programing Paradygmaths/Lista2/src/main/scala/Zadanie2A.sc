import scala.annotation.tailrec

def splitNRec[A](list: List[A], n: Int): List[List[A]] = {
  if (n <= 0) throw new IllegalArgumentException("N must be greater than 0")

  // stworz n pustych list
  def createEmptyLists(nLists: Int): List[List[A]] =
    if (nLists == 0) Nil else Nil :: createEmptyLists(nLists - 1)


  def addToList(actListIndex: Int, inputLists: List[List[A]], element: A, currentIndex: Int): List[List[A]] =
    inputLists match {
      //gdy dojdziemy na koniec wyjdz z rekurencji
      case Nil => Nil

      case h_list :: t_lists =>
        // wchodzimy do konca listyList i szukamy indexu do ktorego ma trafic element
        val restOfLists = addToList(actListIndex + 1, t_lists, element, currentIndex) 
        // jezeli znaleziono doloz go do listy i doklej pozostale listy
        if (actListIndex == currentIndex) {
          (element :: h_list) :: restOfLists
        } else {
          h_list :: restOfLists
        }
    }
  // Najpierw podziel na elementy, i gdy nie bedzie juz zadnej listy
  // Czyli beda same elementy stworz mi puste listy
  def split(listToSplit: List[A], nTotal: Int, currentIndex: Int): List[List[A]] = {
    listToSplit match {
      case Nil => createEmptyLists(nTotal)

      case h :: t =>
        val nextIndex = (currentIndex + 1) % nTotal
        // przy dzieleniu na elementy przekaz do ktorego indexu listy ma trafic dany element
        val subLists = split(t, nTotal, nextIndex)
        // zacznij od subLists[0] i dodaj glowe pozostalej listy na dany index
        addToList(0, subLists, h, currentIndex)
    }
  }

  split(list, n, 0)
}

val test = List(0,1,2,3,4,5,6,7,8,9,10,11,12,13)

splitNRec(test, 4)