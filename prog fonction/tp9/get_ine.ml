let read_line count file=
  let ic = open_in file in 
  try 
    for i=1 to count-1 do
      let _ = input_line ic in ()
    done;

    let result = input_line ic in
    print_endline result;
    close_in ic
  with e ->
    close_in ic;
    raise e


let () = 
  read_line (int_of_string(Sys.argv.(1))) (Sys.argv.(2))