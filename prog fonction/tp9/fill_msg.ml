let fill count msg file =
  let oc = open_out file in
  try
    for i = 1 to count do
      output_string oc msg;
      output_char oc '\n'
    done;
    close_out oc
  with e ->
    close_out oc;
    raise e


let () = 
  fill (int_of_string Sys.argv.(1)) Sys.argv.(2) Sys.argv.(3)