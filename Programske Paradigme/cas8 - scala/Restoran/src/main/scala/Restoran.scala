import java.util.Scanner
import java.util.concurrent.ThreadLocalRandom


object Restoran {

  class Konobar(ime : String, brStolova : Int) extends Thread {
    override def run(): Unit = {
      for(i <- Range(0, brStolova)){
                    //generator slucajnih brojeva jedinstven za svaku nit. cur vrati obj klase
        Thread.sleep(ThreadLocalRandom.current().nextInt(1, 3) * 1000)
        println(s"Konobar $ime usluzio sto $i.")
      }
      println(s"Konobar $ime zavrsio smenu!")
    }
  }

  def main(args : Array[String]) : Unit = {
    val sc : Scanner = new Scanner(System.in)
    print("Unesi broj stolova: ")
    val brojStolova : Int = sc.nextInt()
    val korak : Int = Math.floor(brojStolova / 5.0).toInt

    val dimitrije : Konobar = new Konobar("Dimitrije", korak)
    val nikola : Konobar = new Konobar("Nikola", korak)
    val jelena : Konobar = new Konobar("Jelena", korak)
    val slavica : Konobar = new Konobar("Slavica", korak)
    val sofija : Konobar = new Konobar("Sofija", brojStolova - korak * 4)

    dimitrije.start()
    nikola.start()
    jelena.start()
    slavica.start()
    sofija.start()
  }

}
