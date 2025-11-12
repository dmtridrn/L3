type transitions = int -> (int list)
type graph = {size : int; fwd : transitions}

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

let accessible f x y = 
  let rec aux vus s = 
    if s = y then true else
    if List.mem s vus then false else
      List.exists (fun v -> aux (s::vus) v) (f s)
    in aux [] x;;

let modify g x l =
  let new_fwd y =
    if y = x then l
    else g.fwd y
  in
  {size = g.size; fwd = new_fwd};;

let un_completion g =
  let new_fwd p =
    let direct = g.fwd p in
    let indirect =
      List.flatten (List.map (fun q -> g.fwd q) direct)
    in
    List.sort_uniq compare (direct @ indirect)
  in
  {size = g.size; fwd = new_fwd}

