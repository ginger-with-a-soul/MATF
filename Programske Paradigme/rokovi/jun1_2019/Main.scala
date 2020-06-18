import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentLinkedQueue



object Main {

  class Finder(keyword : String,
               redPutanja : ConcurrentLinkedQueue[String],
              tid : Int) extends Thread {

    override def run(): Unit = {
      while(!redPutanja.isEmpty){

        val novaPutanja : String = redPutanja.poll()

        val fajlScanner : Scanner = new Scanner(new File(novaPutanja))
        var lineNum : Int = 0
        while(fajlScanner.hasNextLine){
          lineNum += 1
          val lineString = fajlScanner.nextLine()
          val strings : Array[String] = lineString.split(" ")
          for(word <- strings){
            if(word.equals(keyword)){
              println(f"$novaPutanja:$lineNum")
            }
          }
        }

      }

      println(f"Nit $tid je zavrsila sa radom!")

    }

  }

  def main(args : Array[String]) : Unit = {

    val scIn : Scanner = new Scanner(System.in)
    println("Unesite kljucnu rec: ")
    val keyword : String = scIn.next()
    println("Unesite broj niti: ")
    val threadNum : Int = scIn.nextInt()

    val scFile : Scanner = new Scanner(new File("tajni_fajl.txt"))

    val redPutanja = new ConcurrentLinkedQueue[String]()

    while(scFile.hasNextLine){
      redPutanja.add(scFile.next())
    }

    val finders = new Array[Finder](threadNum)

    for(i <- Range(0, threadNum)){
      finders(i) = new Finder(keyword, redPutanja, i)
    }

    for(f <- finders){
      f.start()
    }

    for(f <- finders){
      f.join()
    }


  }

}
