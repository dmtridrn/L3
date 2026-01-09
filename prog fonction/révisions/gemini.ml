let decode liste = 
  let rec aux liste acc curr = 
    match liste with 
    [] -> List.rev acc
    | a::reste -> aux reste ((a+curr)::acc) a
  in aux liste [] 0;;


let encode liste = 
  let rec aux liste acc curr = 
    match liste with 
    [] -> List.rev acc
    | a::reste -> aux reste ((a-curr)::acc) a
  in aux liste [] 0;;

decode (encode [10;13;12;15]);;