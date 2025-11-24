let number = ref 0
let message = ref ""
let output = ref ""

let speclist = [
  ("-n", Arg.Int (fun x -> number := x), "Number of lines");
  ("-m", Arg.String (fun s -> message := s), "Message to repeat");
  ("-o", Arg.String (fun s -> output := s), "Output file");
]

let usage_msg = "Usage: fill_msg -n <number> -m <message> -o <output>"
let anon_fun arg = 
  raise (Arg.Bad ("Unexpected argument: " ^ arg))

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
  Arg.parse speclist anon_fun usage_msg;
  
  if !number < 0 then begin
    Printf.eprintf "Error: number must be positive\n";
    Arg.usage speclist usage_msg; 
    exit 1
  end;
  
  fill !number !message !output