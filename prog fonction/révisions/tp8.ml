let rec find f l = 
  match l with 
  [] -> raise(Not_found)
  | a::reste -> if f a then a else find f reste;;

let rec find_opt f l = 
  match l with
  [] -> None
  | a::reste -> if f a then Some a else find_opt f reste;;

let assoc a l = 
  snd (find (fun x-> fst x = a) l);;

let assoc_opt a l =
  match find_opt (fun x-> fst x = a) l with
  None -> None
  | Some paire -> Some (snd paire);;

type tree =
| Leaf of int
| Node of tree * tree

let path_to_leaf n arbre = 
  let rec aux n arbre acc = 
    match arbre with
    Leaf(a) -> if a = n then acc else raise(Not_found)
    | Node(g,d) -> try aux n g ('g'::acc) with Not_found -> aux n d ('d'::acc)
  in aux n arbre [];;

type operator = Add | Sub | Mul | Div
type expression =
| Const of int
| Var of string
| Op of operator * expression * expression


exception Undefined_variable of string
exception Division_by_zero

let rec eval ope env = 
  match ope with
  Const(a) -> a
  | Var(a) -> (try assoc a env with Not_found -> raise(Undefined_variable a))
  | Op(a, e1, e2) -> 
    let v1 = eval e1 env in 
    let v2 = eval e2 env in 
    match a with 
    Add -> v1 + v2 
    | Sub -> v1-v2
    | Mul -> v1*v2
    | Div -> if v2 = 0 then raise Division_by_zero else v1/v2;;

