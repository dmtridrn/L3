
type 'a tree =
| Leaf of 'a
| Node of 'a tree * 'a tree

let rec size = function
| Leaf _ -> 1
| Node(pairs,impairs) -> size pairs + size impairs

let rec get abr idx = 
  match abr with 
  Leaf(a) -> a
  |Node(g,d) -> if idx mod 2 = 0 then get g (idx/2) else get d (idx/2);;

let rec set abr idx elt = 
  if idx >= size abr then raise(Invalid_argument("")) else
    match abr with 
    Leaf(a) -> Leaf(elt)
    | Node(g,d) -> if idx mod 2 = 0 then Node(set g (idx/2) elt, d) else Node (g, set d (idx/2) elt);;

let est_feuille = function Leaf(_) -> true |Node(a,b) -> false;;
let rec tail abr = 
  match abr with 
  Leaf(a) -> raise(Invalid_argument(""))
  | Node(g,d) -> if est_feuille g then d else Node(tail g, d);;

let to_list abr = 
  let rec aux acc arbr i = 
    match arbr with 
    Leaf(a) -> List.rev (a::acc)
    | Node(g,d) -> aux ((get arbr i )::acc) (tail arbr) (i+1) 
  in aux [] abr 0;;

let exemple1 = Node (Node (Leaf 'a', Leaf 'c'), Leaf 'b');;
let exemple2 = Node (Node (Node (Leaf 3, Leaf 2), Leaf 6), Node (Leaf 1, Leaf 7));;

to_list exemple2;;

