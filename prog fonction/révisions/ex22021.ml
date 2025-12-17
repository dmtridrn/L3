let decode l = 
  let rec aux acc l = 
    match l with 
    [] -> List.rev acc
    | (a,b)::reste -> if b = 0 then aux acc reste else aux (a::acc) ((a,b-1)::reste)
  in aux [] l;;


let add v n l = 
  if n = 0 then l else
  match l with
  [] -> (v,n)::l
  | (a,b)::reste ->
    if a = v then (a,b+n)::reste else (v,n)::((a,b)::reste)


let encode l = 
  let rec aux l acc = 
    match l with 
    [] -> List.rev acc 
    | a::reste -> aux reste (add a 1 acc)
  in aux l [];;

let code_map f lr = 
  let rec aux lr acc =
    match lr with 
    [] -> List.rev acc
    | (v, n)::reste -> aux reste (add (f v) n acc)
  in aux lr [];;

type 'a tree =
| Node of 'a tree * 'a * 'a tree
| Leaf
type pos = int (* positions via des entiers strictement positifs *)
