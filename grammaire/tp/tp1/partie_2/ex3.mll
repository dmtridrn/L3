{
  exception Eof
}

let chiffre = ['0'-'9']
let datevivant = chiffre+ '-' chiffre+
let datemort = chiffre+ '-'

rule lexeur = parse
    | datevivant as d {print_string (d^": encore vivant"); print_newline()}
    | datemort as d2 {print_string d2; print_newline()}
    | _           {}
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
