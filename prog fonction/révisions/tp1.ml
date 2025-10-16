let square x = x*x;;

let perimeter rayon = let pi = 3.1415927 in 2.*.pi*.rayon;;

let div n m = let (n1,m1) = (float_of_int n, float_of_int m) in n1/.m1;;
let bis str = str^str;;

let times8 str = bis(bis(bis(str)));;

let is_zero elt = elt = 0;;

let my_max a b = if a > b then a else b;;

let max_triple a b c = max (max a b) c;;

let max_quadruple a b c d = max (max_triple a b c) d;;

let rec somme a = if a = 0 then 0 else a + somme(a-1);;

let rec fibo1 n = 
  match n with
  0 -> 0
  |1 -> 1
  |_ -> fibo1(n-1) + fibo1(n-2);;


