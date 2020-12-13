/*
Kao i Z-algoritam, i KMP algoritam u linearnom vremenu nalazi pojavljivanja nase reci
u zadatom tekstu.

0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22
a b c x a b c d a b x  a  b  c  d  a  b  c  d  a  b  c  y

a b c d a b c y

Krenemo linearno da poredimo nasu rec sa tekstom. Kada naletimo na nepodudaranje, stajemo
u nasoj reci na to slovo i gledamo najduzi sufiks i prefiks sa leve strane tog slova gde smo
stali koji se poklapaju. Sufiks moze da obuhvata sve karaktere sem prvog u tom segmentu koji
se razmatra, analogno za prefiks.To znaci da smo u tekstu koji pretrazujemo, sa leve strane 
onoga gde smo stali (tamo gde nam se prvi put nisu poklapala slova) nasli bas prefiks nase reci 
(jer je relacija tranzitivnosti: nas sufiks i prefiks se poklapaju, nas sufiks se poklapa sa 
sufiksom teksta gde smo stali a to znaci da se nas prefiks poklapa sa sufiksom teksta gde smo stali).
Zatim mi nase pretrazivanje nastavljamo od prvog mesta posle prefiska nase reci, i onog mesta
u tekstu gde smo stali (moze da se dogodi da opet negde stanemo i onda opet gledamo na isti
nacin).

U nasem primeru: prvo se poklapaju a b c i razlika je u x. U nasoj reci nema onda istog prefiksa
i sufiksa pa nastavljamo normalno poredjenje. Sledece poklapanje je a b c d a b i na x se pravi
razlika. Najveci sufiks i prefiks tada su a b, to znaci da mi sada poredimo x i c a tu nema
poklapanja pa nastavljamo dalje. Sledece poklapanje je a b c d a b c i na d se pravi razlika.
Sada su nam najduzi sufiks i prefiks a b c, to znaci da mi onda poredimo d i d, pa a i a i sve
tako i dolazimo na kraju do poklapanja.
*/