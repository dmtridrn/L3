let pesee_max liste = 
  List.fold_left (fun acc x -> acc + x) 0 liste;;

let fusion liste1 liste2 = 
  List.sort_uniq compare (liste1@liste2);;

let pesee_simple liste = 
  List.fold_left (fun acc x -> 
    let new_sommes = List.map (fun s -> s+x) acc in 
    fusion acc new_sommes) [0] liste;;

let pesee_complexe liste = 
  List.fold_left (fun acc x -> 
    let new_sommes = List.map (fun s -> s+x) acc in
    let new_sous = List.map (fun s -> abs(s-x)) acc in 
    fusion (fusion acc new_sommes) new_sous) [0] liste;;

let pesee_complete liste = 
  List.length (pesee_complexe liste) = (pesee_max liste)+1;;

type 'a tree =
| Leaf of 'a
| Node of 'a tree * 'a tree

let rec size = function
| Leaf _ -> 1
| Node(pairs,impairs) -> size pairs + size impairs

let rec get arbre idx = 
  match arbre with 
  Leaf(a) -> if idx = 0 then a else raise(Invalid_argument("indice"))  
  | Node(g,d) -> if idx mod 2 = 0 then get g (idx/2) else get d (idx/2);;

let rec set arbre idx elt = 
  match arbre with 
  Leaf(a) -> if idx = 0 then Leaf(elt) else raise(Invalid_argument("indice"))
  | Node(g,d) -> if idx mod 2 = 0 then Node(set g (idx/2) elt, d) else Node(g, set d (idx/2) elt);;

let rec tail arbre = 
  match arbre with 
  Leaf(a) -> raise(Failure("arbre est feuille"))
  | Node(g,d) -> match g with 
                  Leaf(_) -> d
                  | Node(x,y) -> Node(d, tail g);;

let to_list arbre = 
  let rec aux arbre acc =
    match arbre with 
    Leaf(a) -> List.rev (a::acc)
    | Node(g,d) -> aux (tail arbre) ((get arbre 0)::acc) 
  in aux arbre [];;

let rec cons_gauche elt arbre= 
  match arbre with 
  Leaf(a) -> Node(Leaf(elt),Leaf(a))
  | Node(g,d) -> Node(cons_gauche elt d, g);;

let rec cons_droite arbre elt = 
  let liste = List.rev (to_list arbre) in 
  let rec aux liste acc = 
    match liste with
    [] -> acc
    | a::reste -> aux reste (cons_gauche a acc)
  in aux liste (Leaf(elt));;


let exemple2 = Node (Node (Node (Leaf 3, Leaf 2), Leaf 6), Node (Leaf 1, Leaf 7));;
let exemple1 = Node (Node (Leaf 'a', Leaf 'c'), Leaf 'b');;

cons_droite (Node (Leaf 'a', Leaf 'b')) 'c';;