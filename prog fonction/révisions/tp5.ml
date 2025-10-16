type formula =
  | Prop of string
  | Neg of formula
  | And of formula * formula
  | Or of formula * formula;;

let rec string_of_formula formule = 
  match formule with
  Prop(a) -> a
  |Neg(a) -> "¬" ^ string_of_formula a
  |And(f1,f2) -> "("^string_of_formula f1 ^ " AND " ^ string_of_formula f2 ^")"
  |Or(f1,f2) -> "("^string_of_formula f1 ^ " OR " ^ string_of_formula f2 ^")";;

let list_of_props formule = 
  let rec aux formule acc =
    match formule with
    Prop s -> s::acc
    |Neg s -> aux s acc
    |And(s,d) | Or (s,d) -> List.sort_uniq compare (aux s acc @ aux d acc)
  in aux formule [];;

let rec eval_formula formule inter = 
  match formule with
  Prop a -> List.assoc a inter
  |Neg a -> not (eval_formula a inter)
  |And(a,b) -> eval_formula a inter && eval_formula b inter
  |Or(a,b) -> eval_formula a inter || eval_formula b inter;;

let add_to_all elt liste = 
  List.map (fun x -> elt::x) liste;;

let interpretations_props liste = 
  let rec aux liste acc =
  match liste with
  | [] -> acc
  | a::reste ->
      aux reste ((add_to_all (a,true) acc) @ (add_to_all (a,false) acc))
  in aux liste [[]];;

let interpretations formule = 
interpretations_props (list_of_props formule);;

let satifiable formule = 
  List.exists (fun inter -> eval_formula formule inter) (interpretations formule);;
let tautology formule = 
  List.for_all (fun inter -> eval_formula formule inter) (interpretations formule);;

let is_cons f1 f2 = 
  tautology (Or(Neg (f1), f2));;

let is_equ f1 f2 = 
  (is_cons f1 f2 && is_cons f2 f1);;

let rec desc_neg formule = 
  match formule with 
  Prop s -> formule
  |Neg(Neg(s)) -> desc_neg s
  |Neg(And(a,b)) -> desc_neg (Or(Neg a, Neg b))
  |Neg(Or(a,b)) -> desc_neg (And(Neg a, Neg b))
  |Neg a -> a
  |And(a, b) -> And(desc_neg a, desc_neg b)
  |Or(a, b) -> Or(desc_neg a, desc_neg b);;


