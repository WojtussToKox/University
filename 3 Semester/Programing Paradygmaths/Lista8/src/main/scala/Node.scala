sealed trait Node[+T]

case class Const[+T](value: T) extends Node[T]

case class Variable[+T](name: String) extends Node[T]

case class UnaryOp[A, +R](arg: Node[A], op: A => R) extends Node[R]

case class BinaryOp[A, B, +R](left: Node[A], right: Node[B], op: (A, B) => R) extends Node[R]