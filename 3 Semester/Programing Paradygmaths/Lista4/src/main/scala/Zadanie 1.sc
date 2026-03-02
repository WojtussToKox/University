sealed trait LLTree[+T]
case object Empty extends LLTree[Nothing]
case class Leaf[T](value: T) extends LLTree[T]
case class Node[T](value: T, leftChild: LLTree[T], rightChild: LLTree[T]) extends LLTree[T]

def mapLLTree[A, B] (fun: A => B) (tree: LLTree[A]): LLTree[B] = tree match {
  case Empty => Empty
  case Leaf(value) => Leaf(fun(value))
  case Node(value, lChild, rChild) => Node(fun(value), mapLLTree(fun)(lChild), mapLLTree(fun)(rChild))
}

val intToString: Int => String = x => s"val:$x"

val inputTree: LLTree[Int] =
  Node(100,
    Leaf(50),
    Node(25, Leaf(10), Empty)
  )

val test1Result = mapLLTree(intToString)(Empty)
val test2Result = mapLLTree(intToString)(Leaf(42))
val test3Result = mapLLTree(intToString)(inputTree)