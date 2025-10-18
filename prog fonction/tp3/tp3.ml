let choose liste = 
  match liste with
    [] -> failwith("liste vide")
    | _ -> 
      let len = List.length liste in 
      let index = Random.int len in 
      List.nth liste index;;

let choose_elements liste nombre = 
  if nombre > List.length liste then failwith "pas assez d'éléments" else 
  let rec aux liste nbr acc indices = 
    match nbr with
    0 -> acc
    | _ -> let idx = Random.int (List.length liste) in 
           if List.mem idx indices then aux liste nbr acc indices 
           else aux liste (nbr-1) ((List.nth liste idx)::acc) (idx::indices)
          in aux liste nombre [] [];;

let choose_sublist liste taille = 
  if taille > List.length liste then failwith "pas assez d'éléments" else 
  let rec aux liste nbr accl acci = 
    match nbr with
    0 -> List.rev accl
    | _ -> let idx = Random.int (List.length liste) in
           if idx <= acci || (idx+nbr) > List.length liste then aux liste nbr accl acci
           else aux liste (nbr-1) ((List.nth liste idx)::accl) idx
          in aux liste taille [] (-1);;

let insert element liste = 
  let rec aux elt l1  = 
    match l1 with 
    [] -> elt::l1
    | a::reste -> if a = elt then l1 else if a > elt then elt::l1 else a::(aux elt reste)
in aux element liste;;


let sort liste = 
  let rec aux l1 acc = 
    match l1 with
    [] -> acc
    | a::reste -> aux reste (insert a acc)
  in aux liste [];;


let rec mem_sorted liste  element =
  match liste with
  [] -> false
  | a::reste -> if a = element then true else if a < element then mem_sorted reste element else false;;

let rec union_sorted liste1 liste2 = 
  match (liste1, liste2) with 
  ([], l) | (l, []) -> l
  | (a::reste1, b::reste2) ->
    if a = b then a :: union_sorted reste1 reste2
    else if a < b then a :: union_sorted reste1 liste2
    else b :: union_sorted liste1 reste2;;;;

let rec inter_sorted liste1 liste2 = 
  match (liste1,liste2) with
  ([],l) | (l,[]) -> []
  | (a::reste1,b::reste2) -> 
    if a = b then a::inter_sorted reste1 reste2
    else if a < b then inter_sorted reste1 liste2
    else inter_sorted liste1 reste2;;

let rec quicksort liste = 
  match liste with 
  [] -> []
  | a::reste -> 
    let rec aux l1 acc1 acc2 pivot = 
      match l1 with
      [] -> (acc1,acc2)
      |a::reste -> if a > pivot then aux reste acc1 (a::acc2) pivot
                        else aux reste (a::acc1) acc2 pivot
                      in let (petits,grands) = aux reste [] [] a in 
quicksort petits @ [a] @ quicksort grands;; 


                    