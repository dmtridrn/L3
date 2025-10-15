type 'a tree = 
  Nil 
  | Node of 'a * 'a tree * 'a tree

let rec size arbre = 
  match arbre with
  Nil -> 0
  | Node(a, gauche, droite) -> (1 + size gauche + size droite);;


let rec depth = function
  Nil -> 0
  | Node (a, gauche, droite) -> 1 + max (depth gauche) (depth droite);;


let rec sum = function
  Nil -> 0
  |Node(a,gauche,droite) -> a + sum gauche + sum droite;;

let rec contains element arbre =
  match arbre with
  Nil -> false
  |Node(a,gauche,droite) -> if a = element then true 
                            else contains element gauche || contains element droite;;

let elements arbre = 
  let rec aux arbre acc = 
    match arbre with
    Nil -> acc
    | Node(a,gauche,droite) -> 
      aux gauche (a :: aux droite acc)
    in aux arbre [];;

let perfect arbre = 
  let rec aux arbre = 
    match arbre with
    | Nil -> (true, 0)
    | Node (a, gauche, droite) -> 
      let (parfait_g,hg) = aux gauche in 
      let (parfait_d,hd) = aux droite in 
      (parfait_d && parfait_g && hg = hd, 1 + max hg hd)
    in 
    let (parfait, _) = aux arbre in parfait;;


let rec contains_bst arbre element = 
  match arbre with  
    Nil -> false
    | Node (a,gauche, droite) -> if a = element then true else 
                                  if a < element then contains_bst droite element 
                                  else contains_bst gauche element;;

let rec add_bst arbre element = 
  match arbre with
  Nil -> Node(element, Nil, Nil)
  | Node(a, gauche, droite) -> 
    if a = element then arbre else
      if a < element then Node(a,gauche,add_bst droite element) else Node(a,add_bst gauche element,droite);;


let bst_of_list liste = 
  let rec aux liste arbre = 
    match liste with 
    [] -> arbre
    | a::reste -> aux reste (add_bst arbre a)
  in aux liste Nil;;

let split liste = 
  let mid = (List.length liste) / 2 in
  let rec aux liste acc1 acc2 = 
    match liste with
    [] -> (List.rev acc1, List.rev acc2)
    |a::reste -> if List.length acc1 = mid then aux reste acc1 (a::acc2) else 
                    aux reste (a::acc1) acc2
    in aux liste [] [];;

let rec  bst_of_list_opt liste = 
  match liste with 
  [] -> Nil
  | _ -> 
    let mid = (List.length liste) / 2 in 
    let pivot = List.nth liste mid in 
    let (gauche,droite) = split liste in 
    let vdroite = match droite with 
    [] -> []
    |a::reste -> reste 
  in Node(pivot, bst_of_list_opt gauche, bst_of_list_opt vdroite);;

let is_bst arbre = 
  let liste = elements arbre in 
  let rec is_sorted liste = 
    match liste with 
    [] -> true
    | [a] -> true
    |a::b::reste -> if a < b then is_sorted (b::reste) else false
  in is_sorted liste;;

let rec forall_labels f arbre = 
  match arbre with 
  Nil -> true
  | Node(elt,gauche,droite) -> f elt && forall_labels f gauche && forall_labels f droite;;

let is_uniform elt arbre = 
  forall_labels (function x -> x = elt) arbre;;

let rec forall_subtrees f arbre = 
  match arbre with 
  Nil -> true 
  |Node(a,gauche,droite) -> f a gauche droite && forall_subtrees f gauche && forall_subtrees f droite;;

let is_right_comb arbre = 
  forall_subtrees (fun a gauche droite -> gauche = Nil) arbre;;

let rec fold_tree fn vf a = 
  match a with
  Nil -> vf
  | Node (n,g,d) -> fn n (fold_tree fn vf g) (fold_tree fn vf d);;

let sum2 arbre = 
  fold_tree (fun x gauche droite -> x + gauche + droite) 0 arbre;;
  
let map_tree f arbre = 
  fold_tree (fun x droite gauche -> Node(f x, droite, gauche)) Nil arbre;;

let arbre1 = Node (5, Nil, Nil);;

let arbre2 = Node (10, 
                   Node (5, Nil, Nil), 
                   Node (15, Nil, Nil));;

forall_labels (function x -> x<10) arbre2;;

let arbre3 = Node (20,
                   Node (10, Node (5, Nil, Nil), Nil),
                   Node (30, Nil, Node (35, Nil, Node(4,Nil,Nil))));;
