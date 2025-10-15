let square x = x*x;;
let perimeter cercle =
    let pi = 3.1415927 
    in 2.*.pi*.cercle;;  

let div n m = 
    let r = float_of_int(n) and t = float_of_int(m) 
    in r/.t;;

let bis text = text ^ text;;

let times8 str = 
  let str2 = str^str in
  let str3 = str2^str2 in 
  str3^str3;;

let times8bis str = bis(bis(bis str));;

let is_zero x = x = 0;;
let msg_zero x = 
  if x = 0 then "zero" else "not zero";;

let my_max a b =
  if a > b then a else b;; 

let max_triple a b c = 
  let temp = max a b in max temp c;;

let max_quad a b c d = 
  let temp = max_triple a b c in max temp d;;

let rec somme n =
  if n = 0 then 0 else
    n+somme(n-1);; 

let rec fibo n = 
  if n = 0 then 0 else
    if n = 1 then 1 else
      fibo(n-1) + fibo(n-2);;

let rec sommecarre f n = 
  if n = 0 then 0 else
    f n + sommecarre f (n-1);;

let rec binome p n = 
  if p = 0 || p = n then 1 else
   if p > n then 0 else
     binome (p-1) (n-1) + binome p (n-1);;

