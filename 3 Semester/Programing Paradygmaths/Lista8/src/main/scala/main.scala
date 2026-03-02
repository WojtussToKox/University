import ExpressionEvaluator._

object main extends App {

  // Proste dodawanie (5 + x)
  val tree1 = BinaryOp(
    Const(5),
    Variable[Int]("x"),
    (a: Int, b: Int) => a + b
  )
  val vars1 = Map("x" -> 10)
  println(s"Test 1 (5 + x): ${evaluate(tree1, vars1)}")


  // Mieszanie typów (Int + String)
  val treeMixed = BinaryOp(
    Const(5),
    Const("Kot"),
    (a: Int, b: String) => a.toString + b
  )
  println(s"Test 2 (5 + 'Kot'): ${evaluate(treeMixed, Map())}")


  // --- Test 3: Logika (czy wynik mnożenia > 10) ---
  val multiplication = BinaryOp(
    Variable[Int]("x"),
    Variable[Int]("y"),
    (a: Int, b: Int) => a * b
  )
  val logicTree = UnaryOp(
    multiplication,
    (res: Int) => res > 10
  )
  val vars3 = Map("x" -> 3, "y" -> 4)
  println(s"Test 3 (x*y > 10)?: ${evaluate(logicTree, vars3)}")

}