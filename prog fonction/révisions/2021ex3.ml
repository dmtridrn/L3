type 'a t = 'a list


let destruct lst =
  match lst with
  | [] -> None
  | hd :: tl -> Some (hd, tl)

let cons x xs = 
  x::xs;;

let empty = 
  [];;

let concat xs ys = 
  xs@ys;;

let map f lst = 
  List.map f lst;;
