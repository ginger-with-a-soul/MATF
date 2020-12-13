class Film {
  var naslov : String = ""
  var trajanje : Int = 0
  var godina : Int = 0

  //konstruktor nosi ime this. U Javi je to ime klase. Nema povratnu vrednost

  def this(naslov : String, trajanje : Int, godina : Int){
    this()
    this.naslov = naslov
    this.trajanje = trajanje
    this.godina = godina
  }

  //nije potrebno return jer se po difoltu vraca vrednost poslednje naredbe
  def getNaslov() : String = {
    this.naslov
  }

  //clean metod (telo mu se sastoji od samo jedne naradbe i nema propratnih efekata)
  def getTrajanje() : Int = this.trajanje

  def getGodina() : Int = this.godina

  override def toString: String = {
    s"Film $naslov iz $godina traje $trajanje minuta"
  }
}

class CrtaniFilm extends Film {
  var autor : String = ""

  def this(naslov : String, trajanje : Int, godina : Int, autor : String){
    this()
    this.naslov = naslov
    this.godina = godina
    this.trajanje = trajanje
    this.autor = autor
  }

  def getAutor() : String = this.autor

  override def toString: String = super.toString() + s" autora $autor."
}

object main {

  def main(args : Array[String]) : Unit = {
    var f : Film = new Film()
    println(f)

    var cf : CrtaniFilm = new CrtaniFilm("Petar Pan", 94, 1992, "Walt Disney")
    println(cf)
  }

}
