import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]) : Unit ={

    val conf = new SparkConf()
      .setAppName("MyApp")
      .setMaster("local[4]")
      .set("spark.testing.memory", "24900000000")

    val cnx = new SparkContext(conf)

    val RDD = cnx.textFile("data.csv")
      .map(_.split(","))
      .map(l => (l.last.equals("W"), l.count(_.equals("x")), l.count(_.equals("o")), l.count(_.equals("b"))))
      .cache()

    val res1 = RDD.filter(x => x._1.equals(true)).count * 100.0 / RDD.count()
    val res2 = RDD.filter(x => x._4 == 0).filter(x => x._1.equals(true)).count()
    val res3 = RDD.filter(_._1.equals(true)).filter(_._2 > 3).count()

    println(f"Prvi igrac pobedio: ${res1}")
    println(f"Broj pobeda prvog igraca bez praznih polja: ${res2}")
    println(f"Broj dobijenih partija u vise od 3 poteza: ${res3}")

    cnx.stop()

  }

}
