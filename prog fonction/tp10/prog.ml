open Myset

let affiche elt set = 
  if element elt set then Printf.printf("oui\n") else Printf.printf("non\n");;

let () = 
  let len = Array.length Sys.argv in 
  let elem = int_of_string Sys.argv.(1) in 
  let tab =  ref empty in 
  for i = 2 to len-1 do 
    tab := add (int_of_string Sys.argv.(i)) !tab;
  done;
  affiche elem !tab;;
