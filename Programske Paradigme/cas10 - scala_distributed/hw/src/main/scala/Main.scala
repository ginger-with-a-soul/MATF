import java.util.Scanner

import org.apache.spark.{SparkConf, SparkContext}

object main {

  def main(args: Array[String]): Unit = {

    val conf = new SparkConf().setAppName("MyApp").setMaster("local[4]").set("spark.testing.memory", "214780000")

    val ctx = new SparkContext(conf)

    val sc1 : Scanner = new Scanner(System.in)

    print("Unesite n: ")
    val n : Int = sc1.nextInt()
    val niz = (2 to n by 2).toArray
    val nizRDD = ctx.parallelize(niz)

    val rez : Array[Int]= nizRDD.map(x => x * x).collect()

    ctx.stop()

    println(s"Rezultat: ${rez.mkString(", ")}")

  }

}
