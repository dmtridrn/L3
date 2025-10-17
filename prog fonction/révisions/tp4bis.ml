type 'a tree = Nil | Node of 'a * 'a tree * 'a tree

let rec size arbre = 
  match arbre with
  Nil -> 0
  | Node(a,gauche,droite) -> 1+size gauche + size droite;;

let rec depth arbre = 
  match arbre with
  Nil -> 0
  |Node(a,gauche,droite) -> 1+max (depth gauche) (depth droite);;

let rec sum arbre = 
  match arbre with
  Nil -> 0
  |Node(a,gauche,droite) -> a + sum gauche + sum droite;;

let rec contains arbre elt = 
  match arbre with 
  Nil -> false
  |Node(a,gauche,droite) -> if a = elt then true else contains gauche elt || contains droite elt;;

let elements arbre = 
  let rec aux arbre acc = 
    match arbre with 
    Nil -> acc
    | Node(a,gauche,droite) -> aux gauche (a::aux droite acc)
  in aux arbre [];;

let perfect arbre =
  let rec aux arbre = 
    match arbre with 
    Nil -> (true,0)
    |Node(a,gauche,droite) -> 
      let (pg,hg) = aux gauche in 
      let (pd,hd) = aux droite in 
      (pg && pd && hg = hd, 1+max hd hg) in let (parfait,_) = aux arbre in parfait;; 

let rec contains_bst arbre elt = 
  match arbre with 
  Nil -> false
  |Node(a,gauche,droite) -> if a = elt then true else if a < elt then contains_bst droite elt else contains_bst gauche elt;;

let rec add_bst arbre elt = 
  match arbre with 
  Nil -> Node(elt,Nil,Nil)
  |Node(a,gauche,droite) -> if a = elt then arbre else if a > elt then Node(a, add_bst gauche elt, droite) else Node(a,gauche,add_bst droite elt);;


