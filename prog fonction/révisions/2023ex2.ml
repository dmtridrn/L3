let comp_gauche liste = 
  match liste with
  [] -> []
  |[a] -> [a]
  |a::b::reste -> (a+b)::reste;; 

let comps_gauche liste = 
  let rec aux liste acc =
  match liste with
  [] -> List.rev acc
  | [a] -> List.rev ([a]::acc)
  | a::b::reste -> aux (comp_gauche liste) (liste::acc)
  in aux liste [];;



type parenthese = PO | PF (* Parenth`ese Ouvrante, Parenth`ese Fermante *)
type mot = parenthese list

let test_mbp_opt mot = 
  let rec aux mot acc = 
    match mot with 
    [] -> acc = 0
    | a::reste -> if acc < 0 then false else if a = PO then aux reste (acc+1) else aux reste (acc-1)
  in aux mot 0;;

let exemple1 = [PO;PO;PF;PF;PO;PF];;
let exemple2 = [PO;PF;PF;PO;PF;PO];;


type mbp =
| Vide
| Paren of mbp
| Concat of mbp * mbp

let ecrire_mbp mbp = 
  let rec aux mbp acc = 
    match mbp with
    Vide -> acc
    | Paren(m) -> [PO]@(aux m acc)@[PF]
    | Concat(a,b) -> (aux a acc)@(aux b acc)
  in aux mbp [];;

let lire_mbp mot=

  let rec regrouper = function
      | [] -> Vide
      | [x] -> x
      | h :: t -> Concat (h, regrouper t)
  in

  let rec aux reste_mot pile =
    match reste_mot, pile with
    (* Cas A : Fin du mot *)
    | [], [niveau_base] -> regrouper (List.rev niveau_base)
    | [], _ -> failwith "Erreur : PO non fermée"

    | PO :: suite, p -> aux suite ([] :: p)

    | PF :: suite, courant :: parent :: reste_pile ->
        let bloc = Paren (regrouper (List.rev courant)) in
        aux suite ((bloc :: parent) :: reste_pile)

    | PF :: _, [_] -> failwith "Erreur : PF en trop"
    | _ -> failwith "Erreur syntaxe"
  in
  aux mot [[]]
let exemple1_mbp = Concat (Paren (Paren Vide), Paren Vide);;

ecrire_mbp exemple1_mbp;;