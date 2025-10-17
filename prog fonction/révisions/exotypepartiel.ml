let decode liste = 
  let rec aux liste acc = 
    match liste with
    [] -> List.rev acc
    |a::reste -> if snd a = 0 then aux reste acc else let nv = (fst a, (snd a)-1) in aux liste ((fst nv)::acc)
  in aux liste [];;

decode [('a',3); ('b',1); ('c',2)];;