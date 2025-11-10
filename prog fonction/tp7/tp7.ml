type transitions = int -> (int list)
type graph = {size : int;fwd : transitions}

let f x = match x with
  0 -> [2]
  | 1 -> []
  | 2 -> [0;1]
  |_ -> [];;

let rec chemin f l =
  match l with
  [] -> false
  |[a] -> true
  |a::b::reste -> List.mem b (f a) && chemin f (b::reste);;

let atteints f k x = 
  let rec aux fonc k x acc = 
    match k with
    0 -> acc
    | _ -> let next = 
      match fonc x with
      [] -> None 
      | a::reste -> if not (List.mem a acc) then Some a else None 
    in aux fonc (k-1) next acc 
  in aux f k x [];;
