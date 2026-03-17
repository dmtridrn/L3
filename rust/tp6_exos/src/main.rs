
fn _moyenne_positif(nombres: &[i32]) -> f64{
    let iter: (i32, i32) = nombres.iter()
    .filter(|&&x| x>0)
    .fold((0,0), |(somme,compte), &val| (somme+val, compte+1));

    iter.0 as f64 / iter.1 as f64
}

fn _est_palindrome(s: &str) -> bool {
    s.chars().eq(s.chars().rev())
}

fn _mots_palindromes<'a>(mots: &[&'a str]) -> Vec<&'a str> {
    mots.iter()
    .filter(|&&val| _est_palindrome(val))
    .copied()
    .collect()
}

fn celsius_vers_farenheit(c:f64) -> f64{
    (c * 9.0/5.0) + 32.0
}

fn filtre_temp(celsius: &[f64]) -> Vec<f64>{
    celsius.iter().map(|&c| celsius_vers_farenheit(c)).filter(|&x| x >= 50.0).collect()
}



fn main() {
    let temperatures = vec![10.0, 20.0, 30.0, 0.0, 15.0];
    let filtrees = filtre_temp(&temperatures);
    println!("Températures > 50°F : {:?}", filtrees);
    // Affiche : Températures > 50°F : [50.0, 68.0, 86.0]
}



