use std::{collections::{HashMap, HashSet}};

fn pair_only(vect: Vec<i32>) -> Vec<i32>{
    let mut vec: Vec<i32> = Vec::new();
    for i in vect{
        if i%2 == 0 {
            vec.push(i);
        }
    }
    vec
}

fn fusion(vect1: Vec<i32>, vect2: Vec<i32>) -> Vec<i32>{
    let mut vec: Vec<i32> = Vec::new();
    vec.extend(vect1);
    vec.extend(vect2);
    vec.sort();
    vec
}

fn cpt_occ(str: String) -> HashMap<char, u32>{
    let mut res = HashMap::new();
    for i in str.chars(){
        *res.entry(i).or_insert(0) += 1;
    }
    res
}

fn no_doublons(vect: Vec<i32>) -> Vec<i32>{
    let mut res  = Vec::new();
    let mut temp = HashSet::new();
    for i in vect{
        temp.insert(i);
    }
    for i in temp{
        res.push(i);
    }
    res
}

fn inverse_hash(map: HashMap<String, Vec<String>>) -> HashMap<String, Vec<String>> {
    let mut res = HashMap::new();

    for (cle, val) in map {
        for i in val {
            res.entry(i).or_insert_with(Vec::new).push(cle.clone());
        }
    }
    res
}

fn hash_inter(h1: HashSet<i32>, h2: HashSet<i32>) -> HashSet<i32> {
    let mut res = HashSet::new();
    for i in h1.intersection(&h2){
        res.insert(*i);
    }
    res
}

fn somme_map(hm: HashMap<String, i32>) -> i32 {
    hm.values().sum()
}


enum MonErreur{
    DivisionParZero,
    NombreNegatif
}


fn division(a: f64, b: f64) -> Result<f64, MonErreur> {
    if b == 0.0 {
        return Err(MonErreur::DivisionParZero);
    }
    Ok(a/b)
}

fn racine_carre(ent: f64) -> Result<f64, MonErreur> {
    if ent < 0.0 {
        return Err(MonErreur::NombreNegatif);
    }
    Ok(f64::sqrt(ent))
}

fn mon_calcul(a: f64, b: f64) -> Result<f64, MonErreur> {
    let temp = division(a, b)?;
    let res = racine_carre(temp)?;
    Ok(res)
}


fn main(){

    match mon_calcul(16.0, 4.0) {
        Ok(res) => println!("√(16/4) = {}", res),
        Err(MonErreur::DivisionParZero) => println!("Erreur : division par zéro !"),
        Err(MonErreur::NombreNegatif) => println!("Erreur : nombre négatif !"),
    }

    match mon_calcul(5.0, 0.0) {
        Ok(res) => println!("√(5/0) = {}", res),
        Err(MonErreur::DivisionParZero) => println!("Erreur : division par zéro !"),
        Err(MonErreur::NombreNegatif) => println!("Erreur : nombre négatif !"),
    }

    match mon_calcul(-4.0, 2.0) {
        Ok(res) => println!("√(-4/2) = {}", res),
        Err(MonErreur::DivisionParZero) => println!("Erreur : division par zéro !"),
        Err(MonErreur::NombreNegatif) => println!("Erreur : nombre négatif !"),
    }
}
