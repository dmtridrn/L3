type 'a vector = {
  mutable contents : 'a array;
  default : 'a;
  mutable size : int;
}

let create n a = {
  contents = Array.make n a;
  size = 0;
  default = a;
}

