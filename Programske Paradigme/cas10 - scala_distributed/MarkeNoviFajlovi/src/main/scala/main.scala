import java.io.PrintWriter

import org.apache.spark.{SparkConf, SparkContext}

object main {
  def main(args : Array[String]) : Unit = {
    val conf = new SparkConf()
      .setAppName("MarkeNoviFajl")
      .setMaster("local[4]")
      .set("spark.testing.memory", "9999999999")

    val cnx = new SparkContext(conf)

    cnx.textFile("uredjaji.txt")
        .map(linija => {
          val niz = linija.split("\\s+")
          (niz(0), niz.drop(1).mkString(" "))
        })
        .groupByKey()
        .foreach(par => {
          val f = new PrintWriter(par._1 + ".txt".toLowerCase)

          f.write(s"------ ${par._1} ------\n")
          par._2.foreach(t => {
            f.write(t + "\n")
          })

          f.close()
        })

    cnx.stop()
  }

}
