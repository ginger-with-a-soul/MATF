#! /usr/bin/env python
# -*- coding: utf-8 -*-
"""
Klasa koja opisuje tacke u 2d prostoru.
"""

class Tacka:
    """
    Dokumentacija za klasu se pise na ovaj nacin.
    Trostruki navodnik oznacava 'multiline' string.
    Razvojna okruzenja pri parsiranju python klasa, ocekuju da pronadju
    dokumentaciju kao prvi string unutar klase, i to posle mogu prikazati
    svojim korisnicima pri radu.

    Primetite da u metodima klase moramo eksplicitno prenositi 'self' koji
    predstavlja referencu da objekat nad kojim se metod poziva.
    Razlog za to je sto u Python svetu vlada misljenje:
        "Explicit is better then implicit".
    """

    # Staticka promenljiva unutar klase
    broj_tacaka = 0

    # Konstruktor u Python-u se pise implementiranjem metoda __init__.
    # Python klasa mozemo imati samo jedan konstruktor.
    # Pitanje za vas, kako resiti problem jednog konstruktora ako nam treba vise konstruktora?
    def __init__(self, x, y):
        # Nema specifikatora vidljivosti, duh pajton jezika kaze da su drugi
        # programeri nasi prijatelji, i da ako im stavimo do znanja da je
        # promenljiva privatna, nece je dirati :)
        # https://stackoverflow.com/questions/1641219/does-python-have-private-variables-in-classes
        # Cesto je konvencija da se promenljiva oznaci kao privatna sa prefiksom _
        self._x = float(x)
        self._y = float(y)
        Tacka.broj_tacaka += 1

    def transliraj(self, dx, dy):
        """Translates point by vector (dx, dy)."""
        self._x += dx
        self._y += dy

    def __str__(self):
        """Returns the string representation of object."""
        return "(%.2f, %.2f)" % (self._x, self._y)

    # Nema striktne konvencije povodom 'getera', neki koriste getX, neko x.
    def x(self):
        """Returns the x coordinate of the class."""
        return self._x

    def y(self):
        """Returns the y coordinate of the class."""
        return self._y

    # Procitati dodatno o metodu 'repr', on se poziva kada imamo
    # listu tacaka i zatrazimo stringovni ispis liste. Python poziva
    # metod __repr__ nad elementima i dobija listu stringova, potom se
    # od liste stringova pravi string.
    def __repr__(self):
        return self.__str__();

    # Mozemo predefinisati operator poredjenja (korisno za sortiranje)
    # Poredimo dve tacke, 'self' i 'point2'.
    def __gt__(self, point2):
        if self._x == point2._x:
            return self._y - point2._y
        else:
            return self._x - point2._x

    # Mozemo i predefinisati kako se sabiraju dve tacke!
    # Na primer, sabiramo ih koordinatu po koordinatu.
    def __add__(self, point2):
        return Tacka(self._x + point2._x, self._y + point2._y)

    # Lista operatora koji se mogu predefinisati
    #+          __add__(self, other)            Addition
    # *         __mul__(self, other)            Multiplication
    # -         __sub__(self, other)            Subtraction
    # %         __mod__(self, other)            Remainder
    # /         __truediv__(self, other)        Division
    # <         __lt__(self, other)             Less than
    # <=        __le__(self, other)             Less than or equal to
    # ==        __eq__(self, other)             Equal to
    # !=        __ne__(self, other)             Not equal to
    # >         __gt__(self, other)             Greater than
    # >=        __ge__(self, other)             Greater than or equal to
    # [index]   __getitem__(self, index)        Index operator
    # in        __contains__(self, value)       Check membership
    # len       __len__(self)                   The number of elements
    # str       __str__(self)                   The string representation
