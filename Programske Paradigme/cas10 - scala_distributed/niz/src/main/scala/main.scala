import java.util.Scanner

import org.apache.spark.{SparkConf, SparkContext}

object main {

  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf().setAppName("MyApp").setMaster("local[4]").set("spark.testing.memory", "471859201")

    val cnx = new SparkContext(conf)

    val sc1 : Scanner = new Scanner(System.in)
    print("Input n: ")
    val n : Int = sc1.nextInt()

    val niz = (2 to n by 2).toArray
    val nizRDD = cnx.parallelize(niz)

    val rez = nizRDD.map(x => x * x).take(10)

    cnx.stop()

    println(s"Result: ${rez.mkString(", ")}")

  }

}
