import org.apache.spark.{SparkConf, SparkContext}

import scala.compat.Platform

object main {
  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("Zaposleni")
      .setMaster("local[4]")
      .set("spark.test.memory", "9999999999")

    val cnx = new SparkContext(conf)

    val luckyWinners = cnx.textFile("zaposleni.txt")
        .filter(_.contains("IT_PROG"))
        .map(linija => {
          val niz = linija.split(" ")
          (niz(0), niz(1), niz(3))
        })
        .takeSample(false, 3, Platform.currentTime)

    cnx.stop()

    luckyWinners.foreach(entry => println(s"First name: ${entry._1}, Last name: ${entry._2}, Username: ${entry._3}"))

  }
}