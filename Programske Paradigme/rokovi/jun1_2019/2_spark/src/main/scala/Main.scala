import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("MyApp")
      .setMaster("local[4]")
      //.set("spark.testing.memory", "24900000000000")

    val cnx = new SparkContext(conf)

    val myRDD = cnx.textFile("biostats.csv").cache()

    myRDD.map(linija => {
      val niz = linija.split(",")
      (niz(1), (niz(3).toDouble * 2.54, niz(4).toDouble * 0.45359237))
    })
        .aggregateByKey((0.0, 0.0, 0))((ak, vl) => (ak._1 + vl._1, ak._2 + vl._2, ak._3 + 1), (ak1, ak2) => (ak1._1 + ak2._1, ak1._2 + ak2._2, + ak1._3 + ak2._3))
        .map(p => (p._1, p._2._1 / p._2._3.toDouble, p._2._2 / p._2._3.toDouble))
        .collect()
        .foreach(i => if(i._1.equals("F")){
                          println(f"F: ${i._2} cm")
                      }
                      else{
                          println(f"M: ${i._3} kg")
                      }
        )

    cnx.stop()

  }

}
