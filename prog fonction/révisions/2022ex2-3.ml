let rec pesee_max liste = 
    match liste with 
    [] -> 0
    | [a] -> a
    | a::reste -> a + pesee_max reste;;

let fusion liste1 liste2 = 
    List.sort_uniq compare (liste1@liste2);;

let pesees_simple liste = 
    List.fold_left (fun acc x -> 
        let somme = List.map (fun y -> x+y) acc in 
        fusion acc somme) [0] liste;;
let pesees_complexes liste = 
    List.fold_left (fun acc x -> 
        let somme = List.map (fun y -> x+y) acc in 
        let sous = fusion somme (List.map (fun z -> abs(x-z)) acc) in 
        fusion acc sous) [0] liste;;



