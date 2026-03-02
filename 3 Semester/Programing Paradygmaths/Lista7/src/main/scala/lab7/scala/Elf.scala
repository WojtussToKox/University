package lab7.scala

class Elf( val name: String) {
  def emptyDishwasher(dishwasher: Dishwasher): Unit = {
    println(s"Elf $name podchodzi do zmywarki #${dishwasher.id} i zaczyna ją opróżniać...")
    dishwasher.unload()
  }
}
