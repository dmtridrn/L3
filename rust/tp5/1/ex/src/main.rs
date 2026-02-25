#![allow(unused)]

fn swap<T>(a: &mut T, b: &mut T){
    std::mem::swap(a, b);
}

struct Box<T>{
    elt: T
}

impl<T> Box<T>{

    fn new(x: T) -> Self{
        Self { elt : x }
    }
    fn get(&self) -> &T {
        &self.elt
    }

}

enum Resultat<T> {
    Succes(T),
    Echec(String),
}


fn diviser(a: i32, b: i32) -> Resultat<i32> {
    if b != 0{
        return Resultat::Succes(a/b)
    }
    Resultat::Echec(String::from("division par 0"))
}

fn max<T: PartialOrd>(liste: &[T]) -> &T {
    let mut max = &liste[0];
    for i in liste{
        if i > max{
            max = i
        }
    }
    max
}

struct Paire<T, U> {
    premier: T,
    second: U,
}

impl<T, U> Paire<T, U> {
    fn afficher(&self)
    where
        T: std::fmt::Display,
        U: std::fmt::Display,
    {
        println!("Premier: {}, Second: {}", self.premier, self.second);
    }
}

trait Affichable{
    fn afficher(&self);
}

struct Livre{
    titre: String,
    auteur: String
}
struct Film{
    titre: String, 
    realisateur: String
}

impl Affichable for Livre{
    fn afficher(&self) {
        println!("Livre: {} par {}", self.titre, self.auteur);
    }
}

impl Affichable for Film{
    fn afficher(&self) {
        println!("Film: {} réalisé par {}", self.titre, self.realisateur);
    }
}

fn afficher_infos<T: Affichable>(elt: &T){
    elt.afficher();
}

trait Stockable<T>{
    fn quantite(&self) -> T;
    fn ajouter(&self);
    fn retirer(&self);
}

struct Produit{
    quatite: u32
}
struct Liquide{
    volume: f64
}




fn main() {
    let livre = Livre {
        titre: String::from("Le Petit Prince"),
        auteur: String::from("Antoine de Saint-Exupéry"),
    };
    let film: Film = Film {
        titre: String::from("Inception"),
        realisateur: String::from("Christopher Nolan"),
    };

    afficher_infos(&livre);
    afficher_infos(&film);
}   




