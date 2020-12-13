import org.apache.spark.{SparkConf, SparkContext}

object main {

  def main(args : Array[String]) : Unit = {

    val conf = new SparkConf()
      .setAppName("BrojPetocifrenih")
      .setMaster("local[4]")
      .set("spark.testing.memory", "999999999")

    val cnx = new SparkContext(conf)

    val dataRDD = cnx.textFile("brojevi.txt")

    val res = dataRDD
                    .filter(x => x.length() == 5)
                    .count()

    cnx.stop()

    println(s"Result: ${res} 5-digit numbers")

  }
}