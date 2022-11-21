if (somme(codeA)=0 et somme(codeB)=0){
  accepte  = vrai
  fin  = vrai
}else{
   /* Tester if le Segment est totalement invisible */
    if Et_logique(codeA, codeB){
      fin  = vrai;
    }else{
  /* Segment peut être partiellement Visible */
  codeExt  = codeA
  if (somme(codeA)=0){
   codeExt  = codeB
 }
if(superieur(codeExt)){
  x  = Xa + ( Ymax  - Ya)/m y  = Ymax
}else{
// Déterminer l’intersection avec le côte inférieur de F
if (inferieur(codeExt))  { x  = Xa + ( Ymin - Ya)/m y  = Ymin
}else{
// Déterminer l’intersection avec le côte droit de F
if (droite(codeExt))  {
y  = Ya + ( Xmax - Xa)*m x  = Xmax
}else{
// Déterminer l’intersection avec le côte droit de F
if (gauche(codeExt))  {
  y  = Ya + ( Xmin - Xa)*m x  = Xmin
}
}
}
}
// Calcul le code la nouvelle extrémité
if (codeExt= codeA ){
Xa  = x
Ya  = y
codeA  = CalculCode(Xa, Ya, Xmin, Ymin, Xmax, Ymax)
}else{
  Xb  = x Yb  = y
  CodeB  = CalculCode(Xb, Yb, Xmin, Ymin, Xmax, Ymax)
}
if (accept ) {
AfficheSegment(Xa, Ya, Xb, Yb, attribut) Finsi
}
