let somme input = 
  let ic = Scanf.Scanning.open_in input in 
  let sum = ref 0 in
  try
    while true do 
      let nombre = Scanf.bscanf ic "%d " (fun x -> x) in
      Printf.printf "%d " nombre;
      sum := !sum + nombre
    done
  with End_of_file ->
      Scanf.Scanning.close_in ic;
      Printf.printf "Somme: %d\n" !sum

let () = 
    somme Sys.argv.(1)