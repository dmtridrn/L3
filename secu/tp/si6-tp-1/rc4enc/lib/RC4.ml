type t = { state : Bytes.t ; mutable i : char ; mutable j : char }

let swap bytes i j =
  let x = Bytes.get bytes i in
  Bytes.set bytes i (Bytes.get bytes j);
  Bytes.set bytes j x
let get schedule x =
  Bytes.get schedule.state (Byte.to_int x)

let init key =
  let res = { state = Bytes.init 256 Byte.of_int;
              i = Byte.zero; j = Byte.zero } in
  let l = String.length key in
  let j = ref Byte.zero in
  for i = 0 to 255 do
    j := Byte.add (Byte.add (String.get key (i mod l)) (Bytes.get res.state i)) !j;
    swap res.state i (Byte.to_int !j)
  done;
  res

let next schedule =
  schedule.i <- Byte.addi schedule.i 1;
  schedule.j <- Byte.add (get schedule schedule.i) schedule.j;
  swap schedule.state (Byte.to_int schedule.i) (Byte.to_int schedule.j);
  get schedule (Byte.add (get schedule schedule.i) (get schedule schedule.j))

let nextn schedule n =
  let res = Bytes.create n in
  for k = 0 to n-1 do
    Bytes.set res k (next schedule)
  done;
  Bytes.unsafe_to_string res

(*
let () =
  assert
    (Bytes.to_string
       (nextn (init (Bytes.of_string "Key")) 10)
     = "\xEB\x9F\x77\x81\xB7\x34\xCA\x72\xA7\x19");
  
  assert
    (Bytes.to_string
       (nextn (init (Bytes.of_string "Secret")) 8)
     = "\x04\xD4\x6B\x05\x3C\xA8\x7B\x59")
*)
