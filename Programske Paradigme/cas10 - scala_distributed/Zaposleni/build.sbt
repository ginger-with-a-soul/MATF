name := "Zaposleni"

version := "0.1"

scalaVersion := "2.12.7"

libraryDependencies ++= {
  var sparkVer = "2.4.0"
  Seq{
    "org.apache.spark" %% "spark-core" % sparkVer
  }
}