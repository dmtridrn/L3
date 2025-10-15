let length l = 
  let rec count cpt reste =
    match reste with
    [] -> cpt
    | _::restant -> count (cpt+1) restant
  in count 0 l;;

let list_sigma l = 
  let rec acc curr reste = 
    match reste with
    [] -> curr
    | a::restant -> acc(curr + a) restant
  in acc 0 l;;

let rec append l1 l2 = 
  match l1 with
  [] -> l2
  | h1 :: r1 -> h1 :: (append r1 l2);;

let rev liste = 
  let rec aux l1 restant = 
    match restant with
    [] -> l1
    | a::reste -> aux(a::l1) reste
  in aux [] liste;;

let split liste = 
  let rec aux l1 l2 restant =
    match restant with
    [] -> (rev l1, rev l2)
    | (a,b)::reste -> aux(a::l1)(b::l2) reste
  in aux [] [] liste;;

let flatten liste = 
  let rec aux res list = 
    match list with
    [] -> rev res
    | sousliste::restant -> 
      let rec ajout l1 acc = 
        match l1 with
        [] -> acc
        | a::next -> ajout next (a::acc)
      in let final = ajout sousliste res in aux final restant
    in aux [] liste;;

let rec mem elt liste = 
  match liste with
  [] -> false
  | a::restant -> if elt = a then true else mem elt restant;;

let rec simplify liste = 
  let rec aux acc l1 = 
    match l1 with
    [] -> rev acc
    | a::restant -> if mem a acc then aux acc restant else aux (a::acc) restant
  in aux [] liste;;

let successors elt liste = 
  let rec aux acc l1 = 
    match l1 with
    [] -> rev acc
    | elmt::a::restant -> if elmt = elt then aux(a::acc) (a::restant) else aux acc (a::restant)
    | b::restant -> aux acc restant
  in aux [] liste;;

let list_min liste = 
  match liste with
  [] -> failwith "liste vide"
  | premier::restant ->
    let rec aux curr l1 = 
      match l1 with
      [] -> curr
      | a::restant -> if a < curr then aux a restant else aux curr restant
    in aux premier restant;;

let map f liste = 
  let rec aux acc g l1 = 
    match l1 with
    [] -> rev acc
    | a::restant -> aux((g a)::acc) g restant
  in aux [] f liste;;

let rec exists p liste = 
  match liste with
  [] -> false
  | a::restant -> if p a = true then true else exists p restant;;

let rec for_all p liste = 
  match liste with
  [] -> true
  | a::restant -> if p a = true then for_all p restant else false;;

let filter p liste = 
  let rec aux acc g l1 = 
    match l1 with
    [] -> rev acc
    | a::restant -> if g a = true then aux(a::acc) g restant else aux acc g restant
  in aux [] p liste;;

let rec find p liste =
  match liste with
  [] -> failwith "aucun élément ne respecte le prédicat"
  | a::restant -> if p a = true then a else find p restant;;
  
let partition p liste = 
  let rec aux l1 l2 g reste = 
    match reste with
    [] -> rev l1, rev l2
    | a::restant -> if g a = true then aux(a::l1) l2 g restant else aux l1 (a::l2) g restant
  in aux [] [] p liste;;

