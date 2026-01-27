let key =
  if Array.length Sys.argv == 2
  && String.length Sys.argv.(1) > 0
  && String.length Sys.argv.(1) <= 256 then
    Sys.argv.(1)
  else
    (Printf.fprintf stderr "Usage: rc4enc key\n";
     exit 2)

let () =
  let buffer = Bytes.create 1024 in
  let eof = ref false in
  let flot = RC4.init key in 
  while not !eof do
    let nread = In_channel.input stdin buffer 0 (Bytes.length buffer) in
    if nread <= 0 then
      eof := true
    else
      for i = 0 to nread - 1 do
        let curr = Bytes.get buffer i in
        let new_char = 
          Byte.xor (RC4.next flot) curr 
        in
        Bytes.set buffer i new_char
      done;
      (Out_channel.output stdout buffer 0 nread;
       Out_channel.flush stdout)
  done
