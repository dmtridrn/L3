fn convert(temp: f64) -> Result<f64, &'static str>{
    if temp < -273.15 {
        return Err("sous zero abs");
    }
    let res = temp*1.8 + 32.0;
    Ok(res)
}

fn main() {
    // Ton code d'ex1 ici
}
