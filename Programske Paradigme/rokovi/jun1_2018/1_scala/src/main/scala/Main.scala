import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue

object Main {

  class AvioKompanija(odrediste : String,
                      avioKompanije : ConcurrentLinkedQueue[String],
                      res : ConcurrentLinkedQueue[String]) extends Thread{

    override def run(): Unit = {
      var kompanija = "SMTH"
      while(!avioKompanije.isEmpty) {
        kompanija = avioKompanije.poll()

        val sc : Scanner = new Scanner(new File(kompanija))
        while(sc.hasNextLine){
          //res.remove()
          val line : String = sc.nextLine()
          val strings : Array[String] = line.split(" ")
          if(strings(1).equals(odrediste)){
            val str = kompanija + " " + strings(0) + " " + strings(2)
            res.add(str)
          }
        }

      }
      println(f"Kompanija ${kompanija} zavrsila sa radom!")
    }

  }

  def main(args : Array[String]) : Unit = {

    val scIn : Scanner = new Scanner(System.in)
    println("Odrediste: ")
    val odrediste : String = scIn.next()

    val avioKompanije = new ConcurrentLinkedQueue[String]()
    avioKompanije.add("airserbia.txt")
    avioKompanije.add("turkishairlines.txt")
    avioKompanije.add("etihadairways.txt")
    avioKompanije.add("swissairlines.txt")

    val threads = new Array[AvioKompanija](4)
    val res = new ConcurrentLinkedQueue[String]()

    for(i <- Range(0, 4)){
      threads(i) = new AvioKompanija(odrediste, avioKompanije, res)
    }

    for(thread <- threads){
      thread.start()
    }

    for(thread <- threads){
      thread.join()
    }

    while(!res.isEmpty){
      val x = res.poll()
      println(x)
    }

  }

}
