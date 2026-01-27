let contenu = In_channel.with_open_bin "badauth.bin" In_channel.input_all in 

let buffer1 = Bytes.of_string contenu in

let message = "Veuillez virer la somme de 100 dollars a Sir Austin Danger Powers" in 

let buffer2 = Bytes.of_string message in

let masque = Bytes.create (String.length message) in 

  for i = 0 to (String.length message)-1 do 
    Bytes.set masque i (Byte.xor (Bytes.get buffer1 (i+8)) (Bytes.get buffer2 i))
  done;

let nvmsg = "Veuillez virer la somme de 1.000.000 dollars a Dr Evil" in 
let buffer3 = Bytes.of_string nvmsg in
let nvrc = Bytes.create (8+String.length nvmsg) in 
for i = 0 to 7 do 
  Bytes.set nvrc i (Bytes.get buffer1 i)
done; 
for i = 0 to (String.length nvmsg)-1 do 
  Bytes.set nvrc (i+8) (Byte.xor (Bytes.get masque i) (Bytes.get buffer3 i))
done;

let oc = open_out_bin "badauth.evil.bin" in 
output_bytes oc nvrc;
close_out oc;