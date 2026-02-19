pub fn add(left: u64, right: u64) -> u64 {
    left + right
}

pub fn saluer(nom: &str){
    println!("Bonjour {} ! Comment tu vas bb", nom)
}

pub mod maths{
    pub fn add(left: u64, right: u64) -> u64 {
        left + right
    }
    pub fn sub(left: u64, right: u64) -> u64 {
        left - right
    }
}
