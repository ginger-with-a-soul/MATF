import org.apache.spark.{SparkConf, SparkContext}

object Main {

  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("Ocene")
      .setMaster("local[4]")
      .set("spark.testing.memory", "2490000000000")

    val cnx = new SparkContext(conf)

    val myRDD = cnx.textFile("rezultati.txt").cache()

    myRDD.map(linija => {
      val niz = linija.split(" ")
      (niz(0), (niz(1).toInt, niz(2).toInt, niz(3).toInt, niz(4).toInt, niz(5).toInt))
    })
        .aggregateByKey((0, 0))((a, v) => (a._1 + v._1 + v._2 + v._3 + v._4 + v._5, a._2 + 1), (a1, a2) => (a1._1 + a2._1, a1._2 + a2._2))
        .map(i => {
          var ocena = 10
          if(i._2._1 < 51){
            ocena = 5
          }
          else if(i._2._1 >= 51 && i._2._1 < 61){
            ocena = 6
          }
          else if(i._2._1 >= 61 && i._2._1 < 71){
            ocena = 7
          }
          else if(i._2._1 >= 71 && i._2._1 < 81){
            ocena = 8
          }
          else if(i._2._1 >= 81 && i._2._1 < 91){
            ocena = 9
          }
          (ocena, (ocena, i._2._2))
        })
        .reduceByKey((a, b) => (a._1 + b._1, a._2))
        .map(i =>{
          (i._1, i._2._1)
        })
        .collect()
        .foreach(i => println(f"Ocenu ${i._1} dobilo ${i._2} studenata"))


    cnx.stop()
  }

}
