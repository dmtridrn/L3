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
  | Node (a, gauche, droite) -> a + sum gauche + sum droite;;

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

let rec contains_bst elt arbre = 
  match arbre with
  Nil -> false
  | Node(a,gauche,droite) -> if a = elt then true else if a > elt then contains_bst elt gauche else contains_bst elt droite;;

let rec add_bst arbre elt = 
  match arbre with
  Nil -> Node(elt,Nil,Nil)
  | Node(a,gauche,droite) -> 
    if a = elt then arbre else 
      if a < elt then Node(a,gauche, add_bst droite elt) else Node(a, add_bst gauche elt, droite);;

let bst_of_list liste = 
  let rec aux liste arbre = 
    match liste with 
    [] -> arbre
    |a::reste -> aux reste (add_bst arbre a)
  in aux liste Nil;;

let split liste = 
  let mid = (List.length liste)/2 in
  let rec aux liste acc1 acc2 = 
    match liste with 
    [] -> (List.rev acc1, List.rev acc2)
    | a::reste -> if List.length acc1 = mid then aux reste acc1 (a::acc2) else aux reste (a::acc1) acc2
  in aux liste [] [];;
    
let rec bst_of_list_opt liste = 
  match liste with 
  []-> Nil
  | _ ->
    let mid = (List.length liste)/2 in
    let pivot = List.nth liste mid in 
    let (gauche,droite) = split liste in 
    let vdroite = 
      match droite with 
      [] -> []
      |a::reste -> reste in 
    Node(pivot , bst_of_list_opt gauche, bst_of_list_opt vdroite);;


let is_bst arbre = 
  let liste = elements arbre in 
  let rec is_sorted liste = 
    match liste with 
    [] -> true
    | [a] -> true
    | a::b::reste -> if a > b then false else is_sorted (b::reste)
  in is_sorted liste;;
  
let rec forall_labels p arbre = 
  match arbre with
  Nil -> true
  | Node(a,gauche,droite) -> p a && forall_labels p gauche && forall_labels p droite;;

let rec is_uniform elt arbre = 
  forall_labels (fun x -> x=elt) arbre;;

let rec forall_subtrees p arbre = 
  match arbre with
  Nil -> true
  | Node(a,gauche,droite) -> p a gauche droite && forall_subtrees p gauche && forall_subtrees p droite;;

let is_right_comb arbre = 
  forall_subtrees (fun a gauche droite-> gauche = Nil) arbre;;

let rec fold_tree fn vf a =
  match a with
    | Nil -> vf
    | Node(n, g, d) -> fn n (fold_tree fn vf g) (fold_tree fn vf d);;

let sum2 arbre = 
  fold_tree (fun x y z -> x+y+z) 0 arbre;;

let map_tree f arbre = 
  fold_tree (fun x gauche droite -> Node(f x, gauche,droite)) Nil arbre;;