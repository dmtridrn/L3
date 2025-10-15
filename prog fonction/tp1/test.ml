let rec imprimer_liste l = match l with
| [] -> print_newline()
| e::[] -> print_int e
| e::r -> print_int e;
print_string ";";
imprimer_liste (r);;

let l = [2;3;4;3];;

imprimer_liste l;;