let r_decode = ref false
let r_key = ref '\x00'

let () =
  Arg.parse 
    [("-d", Arg.Set r_decode, "Decode") ;
     ("-e", Arg.Clear r_decode, "Encode")]
    (fun arg ->
       if String.length arg = 1 then
         r_key := arg.[0]
       else
         raise (Arg.Bad arg))
    "caesar [-d|-e] key"

let decode = !r_decode
let key = !r_key

let () =
  let buffer = Bytes.create 1024 in
  let eof = ref false in        
  while not !eof do
    let nread = In_channel.input stdin buffer 0 (Bytes.length buffer) in
    if nread <= 0 then
      eof := true
    else
      for i = 0 to nread - 1 do
        let curr = Bytes.get buffer i in
        let new_char = 
          if decode then Byte.sub curr key 
          else Byte.add curr key 
        in
        Bytes.set buffer i new_char
      done;
      (Out_channel.output stdout buffer 0 nread;
       Out_channel.flush stdout)
  done
