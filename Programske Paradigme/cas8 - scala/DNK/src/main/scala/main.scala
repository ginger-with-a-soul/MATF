import java.io.File
import java.util.Scanner
import java.util.concurrent.ConcurrentHashMap

import scala.collection.mutable.ArrayBuffer


class Brojac(pocetak : Int, kraj : Int, linije : ArrayBuffer[String], mapaKaraktera : ConcurrentHashMap[Char, Int]) extends Thread {

  override def run(): Unit = {

    var a : Int = 0
    var c : Int = 0
    var g : Int = 0
    var t : Int = 0

    for(i <- Range(pocetak, kraj)){
      a = linije(i).count(_ == 'a')
      c = linije(i).count(_ == 'c')
      g = linije(i).count(_ == 'g')
      t = linije(i).count(_ == 't')

      mapaKaraktera.synchronized {
        mapaKaraktera.replace('a', mapaKaraktera.get('a') + a)
        mapaKaraktera.replace('c', mapaKaraktera.get('c') + c)
        mapaKaraktera.replace('g', mapaKaraktera.get('g') + g)
        mapaKaraktera.replace('t', mapaKaraktera.get('t') + t)
      }
    }
  }

}

object main {

  def main(args : Array[String]) : Unit = {


    val sc1 : Scanner = new Scanner(new File("bio_podaci.txt"))
    val sc2 : Scanner = new Scanner(System.in)
    println("Broj raspolozivih procesora: " + Runtime.getRuntime.availableProcessors())
    println("Unesite broj niti: ")
    val brojNiti = sc2.nextInt()

    val brojaci = new Array[Brojac](brojNiti)
    //ArrayBuffer je niz promenljive duzine; u ovom slucaju niz linija tj. Stringova
    val linije = new ArrayBuffer[String]()

    while(sc1.hasNextLine()){
      linije.append(sc1.nextLine())
    }

    val brojLinija : Int = linije.length

    val mapaKaraktera = new ConcurrentHashMap[Char, Int](4, 2, brojNiti)
    mapaKaraktera.put('a', 0)
    mapaKaraktera.put('c', 0)
    mapaKaraktera.put('g', 0)
    mapaKaraktera.put('t', 0)

    val korak : Int = Math.ceil(brojLinija / brojNiti.toDouble).toInt

    for(i <- Range(0, brojNiti)){
      brojaci(i) = new Brojac(i * korak, Math.min((i + 1) * korak, brojLinija), linije, mapaKaraktera)
    }

    for(i <- Range(0, brojNiti)){
      brojaci(i).start()
    }

    for(i <- Range(0, brojNiti)){
      brojaci(i).join()
    }

    println("a: " + mapaKaraktera.get('a'))
    println("c: " + mapaKaraktera.get('c'))
    println("g: " + mapaKaraktera.get('g'))
    println("t: " + mapaKaraktera.get('t'))

  }

}
