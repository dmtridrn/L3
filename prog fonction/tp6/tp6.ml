let rec listn n =
  if n = 0 then [0]
  else n :: (listn (n - 1));;

let listnterm n = 
  let rec aux n acc = 
    match n with
    0 -> List.rev acc
    |_ -> aux (n-1) (n::acc)
  in aux n [];;

let rec length l = match l with
  | [] -> 0
  | _ :: l' -> 1 + (length l')

let lengthterm l = 
  let rec aux liste acc = 
    match liste with
    [] -> acc
    | a::reste -> aux reste (acc+1)
  in aux l 0;;

let rec rev_append liste1 liste2 = 
  match liste1 with
  [] -> liste2
  | a::reste -> rev_append reste (a::liste2);;

let append liste1 liste2 = 
  let liste3 = List.rev liste1 in rev_append liste3 liste2;;

append [1;2;3] [4;5;6];;

type 'a tree =
  | Nil
  | Node of 'a * 'a tree * 'a tree

let size_aux liste n = 
  let rec aux acc liste = 
    match liste with 
    [] -> acc
    | Nil::t -> aux acc t
    | Node(_,g,d) :: t -> aux (acc+1) (g::d::t)
  in aux liste n;;

let size t = 
  let liste = [t] in 
  size_aux 0 liste;;

let insert liste elt = 
    