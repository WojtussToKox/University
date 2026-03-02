package lab7.scala

import lab7.java.IVisitor

case class Spoon(length: Double) extends Cutlery {

  override def toString: String = s"Łyżka (długość: $length cm)"
  
  override def accept(v: IVisitor): Unit = {
    v.visit(this)
  }
}
