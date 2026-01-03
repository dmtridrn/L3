type transitions = int -> (int list)
type graph = {size : int;fwd : transitions}

let tran = function
  0 -> [2]
  |1 -> []
  |2 -> [0;1]
  |_ -> [];;
let rec chemin f l = 
  match l with
  [] | [_] -> true
  | a::b::reste -> if List.mem b (f a) then chemin f (b::reste) else false;;

