Random.self_init ()

let fill number sup output = 
  let oc = open_out output in 
  try
    for i=1 to number do 
      let num = Random.int sup in 
      Printf.fprintf oc "%d " num
    done;
    close_out oc
  with e -> 
    close_out oc;
    raise e

let () =
  fill (int_of_string Sys.argv.(1)) (int_of_string Sys.argv.(2)) Sys.argv.(3)