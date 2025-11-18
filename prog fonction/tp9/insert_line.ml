let print_file number line input output =
  try
    let ic = open_in input in
    let oc = open_out output in
    let i = ref 1 in
    try
      while true do
        if !i = number then begin
          output_string oc line;
          output_char oc '\n';
        end;
        let text = input_line ic in
        output_string oc text;
          output_char oc '\n';
        i := !i+1;
      done
    with End_of_file ->
      close_out oc;
      close_in ic;
  with Sys_error msg ->
    Printf.eprintf "Erreur: %s\n" msg

let () =
  print_file (int_of_string Sys.argv.(1)) Sys.argv.(2) Sys.argv.(3) Sys.argv.(4)