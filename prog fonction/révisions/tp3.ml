let choose liste = List.nth liste (Random.int (List.length liste));;

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


let insert elt liste = 
  let rec aux elt liste acc = 
    match liste with 
    [] -> List.rev acc @ [elt]
    |a::reste -> if a < elt then aux elt reste (a::acc) else if a = elt then List.rev acc @ a::reste else List.rev acc @ [elt] @ a::reste
  in aux elt liste [];;

let sort liste = 
  let rec aux liste acc = 
    match liste with
    [] -> acc
    |a::reste -> aux reste (insert a acc)
  in aux liste [];;

