let length liste = 
  let rec aux l1 acc = 
    match l1 with 
    [] -> acc
    |a::reste -> aux reste (acc+1)
  in aux liste 0;;

let list_sigma liste = 
  let rec aux l1 acc = 
    match l1 with
    [] -> acc
    |a::reste -> aux reste (acc+a)
  in aux liste 0;;

let rec append liste1 liste2 =
  match liste1 with
  [] -> liste2
  |a::reste -> a::(append reste liste2);;

let rev liste = 
  let rec aux l1 acc = 
    match l1 with 
    [] -> acc
    |a::reste -> aux reste (a::acc)
  in aux liste [];;

let split liste = 
  let rec aux l1 (acc1,acc2) = 
    match l1 with
    [] -> (rev acc1, rev acc2)
    | (a,b)::reste -> aux reste (a::acc1,b::acc2)
  in aux liste ([],[]);;

let flatten liste = 
  let rec aux l1 res = 
    match l1 with
    [] -> res
    |a::reste -> aux reste (append res a)
  in aux liste [];;

let rec mem elt liste = 
  match liste with
  [] -> false
  | a::reste -> if a = elt then true else mem elt reste;;

let simplify liste = 
  let rec aux l1 acc = 
    match l1 with 
    [] -> rev acc
    | a::reste -> if mem a acc then aux reste acc else aux reste (a::acc)
  in aux liste [];;

let successors elt liste = 
  let rec aux elt liste acc = 
    match liste with
      [] -> rev acc
      |a::reste -> 
        if a = elt then 
          match reste with 
            [] -> []
            |b::restant -> aux elt reste (b::acc)
        else aux elt reste acc
      in aux elt liste [];;

let list_min liste = 
  match liste with
  [] -> failwith("liste vide")
  |premier::reste -> 
    let rec aux l1 acc = 
      match l1 with
      [] -> acc
      |a::reste -> if a < acc then aux reste a else aux reste acc
    in aux reste premier;;

let map f liste = 
  let rec aux f l1 acc = 
    match l1 with
    [] -> rev acc
    |a::reste -> aux f reste ((f a)::acc)
  in aux f liste [];;

let exists p liste = 
  let rec aux p liste = 
    match liste with 
    [] -> false
    |a::reste -> if p a then true else aux p reste 
  in aux p liste;;

let for_all p liste = 
  let rec aux p liste = 
    match liste with 
    [] -> true
    |a::reste -> p a && aux p reste
  in aux p liste;;

let filter p liste = 
  let rec aux p liste acc = 
    match liste with
    [] -> rev acc
    | a::reste -> if p a then aux p reste (a::acc) else aux p reste acc
  in aux p liste [];;

let rec find p liste =
  match liste with
  [] -> failwith("élément non trouvé")
  | a::reste -> if p a then a else find p reste;;

let partition p liste = 
  let rec aux p liste acc1 acc2 = 
    match liste with 
    [] -> (rev acc1, rev acc2)
    |a::reste -> if p a then aux p reste (a::acc1) acc2 else aux p reste acc1 (a::acc2)
  in aux p liste [] [];;
