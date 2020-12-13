import org.apache.spark.{SparkConf, SparkContext}

object main {
  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("Maiven")
      .setMaster("local[4]")
      .set("spark.test.memory", "9999999999")

    val cnx = new SparkContext(conf)

    val data = cnx.textFile("mavenLog.txt")
        .filter(linija => linija.startsWith("Downloading") || linija.startsWith("Downloaded"))
        .map(linija => {
          val niz = linija.split(":")
          (niz(0), niz.drop(1))
        })
        .groupByKey()
        .map(par => (par._1, par._2.size))
        .collect()

    //mogli smo i da ucitamo ovaj mavenLog.txt u jednu promenjivu i stavimo .cache()
    //kako bi se kesiralo
    //zatim uradimo posebno filter nad tom promenljivom za Downloaded i prebrojimo
    //a zatim i za Downloading!
    cnx.stop()

    data.foreach(par => println(s"${par._1} -> ${par._2}"))
  }
}