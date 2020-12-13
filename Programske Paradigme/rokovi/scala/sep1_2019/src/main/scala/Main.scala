import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]) : Unit ={

    val conf = new SparkConf()
      .setAppName("MyApp")
      .setMaster("local[4]")
      .set("spark.testing.memory", "249000000000")

    val cnx = new SparkContext(conf)

    val RDD = cnx.textFile("data.csv")
        .map(linija => {
          var niz = linija.split(",")
          (niz(2), ((niz(3).toFloat*1000).toInt, (niz(4).toFloat*1000).toInt, (niz(5).toFloat*1000).toInt, (niz(6).toFloat*1000).toInt, (niz(7).toFloat*1000).toInt))
        })
        .aggregateByKey((0, 0, 0, 0, 0))((acc, v) => (acc._1 + v._1, acc._2 + v._2, acc._3 + v._3, acc._4 + v._4, acc._5 + v._5), (a1, a2) => (a1._1 + a2._1, a1._2 + a2._2, a1._3 + a2._3, a1._4 + a2._4, a1._5 + a2._5))
        .sortByKey(ascending = true)
        .collect()
        .foreach(x => println(x._1 + ": " + x._2._1 + ", " + x._2._2 + ", " + x._2._3+ ", " + x._2._4 + " " + x._2._5))

    cnx.stop()
  }
}
