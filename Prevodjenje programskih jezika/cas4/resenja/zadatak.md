---
layout: default-panel
---
# Prevođenje programskih jezika
## Čas 04

### Zadatak 1
Napisati python-skript koji kao prvi argument komandne linije prihvata ime fajla
koji je dobijen sistemom UNITEX kao rezultat prepoznavanja imenovanih entiteta. Na
osnovu tog fajla treba napraviti .xml fajl koji je dobijen zamenom semantičkih markera
odgovarajućim tagom (+org se menja tagom <org>).

```
{Kompanija "Jat ervejz",.NE+org:1s}
saopstila je da ce od {ponedeljka, 26.
novembra,.NE+date:2s}, organizovati
decembarsku promotivnu akciju u okviru
koje ce putnici moci za {99
evra,.NE+price:4p} da kupe povratne
karte do {Podgorice,.NE+city:2q},
{Tivta,.NE+city:2q},
{Sarajeva,.NE+city:2q} i
{Skoplja,.NE+city:2q}.

```

```xml
<lista_knjiga>
    <knjiga rbr="1" >
        <naslov> Yacc </naslov>
        <autor> Filip Maric </autor>
        <godina_izdanja> 2004 </godina_izdanja>
        <izdavac> Matematicki fakultet </izdavac>
        <cena valuta="rsd"> 1000 </cena>
    </knjiga>
    <knjiga rbr="2" >
        <autor> Fredrik Lundh </autor>
        <cena valuta="eur"> 50 </cena>
        <izdavac> O’Reilly & Associates </izdavac>
        <godina_izdanja> 2001 </godina_izdanja>
        <naslov> Python Standard Library </naslov>
    </knjiga>
</lista_knjiga>
```

### Zadatak 2
Napisati python-skript koji štampa na standardni izraz autora (−a), cenu (−c),
izdavača (−i) ili godinu izdanja (−g) knjige koja se navodi kao argument komande linije,
u zavisnosti od prisutne opcije komandne linije (u slučaju da nema opcija, ispisati sve
podatke o traženoj knjizi). Informacije o knjigama se nalaze u fajlu knjige.xml koji ima
sledeći format:

```xml
<?xml version="1.0" encoding="utf-8" ?>
<lista_knjiga>
    <knjiga rbr="1" >
        <naslov> Yacc </naslov>
        <autor> Filip Maric </autor>
        <godina_izdanja> 2004 </godina_izdanja>
        <izdavac> Matematicki fakultet </izdavac>
        <cena valuta="rsd"> 1000 </cena>
    </knjiga>
    <knjiga rbr="2" >
        <autor> Fredrik Lundh </autor>
        <cena valuta="eur"> 50 </cena>
        <izdavac> O’Reilly & Associates </izdavac>
        <godina_izdanja> 2001 </godina_izdanja>
        <naslov> Python Standard Library </naslov>
    </knjiga>
</lista_knjiga>
```

NAPOMENA: Od korisnika se uvek očekuje da kao poslednji argument prosledi ime knjige koju traži
(pod navodnicima za slučaj da je u pitanju više reči). Pre poslednjeg argumenta korisnik može
proslediti najmanje 0, a najviše 4 opcije iz skupa {-a, -c, -i, -g} i to u proizvoljnom redosledu.
