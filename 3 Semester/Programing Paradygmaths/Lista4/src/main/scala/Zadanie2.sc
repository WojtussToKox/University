
sealed trait ProductUnit
case object Kilogram extends ProductUnit
case object Piece extends ProductUnit


case class Product(
                    code: String,
                    name: String,
                    price: Double,
                    unit: ProductUnit
                  )


type ProductDataBase = List[Product]
type ReceiptItem = (String, Double)
type FullReceipt = List[ReceiptItem]
type ReceiptDataBase = List[FullReceipt]



def findProduct(code: String, dataBase: ProductDataBase): Option[Product] = {
  dataBase.find(product => product.code == code)
}


def formatUnit(unit: ProductUnit): String = {
  unit match {
    case Kilogram => "per Kilo"
    case Piece    => "per Piece"
  }
}

def prettyPrint(receipt: FullReceipt, dataBase: ProductDataBase): List[(String, String, Double, Double, Double)] = {


  receipt.flatMap { case (code, quantity) =>

    val productOption = findProduct(code, dataBase)

    productOption match {
      case None => None

      case Some(product) =>
        val name = product.name
        val price = product.price
        val unitInfo = formatUnit(product.unit)
        val totalValue = price * quantity

        Some((name, unitInfo, quantity, price, totalValue))
    }
  }
}

val test_db: ProductDataBase = List(
  Product("101", "Banan", 4.50, Kilogram),
  Product("202", "Czekolada", 5.25, Piece),
  Product("303", "Chleb", 3.80, Piece)
)

val test_paragon_1: FullReceipt = List(
  ("101", 1.5),
  ("202", 3.0),
  ("999", 1.0)
)

val test_paragon_2: FullReceipt = List()

val test_paragon_3: FullReceipt = List(("303", 2.0))

val pusta_baza: ProductDataBase = List()


val wynik1 = prettyPrint(test_paragon_1, test_db)
val wynik2 = prettyPrint(test_paragon_2, test_db)
val wynik3 = prettyPrint(test_paragon_3, pusta_baza)
