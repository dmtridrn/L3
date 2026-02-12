{
  exception Eof
  let somme = ref 0
}

let digit = ['0'-'9']+
  
rule lexeur = parse
  | digit as c	{ print_string c; somme := !somme + (int_of_string c)}
  | _           { lexeur lexbuf }
  | eof		{ raise Eof }

{
  let ch = open_in (Sys.argv.(1)) in
  let lexbuf = Lexing.from_channel ch in
  try
    while true do
      lexeur lexbuf
    done
  with Eof -> (print_newline(); print_int !somme; print_newline())
}
