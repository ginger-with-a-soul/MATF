import org.apache.spark.{SparkConf, SparkContext}

object main {
  def main(args : Array[String]) : Unit = {
    val conf = new SparkConf()
      .setAppName("LogFile")
      .setMaster("local[4]")
      .set("spark.testing.memory", "9999999999")

    val cnx = new SparkContext(conf)

    val msgs = cnx.textFile("log.txt")
        .filter(linija => (linija.startsWith("[warn]") || linija.startsWith("[info]") || linija.startsWith("[error]")) && linija.contains("java"))
        .map(linija => {
          val niz = linija.split(" ")
          (niz(0), niz.drop(1).mkString(" "))
        })
        .groupByKey()
        .map(par => (par._1, par._2.size))
        .collect()

    cnx.stop()

    msgs.foreach(par => println(s"${par._1}: ${par._2}"))
  }
}