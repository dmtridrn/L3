type 'a tree = 
  Nil 
  | Node of 'a * 'a tree * 'a tree

let rec size arbre = 
  match arbre with
  Nil -> 0
  | Node (a, gauche, droite) -> 1 + size gauche + size droite;;

let rec depth arbre = 
  match arbre with
  Nil -> 0
  | Node(a,gauche,droite) -> 1 + max (depth gauche) (depth droite);;
  
let rec sum arbre = 
  match arbre with
  Nil -> 0
  | Node (a, gauche, droite) -> a + size gauche + size droite;;

let rec contains elt arbre = 
  match arbre with
  Nil -> false
  | Node(a,gauche,droite) -> if a = elt then true else contains elt gauche || contains elt droite;;

let elements arbre = 
  let rec aux arbre acc = 
    match arbre with
    Nil -> acc
    | Node(a,gauche,droite) -> aux gauche (a::aux droite acc)
  in aux arbre [];;

let perfect arbre = 
  let rec aux abre = 
    match arbre with
    Nil -> (true,0)
    | Node(a,gauche,droite) -> 
      let (parfait1,hg) = aux gauche in 
      let (parfait2,hd) = aux droite in 
      (parfait1 && parfait2 && hg = hd, 1+max hg hd)
    in let (parfait,_) = aux arbre in parfait;;