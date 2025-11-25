  type 'a set = 'a list         
  let empty = []
  let add x set = if List.mem x set then set else x::set
  let element x set = List.mem x set
  let debug s = s