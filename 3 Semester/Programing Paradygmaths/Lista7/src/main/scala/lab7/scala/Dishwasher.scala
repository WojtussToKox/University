package lab7.scala
import lab7.java.KitchenSorter
import scala.jdk.CollectionConverters._

class Dishwasher (val id: Int, val spoonCapacity: Int, val plateCapacity: Int){
  private var isWorking = false

  def loadFromSorter(sorter: KitchenSorter): Unit = {
    if (isWorking) {
      println("Zmywarka wciąż pracuje! Czekaj.")
      return
    }

    val javaSpoons = sorter.getSpoons
    val javaPlates = sorter.getPlates

    val scalaSpoons = javaSpoons.asScala
    val scalaPlates = javaPlates.asScala

    val spoonsToWash = scalaSpoons.take(spoonCapacity).toList
    val platesToWash = scalaPlates.take(plateCapacity).toList

    if (spoonsToWash.isEmpty && platesToWash.isEmpty) {
      println(s"Zmywarka #$id: Brak odpowiednich naczyń w sortowni.")
      return
    }

    javaSpoons.removeAll(spoonsToWash.asJava)
    javaPlates.removeAll(platesToWash.asJava)


    isWorking = true;

    println(s"Zmywarka #$id pobrała: ${spoonsToWash.size} łyżek i ${platesToWash.size} talerzy.")
    println(s"Zmywarka #$id rozpoczyna program mycia (BLOKADA).")
  }

  def unload(): Unit = {
    if (isWorking) {
      isWorking = false
      println(s"Zmywarka #$id została opróżniona i jest gotowa do dalszej pracy.")
    } else {
      println(s"Zmywarka #$id stoi pusta, nie ma co opróżniać.")
    }
  }
}
