package lab7.scala

import lab7.java.IVisitor

case class Plate(diameter: Double) extends KitchenItem {

  override def toString: String = s"Talerz (średnica: $diameter cm)"

  override def accept(v: IVisitor): Unit = {
    v.visit(this)
  }
}
