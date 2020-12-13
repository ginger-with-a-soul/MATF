import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]) : Unit ={

    val conf = new SparkConf()
      .setAppName("MyApp")
      .setMaster("local[4]")
      .set("spark.testing.memory", "249000000000")

    val ctx = new SparkContext(conf)

    var RDD = ctx.textFile("data.txt")
      .map(_.split("\\s*,\\s*"))
      .cache()

    var svi = RDD
        .aggregate((0.0, 0.0))((ak, vr) => (ak._1 + vr(1).toInt, ak._2 + vr(2).toInt), (a1, a2) => (a1._1 + a2._1, a1._2 + a2._2))

    var sys = RDD
        .filter(_.length > 3)
        .map(items => (items(1).toInt, items(2).toInt))
        .reduce((acc, v) => (acc._1 + v._1, acc._2 + v._2))

    ctx.stop()

    println("Svi: RAM: " + svi._1 + " CPU: " + svi._2)
    println("Sys: RAM: " + sys._1 + " RAM: " + sys._2)

  }

}
