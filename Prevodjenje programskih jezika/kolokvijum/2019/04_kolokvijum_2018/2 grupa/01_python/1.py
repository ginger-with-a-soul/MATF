import re, sys

if len(sys.argv) < 2 :
  exit('Nedovoljan broj argumenata')

sve =False
izdavac = False
platforma= False
info = False

if sys.argv[1] == "-sve":
  sve = True  
else:
   if len(sys.argv) ==2:
    exit("Nedovoljno argumenata")
   else: 
    rec= sys.argv[2] 
  
   if sys.argv[1] == '-i': 
    izdavac = True
   elif sys.argv[1] == '-p':
    platforma= True     
   elif sys.argv[1] == '-info' :
    info = True
   else:
    exit("Nepodrzana opcija") 
    
regex = re.compile(r'<igra\s+id="(\d+)">\s*'
+r"<naziv>\s*(?P<naslov>([a-zA-Z0-9,.:'()]+ ?)+) *</naziv>\s*"
+r"<godina>\s*(?P<godina>19[5-9]\d|200\d|201[0-8])\s*</godina>\s*"
+r"<izdavac>\s*(?P<izdavac>([0-9A-Z][a-zA-Z0-9]* ?)+) *</izdavac>\s*"
+r"<platforme>\s*(?P<platforma>(PlayStation|Xbox|PC|Nintendo)(,\s*(PlayStation|Xbox|PC|Nintendo))*)\s*</platforme>\s*"
+r"<ocena>\s*(?P<ocena>\d\.\d|10\.0)\s*</ocena>\s*"
+r"</igra>"
)    

try:
  with open("podaci.xml","r") as f:
    datoteka = f.read()
except IOError:
  exit("Ne mogu da citam podaci.xml")
  
zbirka ={}
     
for m in regex.finditer(datoteka):
#  print( re.split(', *',m.group('platforma')))
  zbirka[m.group(1)] = [m.group('naslov'),m.group('godina'), m.group('izdavac'),m.group('ocena'),re.split(', *',m.group('platforma'))]
  
if sve:
  lista = list(zbirka.values())
  lista.sort()
  for  i in lista:
    print(i[0])
    
if izdavac :
  for v in zbirka.values():
    if rec == v[2]:
      print(v[0], "(",v[1],")")    

if info:
  for v in zbirka.values():
    if re.search(r''+rec,v[0],re.I) is not None:
      print (v[0],"(",v[3],")")    

if platforma:
  for v in zbirka.values():       
    if rec in v[-1]:
      print (v[0])
