type 'a vector = {
  mutable contents : 'a array;
  default : 'a;
  mutable size : int;
}

let create n a = {
  contents = Array.make n a;
  size = 0;
  default = a;
}

let of_list liste default capacity = 
  let n = List.length liste in 
  let tab = Array.make capacity default in 
  List.iteri (fun i x -> if i < capacity then tab.(i) <- x) liste;
    {
    contents = tab;
    size = n;
    default = default;
  };;

let get vect idx = 
  if idx < 0 || idx >= vect.size then
    raise(Invalid_argument "get")
  else
    vect.contents.(idx)

let set vect idx elt = 
  if idx < 0 || idx >= vect.size then
    raise(Invalid_argument "set")
  else
    vect.contents.(idx) <- elt;;

let eq x y = 
  x = y;;

let equal eq v1 v2 =
  if v1.size <> v2.size then false else
  let rec aux i = 
    if i = v1.size then true else
      if eq (get v1 i) (get v2 i) then aux (i+1) else false
    in aux 0;;

let clear vec = 
  Array.fill (vec.contents) 0 (vec.size) (vec.default);
  vec.size <- 0;;

let push_back vec elt = 
  if (vec.size)+1 > (Array.length vec.contents) then raise(Failure "pushback");
  vec.contents.(vec.size) <- elt; 
  vec.size <- vec.size + 1;;


let pop_back vec = 
  if vec.size = 0 then None 
  else
    let elt = vec.contents.(vec.size - 1) in     
    vec.contents.(vec.size - 1) <- vec.default;
    vec.size <- vec.size-1;
    Some elt;;