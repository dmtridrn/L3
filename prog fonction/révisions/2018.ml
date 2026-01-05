(*exo 2*)
let checkparfait n = 
  let rec aux s i = 
    if i > n/2 then s = n else
      if n mod i = 0 then aux (s+i) (i+1) 
      else aux s (i+1)
    in aux 1 2;;

let rec exists_perfect liste = 
  match liste with 
  [] -> false 
  | a::reste -> checkparfait a || exists_perfect reste;;


  (*****exo 3*****)
type 'a tree = Node of 'a * ('a tree list)

let rec size tr = 
  match tr with 
  Node(a, liste) -> List.fold_left (fun acc fils -> acc + size fils) 1 liste;;

let rec tree_map f tr = 
  match tr with
  Node(a, liste) -> Node(f a, List.map (tree_map f) liste);;

let rec tree_fold f tr acc = 
  match tr with 
  Node(a,liste) -> f a (List.fold_right (tree_fold f) liste acc);;


let t1 = Node(3, [Node(4, []); Node(5, []); Node(4, [Node(1, [])])]);;
tree_map (fun x -> x+1) t1;;

  (*****exo 4*****)

let is_space car = 
  car = ' ' || car = '\n' || car = '\t' || car = '\r';;
let is_letter car = 
  not (is_space car);;

let first index f str = 
  
