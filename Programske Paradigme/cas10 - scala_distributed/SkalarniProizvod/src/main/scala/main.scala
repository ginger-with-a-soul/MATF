import org.apache.spark.{SparkConf, SparkContext}

object main {

  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("SkalarniProizvod")
      .setMaster("local[4]")
      .set("spark.testing.memory", "9999999999")

    val cnx = new SparkContext(conf)

    val v1RDD = cnx.textFile("vektor1.txt")
      .flatMap(linija => linija.split(", *"))
      .map(_.toInt)

    val v2RDD = cnx.textFile("vektor2.txt")
        .flatMap(_.split(", *"))
        .map(_.toInt)

    val res = v1RDD.zip(v2RDD)
        .map(pair => pair._1 * pair._2)
        .reduce((a, b) => a + b) //sum() more elegant; or reduce((_+_))

    cnx.stop()

    println(s"Result: ${res}")

  }

}