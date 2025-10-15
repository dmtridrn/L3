type 'a arbre = 
  | Vide
  | Noeud of 'a * 'a arbre * 'a arbre

let rec hauteur = function
  | Vide -> 0
  | Noeud (_, gauche, droite) -> 
      1 + max (hauteur gauche) (hauteur droite)

let rec parcours_infixe = function
  | Vide -> []
  | Noeud (valeur, gauche, droite) ->
      (parcours_infixe gauche) @ [valeur] @ (parcours_infixe droite)