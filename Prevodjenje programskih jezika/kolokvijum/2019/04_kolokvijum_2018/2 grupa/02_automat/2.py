
stanje = 0
prelaz= {0:{'a':0,'b':1,'c':0}, 1:{'b':1, 'c':2} , 2:{'c':2} }
zavrsna =[ 1,2]

rec=""

while(True):
  try:
    c= input()
    if (c!='a' and c!='b' and c!= 'c'):
      raise ValueError('Invalid input character')

    if (c not in prelaz[stanje].keys()):
      print("Automat ne prihvata unetu rec!")
      exit()
    else:
      stanje = prelaz[stanje][c] 
      rec+=c
      
  except EOFError:
    break
  except ValueError as v:
    exit( v)
  
if (stanje in zavrsna):
    print("Rec prihvacena automatom "+ rec)
else:
    print("Automat nije prihvatio rec " + rec)
  
  