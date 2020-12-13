import org.apache.spark.{SparkConf, SparkContext}

object main {
  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("PojavljivanjeReci")
      .setMaster("local[4]")
      .set("spark.testing.memory", "9999999999")

    val cnx = new SparkContext(conf)

    cnx.textFile("knjiga.txt")
        .flatMap(_.split(" "))
        .map(rec => (rec.toLowerCase(), 1))
        .reduceByKey((_+_))
        .sortByKey()
        .saveAsTextFile("Broj_pojavljivanja_reci")

    cnx.stop()

  }
}
