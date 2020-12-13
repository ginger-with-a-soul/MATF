Procedure Sort_Merge (Var t : TAB; g, d : integer); 
Var 
   m, i, j, k : integer; 
   s : TAB; 
Begin 
     If d > g Then 
     Begin          
          m := (g + d) Div 2; 
          Sort_Merge (t, g, m); 
          Sort_Merge (t, m + 1, d); 
           
     For i := m DownTo g Do 
              s[i] := t[i]; 
           
     For j := m + 1 To d Do 
              s[d + m + 1 - j] := t[j]; 
           
     i := g; j := d; 
          For k := g To d Do 
          Begin 
               If s[i] < s[j] Then 
               Begin 
                    t[k] := s[i]; 
                    i := i + 1; 
               End 
               Else 
                   Begin 
                         t[k] := s[j]; 
                         j := j - 1; 
                   End; 
          End; 
     End; 
End; z
