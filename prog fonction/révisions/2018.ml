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

let first_index f str = 
    let rec aux acc = 
      if acc = String.length str then (acc, 0) else
      if f (String.get str acc) then (acc, (String.length str) - acc) else aux (acc+1)
    in aux 0;;

let trim str = 
  let rec aux acc = 
    if acc = String.length str then acc else
    if is_letter (String.get str acc) then acc else aux (acc + 1) in 
    let idx = aux 0 in 
    String.sub str idx ((String.length str) - idx);;

let cut_first str = 
  if trim str = "" then raise(Not_found) else 
    let nvstr = trim str in 
    let sep = first_index is_space nvstr in 
    let premier = String.sub nvstr 0 (fst sep) in 
    let deuxieme = String.sub nvstr (fst sep) ((String.length nvstr)-(fst sep))
  in (premier,deuxieme);;

let explode str = 
  let rec aux soustr acc = 
    try 
      let couple = cut_first soustr in 
      aux (snd couple) ((fst couple) :: acc)
    with Not_found -> List.rev acc
  in aux str [];;

let format k str = 
  let liste = explode str in 
  let rec aux acc sousliste lencurr = 
    match sousliste with 
    [] -> acc 
    |a::reste -> 
      if (lencurr + (String.length a) + 1) > k then aux (acc^"\n") sousliste 0
      else aux (acc^a^" ") reste ((lencurr + String.length a)+1)
  in aux "" liste 0;;
