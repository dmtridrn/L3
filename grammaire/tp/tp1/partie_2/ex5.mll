{
  exception Eof
}

let chiffre = ['0'-'9']
let datevivant = chiffre+ '-' chiffre+
let datemort = chiffre+ '-'
let name = ['a'-'z''A'-'Z']+
let espacement=[' ''\t']+ 
let fullname = (name espacement*)+ 
let prof = '[' (espacement* name espacement*)+ ']'
let mort = fullname espacement* datemort espacement* prof?
let vivant = fullname espacement* datevivant espacement* prof?
let autre = 

rule lexeur = parse
    | mort as m {print_string (m ^ ": il est mort"); print_newline()}
    | vivant as v {print_string (mv^ ": il est vivant"); print_newline()}
    | _           { lexeur lexbuf }
    | eof		{ raise Eof }

{
  let ch = open_in (Sys.argv.(1)) in
  let lexbuf = Lexing.from_channel ch in
  try
    while true do
      lexeur lexbuf
    done
  with Eof -> (print_newline(); print_newline())
}
