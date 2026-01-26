let add x y = Char.chr (Int.logand (Char.code x + Char.code y) 255)
let sub x y = Char.chr (Int.logand (Char.code x - Char.code y) 255)
let mul x y = Char.chr (Int.logand (Char.code x * Char.code y) 255)
let neg x = Char.chr (Int.logand (- Char.code x) 255)

let xor x y = Char.chr (Int.logxor (Char.code x) (Char.code y))
let not x = Char.chr (Int.logand (Int.lognot (Char.code x)) 255)
let andb x y = Char.chr (Int.logand (Char.code x) (Char.code y))
let borb x y = Char.chr (Int.logor (Char.code x) (Char.code y))

let addc x y c =
  let r = Char.code x + Char.code y + if c then 1 else 0 in
  (Char.chr (Int.logand r 255), r > 255)
let subc x y c =
  let r = Char.code x - Char.code y - if c then 1 else 0 in
  (Char.chr (Int.logand r 255), r < 0)
let mulc x y =
  let r = Char.code x * Char.code y in
  (Char.chr (Int.logand r 255), Char.chr (Int.shift_right r 8))

let addi x i = Char.chr (Int.logand (Char.code x + i) 255)
let subi x i = Char.chr (Int.logand (Char.code x - i) 255)

let of_int i = Char.chr (Int.logand i 255)
let to_int x = Char.code x

let zero = Char.chr 0
let one = Char.chr 1
    
