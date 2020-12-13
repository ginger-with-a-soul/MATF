import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("VlaznostVazduha")
      .setMaster("local[4]")
      .set("spark.testing.memory", "249000000000")

    val cnx = new SparkContext(conf)

    val myRDD = cnx.textFile("beograd.txt").cache()

    myRDD.map(linija => {
      val niz = linija.split(" ")
      ((niz(2), niz(1)), niz(3).toDouble)
    })
        .aggregateByKey((0.0, 0))((a, v) => (a._1 + v, a._2 + 1), (a1, a2) => (a1._1 + a2._1, a1._2 + a2._2))
        .collect()
        .foreach(i => println(f"Godine ${i._1._1}, meseca ${i._1._2}, prosecna vlaznost vazduha bila je: ${i._2._1 / i._2._2}"))

    cnx.stop()

  }

}
