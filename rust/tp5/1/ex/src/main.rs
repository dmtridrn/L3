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
    fn ajouter(&mut self, montant: T);
    fn retirer(&mut self, montant: T) -> Result<T, String>;
}

struct Produit{
    quantite: u32
}
struct Liquide{
    volume: f64
}

impl Stockable<u32> for Produit{
    fn quantite(&self) -> u32 {
        self.quantite
    }

    fn ajouter(&mut self, montant: u32) {
        self.quantite += montant;
    }

    fn retirer(&mut self, montant: u32) -> Result<u32, String> {
        if montant < self.quantite{
            self.quantite -= montant;
            return Result::Ok((montant));
        }
        Result::Err(String::from("nn"))
    }
}

impl Stockable<f64> for Liquide{
    fn quantite(&self) -> f64 {
        self.volume
    }

    fn ajouter(&mut self, montant: f64) {
        self.volume += montant;
    }

    fn retirer(&mut self, montant: f64) -> Result<f64, String> {
        if montant < self.volume{
            self.volume -= montant;
            return Result::Ok((montant));
        }
        Result::Err(String::from("nn"))
    }
}

fn afficher_stock <S, T>(elt: &S)
    where 
        S: Stockable<T>,
        T: std::fmt::Display
    {
        println!("Stock: {}", elt.quantite());
}

fn first_in_dictionary<'a>(x: &'a str, y: &'a str) -> &'a str {
    if x < y {
        x
    } else {
        y
    }
}


struct Book {
    title: String,
}

struct BookReview<'a>{
    title_ref: &'a str
}

impl<'a> BookReview<'a>{
    fn get_title(&self) -> &str{
        self.title_ref
    }
}

fn get_title<'a>(rev: &'a BookReview) -> &'a str{
    rev.title_ref
}

trait Summary {
    fn summarize(&self) -> &str;
}

struct Article {
    headline: String,
    content: String,
}

impl Summary for Article {
    fn summarize(&self) -> &str {
        &self.headline
    }
}


fn main() {
    let my_book = Book {
        title: String::from("Le Rust pour les nuls"),
    };
    let review = BookReview {
        title_ref: &my_book.title
    };

    println!("{}", review.get_title());
    println!("{}", get_title(&review));
}






