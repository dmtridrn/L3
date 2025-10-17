(*TYPE PARTIEL EN AMPHI*)

let decode liste = 
  let rec aux liste acc = 
    match liste with
    [] -> List.rev acc
    |(a,b)::reste -> if b = 0 then aux reste acc else aux ((a,b-1)::reste) (a::acc)
  in aux liste [];;


let rec add valeur nombre liste = 
    match liste with 
    [] -> [((valeur, nombre))]
    |(a,b)::reste -> if a = valeur then (a,b+1)::reste else (a,b)::add valeur nombre reste;;

let encode liste = 
  let rec aux liste acc = 
    match liste with
    [] -> acc
    |a::reste -> aux reste (add a 1 acc)
  in aux liste [];;

let code_map f liste = 
  let rec aux f liste acc =
    match liste with
    [] -> List.rev acc
    | (a,b)::reste -> if b = 0 then aux f reste acc else aux f ((a,b-1)::reste) (add (f a) 1 acc)
  in aux f liste [];;



(*ANNALE EXAM 2023*)
(*EXO 2*)

let comp_gauche liste = 
  match liste with
  [] | [_] -> liste
  | a::b::reste -> (a+b)::reste

let comps_gauche liste = 
  let rec aux liste acc = 
    match liste with
    [] -> acc
    |[a] -> [a]::acc
    |a::b::reste -> aux (comp_gauche liste) (liste::acc)
  in List.rev (aux liste []);;


(*2024*)
(*EXO 3*)

type 'a btree = 
  F of 'a
  | I of 'a * 'a btree * 'a btree

let rec liste_feuilles arbre = 
  match arbre with 
  | F a -> a::[]
  | I(a,b,c) -> (liste_feuilles b)@(liste_feuilles c);;

let rec cons_parfait n e = 
  match n with
  0 -> F e
  |_ -> I(e, cons_parfait (n-1) e, cons_parfait (n-1) e);;

let rec eten a e n = 
  match a with
  F f -> cons_parfait n e
  | I(z,b,c) -> I(z,eten b e n, eten c e n);;


let rec verif_arbre arbre = 
  match arbre with
  F _ -> true
  |I(a,g,d) -> 
    let labg = match g with
                F a -> a
                |I(a,_,_) -> a
  in let labd = match d with 
                F a -> a 
                |I(a,_,_) -> a
in labg = "0"^a && labd = "1"^a && verif_arbre g && verif_arbre d;;


let rec cons_parfait_be e n = 
  match n with 
  0 -> F e
  | _ -> I(e, cons_parfait_be ("0"^e)(n-1), cons_parfait_be ("1"^e) (n-1));;


(*MODE CUSTOM*)

type 'a tree = 
  Nil 
  | Node of 'a * 'a tree * 'a tree

let rec count_leaves arbre = 
  match arbre with
  Nil -> 0
  | Node(_, Nil,Nil) -> 1
  | Node(a,gauche,droite) -> count_leaves gauche + count_leaves droite;;

let rec mirror arbre =  
  match arbre with 
  Nil -> Nil
  |Node(a,gauche,droite) -> Node(a,mirror droite, mirror gauche);;

let rec balanced arbre = 
  let rec aux arbre =
  match arbre with 
  Nil -> (true,0) 
  | Node(a,gauche,droite) -> 
    let (perf_g,hg) = aux gauche in
    let (perf_d,hd) = aux droite in 
    (perf_d && perf_g && hd = hg, 1+max hd hg) 
  in 
  let (parfait,_) = aux arbre in parfait;;  

let same_shape arbre1 arbre2 = 
  let rec aux a1 a2 = 
    match a1,a2 with
      Nil,Nil -> true
      |Node(_,g,d),Node(_,f,h) -> aux g f && aux d h
      |_ -> false
    in aux arbre1 arbre2;; 

let count_occurences arbre e = 
  let rec aux arbre e =
    match arbre with 
    Nil -> 0
    |Node(a,gauche,droite) -> if a = e then 1 + aux gauche e + aux droite e else aux gauche e + aux droite e
  in aux arbre e;;

let parcours_infixe arbre = 
  let rec aux arbre acc = 
    match arbre with 
    Nil -> acc
    |Node(a,gauche,droite) -> 
      aux gauche (a::aux droite acc)
    in aux arbre [];;

let rec min_bst arbre = 
  match arbre with
  |Nil -> None
  |Node(a,Nil,Nil) -> Some a
  |Node(a,gauche,droite) -> min_bst gauche;;