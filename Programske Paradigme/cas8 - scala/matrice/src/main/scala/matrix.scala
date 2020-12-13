import java.io.{File, PrintWriter}
import java.util.Scanner

object matrix {

  def main(args : Array[String]) : Unit = {

    val sc1 : Scanner = new Scanner(new File("src/main/data/matrix1.txt"))
    val sc2 : Scanner = new Scanner(new File("src/main/data/matrix2.txt"))
    val pw : PrintWriter = new PrintWriter(new File("src/main/data/res.txt"))

    val n : Int = sc1.nextInt()
    val m1 : Int = sc1.nextInt()
    val m2 : Int = sc2.nextInt()
    val k : Int = sc2.nextInt()

    if(m1 != m2){
      println("Error: invalid matrix dimensions")
      System.exit(1)
    }

    val matrix1 = Array.ofDim[Int](n, m1)
    val matrix2 = Array.ofDim[Int](m1, k)

    for(i <- Range(0, n)){
      for(j <- Range(0, m1)){
        matrix1(i)(j) = sc1.nextInt()
      }
    }

    for(i <- Range(0, m2)){
      for(j <- Range(0, k)){
        matrix2(i)(j) = sc2.nextInt()
      }
    }

  }

}
