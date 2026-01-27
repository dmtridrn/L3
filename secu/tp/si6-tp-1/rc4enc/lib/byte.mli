val add : char -> char -> char
val sub : char -> char -> char
val mul : char -> char -> char

val neg : char -> char
val xor : char -> char -> char
val not : char -> char
val andb : char -> char -> char
val borb : char -> char -> char

val addc : char -> char -> bool -> char * bool
val subc : char -> char -> bool -> char * bool
val mulc : char -> char -> char * char

val addi : char -> int -> char
val subi : char -> int -> char

val of_int : int -> char
val to_int : char -> int

val zero : char
val one : char
  
