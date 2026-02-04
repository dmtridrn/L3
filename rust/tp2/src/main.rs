fn premier_mot(s: &str) -> &str{
    let bytes = s.as_bytes();
    for (i, &val) in bytes.iter().enumerate(){
        if val == b' '{
            return &s[0..i];
        }
    }
        return &s;
}



fn main() {
    
}
