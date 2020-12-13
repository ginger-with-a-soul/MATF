import java.io.File
import java.util.Scanner
import java.util.concurrent.ThreadLocalRandom

import scala.collection.mutable
import scala.collection.mutable.ArrayBuffer

class Kladionicar(ime : String, novac : Int, tiket : mutable.HashMap[String, Char],
                  utakmice : mutable.HashMap[String, (Float, Float, Float, Char)])
                  extends Thread {

  var zarada : Float = 0
  var pogodjednoParova : Int = 0

  def getZarada : Float = this.zarada
  def getPogodjenoParova : Int = this.pogodjednoParova
  def getIme : String = this.ime

  override def run(): Unit = {
    utakmice.synchronized {
      utakmice.wait()
    }
    val it = tiket.iterator
    while(it.hasNext){
        val t = it.next()
        val ut = utakmice(t._1)
        if(ut._4 == t._2){
          println(s"$ime je pogodio rezultat utakmice ${t._1} --> ${t._2}")
          pogodjednoParova += 1
          if(t._2 == '1'){
            zarada += ut._1
          }
          else if(t._2 == 'x'){
            zarada += ut._2
          }
          else{
            zarada += ut._3
          }
        }
      }
      if(pogodjednoParova > 0){
        zarada = zarada * novac / pogodjednoParova
      }
    }
}

object main {

  def main(args : Array[String]): Unit = {

    val sc1 : Scanner = new Scanner(new File("utakmice.txt"))
    val sc2 : Scanner = new Scanner(new File("kladionicari.txt"))

    val utakmice = new mutable.HashMap[String, (Float, Float, Float, Char)]()

    while(sc1.hasNextLine){
      utakmice.put(sc1.nextLine(), (sc1.nextFloat(), sc1.nextFloat(), sc1.nextFloat(), '-'))
      sc1.nextLine()
    }

    val kladionicari = new ArrayBuffer[Kladionicar]()

    while(sc2.hasNextLine){
      val ime : String = sc2.next()
      val novac : Int = sc2.nextInt()
      val tiket = new mutable.HashMap[String, Char]()
      for(_ <- Range(0, 5)){
        sc2.nextLine()
        tiket.put(sc2.nextLine(), sc2.next()(0))
      }

      kladionicari.append(new Kladionicar(ime, novac, tiket, utakmice))

    }

    for(k <- kladionicari){
      k.start()
    }

    println("Utakmice se odigravaju...")
    Thread.sleep(5000)

    val res = Array('1', 'x', '2')

    for(u <- utakmice){
      utakmice(u._1) = (u._2._1, u._2._2, u._2._3, res(ThreadLocalRandom.current().nextInt(0, 3)))
    }

    utakmice.synchronized{
      utakmice.notifyAll()
    }

    for(k <- kladionicari){
      k.join()
    }

    var trebaPlatiti : Float = 0
    for(k <- kladionicari){
      println(s"Kladionicar ${k.getIme} je pogodio ${k.getPogodjenoParova}.\nZarada: ${k.getZarada}e.")
      trebaPlatiti += k.getZarada
    }

    println(s"Kladionica treba da plati: ${trebaPlatiti}e.")

  }

}
