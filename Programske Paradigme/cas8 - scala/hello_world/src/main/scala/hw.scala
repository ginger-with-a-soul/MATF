object hw {
  def main(args : Array[String]): Unit ={
    println("Hello Scala World")
    //val == const
    val multiline : String =
      """
        |This
        |is
        |a
        |multiline
        |string
      """.stripMargin

    println(multiline)

    //interpolation
    val len : Int = 3
    var subj : String = "Programming Paradigms"
    println(s"Class $subj lasts for $len hours.")

    //for loop
    //var i : Int = 0
    for(i <- Range(1, 10, 2)){
      print(s"$i ")
      println()
    }

    //collection loop
    var subjects : Array[String] = new Array[String](5)
    subjects(0) = "PP"
    subjects(1) = "P1"
    subjects(2) = "P0"
    subjects(3) = "PPI"
    subjects(4) = "RG"

    for(s <- subjects){
      println(s)
    }

    def writeOutSorted(subjects : Array[String]) : Unit = {
      val x = subjects.sortWith(cmpString)
      //lambda:                ((p1, p2) => {if(p1.compareTo(p2) < 0) true else false})
      //                        (arguments) => {func body}
      for(s <- x){
        println(s)
      }
    }

    def cmpString(s1 : String, s2 : String) : Boolean = {
      if(s1.compareTo(s2) < 0){
        return true
      }
      else{
        return false
      }
    }

    writeOutSorted(subjects)
  }
}
