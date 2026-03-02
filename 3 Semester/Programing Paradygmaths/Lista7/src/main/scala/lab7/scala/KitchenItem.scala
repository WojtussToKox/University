package lab7.scala

import lab7.java.IVisitor

trait KitchenItem {
  def toString: String
  def accept(v: IVisitor): Unit
}
