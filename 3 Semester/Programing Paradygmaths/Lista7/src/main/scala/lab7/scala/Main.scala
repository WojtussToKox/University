package lab7.scala

import lab7.java.KitchenSorter

import java.util
import java.util.LinkedList

object Main extends App {

  val dirtyItems = new util.LinkedList[KitchenItem]()
  dirtyItems.add(Spoon(10.0))
  dirtyItems.add(Plate(22.5))
  dirtyItems.add(Spoon(12.5))
  dirtyItems.add(Spoon(9.0))
  dirtyItems.add(Plate(18.0))
  dirtyItems.add(Spoon(14.0))

  println(s"Na taśmie wjechało: ${dirtyItems.size()} brudnych naczyń.")

  val sorter = new KitchenSorter()
  sorter.sort(dirtyItems)
  println(s"Stan sortowni: ${sorter.getSpoons.size()} łyżek, ${sorter.getPlates.size()} talerzy.")

  val dishwasher = new Dishwasher(id = 1, spoonCapacity = 3, plateCapacity = 2)
  val workerElf = new Elf("Zgred")


  dishwasher.loadFromSorter(sorter)
  println(s"Stan sortowni po 1. cyklu: ${sorter.getSpoons.size()} łyżek, ${sorter.getPlates.size()} talerzy.")

  //proba załadowania zajetej zmywarki
  dishwasher.loadFromSorter(sorter)

  //oproznienie
  workerElf.emptyDishwasher(dishwasher)

  //oproznienie pustej
  workerElf.emptyDishwasher(dishwasher)

  dishwasher.loadFromSorter(sorter)
  println(s"Stan sortowni po 2. cyklu: ${sorter.getSpoons.size()} łyżek, ${sorter.getPlates.size()} talerzy.")

  workerElf.emptyDishwasher(dishwasher)


  dishwasher.loadFromSorter(sorter)
}
