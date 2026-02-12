{
open Token
}

let digit=['0'-'9']+
let other=[^'0'-'9']

rule lexeur = parse
        | digit as s {DIGIT(int_of_string s)}
        | other {OTHER}
        | eof {EOF}
        | _  {exit 0}

            
