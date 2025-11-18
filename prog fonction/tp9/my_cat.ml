let print_file filename =
  try
    let ic = open_in filename in
    try
      while true do
        let line = input_line ic in
        print_endline line
      done
    with End_of_file ->
      close_in ic
  with Sys_error msg ->
    Printf.eprintf "Erreur: %s\n" msg

let () =
    let len = Array.length Sys.argv in 
    for i=1 to len -1 do 
      let filename = Sys.argv.(i) in 
      print_file filename
    done
