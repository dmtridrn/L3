module type SET = sig
  type 'a set 
  val empty : 'a set
  val add : 'a -> 'a set -> 'a set
  val element: 'a -> 'a set -> bool
  val debug : 'a set -> 'a list  
end


module Set : SET = struct
  type 'a set = 'a list         
  let empty = []
  let add x set = if List.mem x set then set else x::set
  let element x set = List.mem x set
  let debug s = s
end


module Set_abr : SET = struct

  type 'a set = 
  | Empty
  | Node of 'a * 'a set * 'a set

  let empty = Empty

  let rec add x set = 
    match set with 
    Empty -> Node(x,Empty,Empty)
    |Node(a,g,d) -> if x = a then set else if x < a then Node(a, add x g, d) else Node(a,g,add x d)
  
  let rec element x set = match set with
    |Empty -> false
    |Node(a,g,d) -> if x = a then true else if x < a then element x g else element x d

  let debug set = 
    let rec aux arbre acc = 
    match arbre with
    Empty -> acc
    | Node(a,gauche,droite) -> aux gauche (a :: aux droite acc)
    in aux set [];;

end 

module type SET_USER = sig
  type 'a set 
    val element: 'a -> 'a set -> bool
end

module type SET_ADMIN = sig
  type 'a set
  val empty : 'a set
  val add : 'a -> 'a set -> 'a set
end
