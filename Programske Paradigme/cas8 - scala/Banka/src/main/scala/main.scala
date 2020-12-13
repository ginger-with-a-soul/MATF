import java.io.File
import java.util.Scanner
import java.util.concurrent.{ConcurrentLinkedQueue, ThreadLocalRandom}
import java.util.concurrent.atomic.AtomicLong


class Klijent(ime : String, zajam : Long){

  var dug : Double = 0

  def getIme : String = this.ime

  def getZajam : Long = this.zajam

  def setDug(dug : Double) : Unit = {
    this.dug = dug
  }

  def getDug : Double = this.dug

}

class Sluzbenica(kamata : Double, pocetniKapital : AtomicLong,
                 redKlijenata : ConcurrentLinkedQueue[Klijent],
                 redZaduzenih : ConcurrentLinkedQueue[Klijent]) extends Thread {

  override def run(): Unit = {

    while(!redKlijenata.isEmpty){

      val k = redKlijenata.poll()
      println("Klijent " + k.getIme + " je na redu.")
      Thread.sleep(ThreadLocalRandom.current().nextInt(1, 4) * 1000)

      pocetniKapital.synchronized{
        if (k.getZajam > pocetniKapital.get()) {
          println("Klijent " + k.getIme + " ne moze da dobije zajam jer nema dovoljno novca!")
        }
        else {
          k.setDug(k.getZajam * (1 + (kamata / 100)))
          redZaduzenih.add(k)
          pocetniKapital.set(pocetniKapital.get() - k.getZajam)
          println(s"Klijent ${k.getIme} je dobio zajam ${k.getZajam}e. Dug sa kamatom: ${k.getDug}e.")
        }
      }
    }

  }
}

object main {

  def main(args : Array[String]): Unit = {

    val sc1 : Scanner = new Scanner(System.in)
    print("Unesite pocetni kapital: ")
    val pocetniKapital : AtomicLong = new AtomicLong(sc1.nextLong())
    val vrednostKapital = pocetniKapital.get()

    print("Unesite kamatnu stopu: ")
    val kamatnaStopa : Double = sc1.nextDouble()
  
    print("Unesite broj sluzbenica: ")
    val brojSluzbenica : Int = sc1.nextInt()

    val sc2 : Scanner = new Scanner(new File("red_klijenata.txt"))

    val redKlijenata = new ConcurrentLinkedQueue[Klijent]()
    val redZaduzenih = new ConcurrentLinkedQueue[Klijent]()

    while(sc2.hasNextLine){
      redKlijenata.add(new Klijent(sc2.next(), sc2.nextLong()))
    }

    val sluzbenice = new Array[Sluzbenica](brojSluzbenica)

    for(i <- Range(0, brojSluzbenica)){
      sluzbenice(i) = new Sluzbenica(kamatnaStopa, pocetniKapital, redKlijenata, redZaduzenih)
    }

    for(sl <- sluzbenice){
      sl.start()
    }

    for(sl <- sluzbenice){
      sl.join()
    }

    var zarada : Double = 0
    val it = redZaduzenih.iterator()

    while(it.hasNext){
      zarada += it.next().getDug
    }

    println(s"Ostalo kapitala: ${pocetniKapital.get()}. Banka je zaradila: ${-vrednostKapital + zarada + pocetniKapital.get()}e.")
  }

}
