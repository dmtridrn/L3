let rec find p liste = 
  match liste with
  [] -> raise Not_found
  | a::reste -> if p a then a else find p reste;;

let rec find_opt p liste = 
  match liste with
  [] -> None
  | a::reste -> if p a then Some a else find_opt p reste;;

let assoc a liste = 
  snd (find (fun x -> fst x = a) liste);;

let assoc_opt a liste =
  find_opt (fun x -> fst x = a) liste;;




type tree =
  | Leaf of int
  | Node of tree * tree

let path_to_leaf n arbre = 
  let rec aux n arbre acc = 
    match arbre with 
      Leaf(a) -> if a = n then acc else raise Not_found
      | Node(gauche,droite) -> try aux n gauche ('g'::acc) with Not_found -> aux n droite ('d'::acc)
  in aux n arbre [];;



type operator = Add | Sub | Mul | Div
type expression =
  | Const of int
  | Var of string
  | Op of operator * expression * expression

exception Undefined_variable of string
exception Division_by_zero

let rec eval expr env = 
  match expr with
  Const(a) -> a
  | Var(a) -> (try assoc a env with Not_found -> raise (Undefined_variable a))
  | Op(o,e1,e2) -> 
    let v1 = eval e1 env in 
    let v2 = eval e2 env in 
    match o with
    Add -> v1 + v2
    | Sub -> v1 - v2
    | Mul -> v1 * v2
    | Div -> if v2 = 0 then raise Division_by_zero else v1/v2;;




exception Unknown_operator of char
exception Unmatched_parenthesis of int
exception Unexpected_character of char * int

let is_alphanumeric c = 
  match c with 
  '0'..'9' -> true
  | 'a'..'z' | 'A'..'Z' -> true
  |_ -> false;;

let op_of_char c = 
  match c with 
  '+' -> Add
  | '-' -> Sub
  | '*' -> Mul
  | '/' -> Div
  | a -> raise (Unknown_operator a);;

let find_next_symbol s start =
  let rec aux curr = 
    if curr = String.length s then String.length s else 
    if not (is_alphanumeric s.[curr]) then curr else aux (curr+1)
  in aux start;;

let find_matching_parenthesis str start = 
  let rec aux cpt curr = 
    if curr = String.length str then raise (Unmatched_parenthesis start) else 
      match str.[curr] with 
      | '(' -> aux (cpt+1) (curr+1) 
      | ')' -> if cpt = 0 then curr else aux (cpt-1) (curr+1)
      | _ -> aux cpt (curr+1)
  in aux 0 (start+1);;


let rec parse_operand s i = 
  match s.[i] with 
  '(' -> let nextpar = 
    find_matching_parenthesis s i in
    let expr = parse_expr s (i+1) nextpar
    in (expr, nextpar+1)
  | a -> if is_alphanumeric a then 
    let nextpos = find_next_symbol s i in 
  let symbol = String.sub s i (nextpos -i) in 
  try (Const (int_of_string symbol),nextpos) with Failure _ -> (Var(symbol),nextpos)
else raise (Unexpected_character (a,i))
and parse_expr s i k = 
  let operand1 = parse_operand s i in 
  if snd operand1 = k then fst operand1 else
    let operateur = op_of_char (s.[snd operand1]) in 
    let operand2 = parse_operand s (snd operand1 + 1) in 
    if (snd operand2) = k then Op(operateur, fst operand1, fst operand2) else
      raise (Unexpected_character (s.[snd operand2], snd operand2));;

