type formula =
  | Prop of string
  | Neg of formula
  | And of formula * formula
  | Or of formula * formula;;

let rec string_of_formula formule =
  match formule with
  Prop s -> s
  |Neg f -> "¬" ^ string_of_formula f 
  |And (f1,f2) -> "(" ^ string_of_formula f1 ^ "AND" ^ string_of_formula f2 ^ ")"
  |Or (f1,f2) -> "(" ^ string_of_formula f1 ^ "OR" ^ string_of_formula f2 ^ ")";;

let rec list_of_props formule = 
    match formule with
    |Prop s -> [s]
    |Neg f -> list_of_props f
    |And(f1,f2) | Or(f1,f2) -> List.sort_uniq compare (list_of_props f1)@(list_of_props f2);;

let eval_formula formule interpretation =
  let rec aux formule interpretation = 
    match formule with
    |Prop s -> List.assoc s interpretation
    |Neg f -> not (aux f interpretation)
    |And(f1,f2) -> aux f1 interpretation && aux f2 interpretation
    |Or(f1,f2) -> aux f1 interpretation || aux f2 interpretation
  in aux formule interpretation;;

let add_to_all elt liste = 
  List.map(fun x -> elt::x) liste;;

let rec interpretations_props liste = 
  match liste with
  [] -> [[]]
  | a::reste -> let restant = interpretations_props reste in 
  add_to_all(a,true) restant @ add_to_all (a,false) restant;;

let interpretation formule = 
  interpretations_props (list_of_props formule);;

let satisfiable formule = List.exists (fun inter -> eval_formula formule inter) (interpretation formule);;

let tautology formule = List.for_all (fun inter -> eval_formula formule inter) (interpretation formule);;

let is_consequence formule1 formule2 = tautology (Or(Neg(formule1),formule2));;
let are_equivalent formule1 formule2 = is_consequence formule1 formule2 && is_consequence formule2 formule1;;
