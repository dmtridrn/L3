let () =
  let buffer = Bytes.create 1024 in
  let eof = ref false in
  while not !eof do
    let nread = In_channel.input stdin buffer 0 (Bytes.length buffer) in
    if nread <= 0 then
      eof := true
    else
      (Out_channel.output stdout buffer 0 nread;
       Out_channel.flush stdout)
  done        
