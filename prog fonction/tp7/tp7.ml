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
  {size = g.size; fwd = new_fwd};;

let equal g1 g2 = 
  if g1.size != g2.size then false else
    let rec aux curr =
      if curr = g1.size then true else
      let v1 = g1.fwd curr in 
      let v2 = g2.fwd curr in 
      if v1<>v2 then false else
        aux (curr+1)
    in aux 0;;

let rec completion_max g =
  let g2 = un_completion g in 
  if equal g g2 then g else 
    completion_max g2;; 

let rec connexe g = 
  let graph = completion_max g in
  let rec aux curr = 
    if curr = graph.size then true else
      let check = graph.fwd curr in 
      if List.length check != graph.size then false else 
        aux (curr+1)
      in aux 0;;