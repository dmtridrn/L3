let rec expo n f = fun x ->
  if n = 1 then x
    else f (expo (n-1) f x) (expo(n-1) f x);;

print_int(expo 5 (+) 2);;