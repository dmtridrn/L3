let rec max_list l = 
  match l with 
  [] -> None
  | h::r -> match max_list r with 
            None -> Some h
            | Some m -> Some (max h m);;

let max_list_opt l = 
  let rec aux acc liste = 
    match liste with 
    [] -> acc
    | a::reste -> if acc = None then aux (Some a) reste else aux (max (Some a) acc) reste
  in aux None l;;

let flatten_opt l = 
  let rec aux acc liste = 
    match liste with 
    [] -> List.rev acc
    | a::reste -> aux (List.rev_append a acc) reste
  in aux [] l;;

type 'a btree = 
| F of 'a
| I of 'a * 'a btree * 'a btree

let liste_feuille arbre = 
  let rec aux acc abr = 
    match abr with 
    F(a) -> a::acc
    | I(v, g, d) -> (aux acc g)@(aux acc d)
  in aux [] arbre;;

let cons_parfait taille vale = 
  let rec aux n acc = 
    if n = 0 then acc else
    match acc with 
    F(a) -> aux (n-1) (I(a, F(a), F(a)))
    | I(a,g,d) -> I(a, aux (n-1) g, aux (n-1) d)
  in aux taille (F(vale));;

let rec eten arbre etiqu taille = 
  match arbre with 
  F(a) -> if a = etiqu then cons_parfait taille a else F(a) 
  |I(v,g,d) -> I(v, (eten g etiqu taille), (eten d etiqu taille));;

let rec verif_arbre arbre = 
  match arbre with 
  F(a) -> true 
  | I(a,g,d) -> let resg = match g with 
                F(b) -> if b <> "0"^a then false else verif_arbre g
                |I(b,g2,d2) -> verif_arbre g2 && verif_arbre d2
                in let resd = match d with 
                F(b) -> if b <> "1"^a then false else verif_arbre g
                |I(b,g2,d2) -> verif_arbre g2 && verif_arbre d2
              in resg && resd;;

let cons_arbre_be et taille = 
  let rec aux acc n = 
    if n = 0 then acc else
    match acc with 
    |F(a) -> let (fg,fd) = (F("0"^a), F("1"^a)) in aux (I(a, fg, fd)) n
    |I(a,g,d) -> I(a, (aux g (n-1)), (aux d (n-1)))
  in aux (F(et)) taille;;





let ab1 = I("a", F("a"), F("a"));;
let ab2 = I("", I("0", F("00"), F("10")), I("1", F("01"), F("11")));;

cons_arbre_be "" 2;;