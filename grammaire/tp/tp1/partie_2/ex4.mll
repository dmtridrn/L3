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
let mort = fullname espacement* datemort espacement* prof

rule lexeur = parse
    | mort as m {print_string m; print_newline()}
    | _           { lexeur lexbuf }
    | eof		{ raise Eof }

{
  let ch = open_in (Sys.argv.(1)) in
  let lexbuf = Lexing.from_channel ch in
  try
    while true do
      lexeur lexbuf
    done
  with Eof -> ()
}
