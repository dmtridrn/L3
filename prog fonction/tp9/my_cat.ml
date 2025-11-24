let print_file filename flag =
  try
    let ic = open_in filename in
    let numero = ref 1 in
    try
      while true do
        let line = input_line ic in
        if flag then
          Printf.printf "%d: %s\n" !numero line
        else
          print_endline line;
        numero := !numero+1
      done
    with End_of_file ->
      close_in ic
  with Sys_error msg ->
    Printf.eprintf "Erreur: %s\n" msg

let () =
    let len = Array.length Sys.argv in 
    if Sys.argv.(1) = "-n" then 
      for i=2 to len -1 do 
      let filename = Sys.argv.(i) in 
      print_file filename true
    done
  else 
    for i=1 to len -1 do 
      let filename = Sys.argv.(i) in 
      print_file filename false
    done
