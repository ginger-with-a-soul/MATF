import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]): Unit = {

    val conf = new SparkConf()
      .setAppName("MyApp")
      .setMaster("local[4]")
      .set("spark.testing.memory", "249000009000")


    val ctx = new SparkContext(conf)

    ctx.textFile("temperatureBoston.txt")
        .map(linija => {
          val niz = linija.split(" ")
          (niz(3), (niz(1), niz(2), niz(4).toDouble))
        })
        .aggregateByKey((0.0, 0))((ak, vr) => (ak._1 + vr._3, ak._2 + 1), (a1, a2) => (a1._1 + a2._1, a1._2 + a2._2))
        .map(p => (p._1, p._2._1 / p._2._2))
        .sortByKey()
        .collect()
        .foreach(p => println("Godina: " + p._1 + " -> " + "Temperatura: " + p._2))

    ctx.stop()
  }

}
