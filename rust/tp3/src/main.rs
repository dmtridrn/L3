// exo 2.2

enum Forme{
    Cercle(f64),
    Rectangle(f64, f64),
    Carre(f64)
}

fn aire(forme: Forme) -> f64{
    match forme {
        Forme::Cercle(n) => (std::f64::consts::PI)*n*n,
        Forme::Rectangle(n, m) => n*m,
        Forme::Carre(n) => n*n
    }
}

fn diviser(a: f64, b: f64) -> Result<f64, String>{
    if b == 0.0 {
        Err(String::from("Division par 0"))
    }
    else{
        Ok(a/b)
    }
}

fn affiche_resultat(res: Result<f64, String>){
    match res {
        Result::Ok(n) => println!("{}", n),
        Result::Err(s) => println!("{}", s)
    }
}

enum Chifoumi{
    Pierre,
    Feuille,
    Ciseaux
}

impl Chifoumi {
    fn est_ciseaux(&self) -> bool{
        match self{
            Chifoumi::Pierre => false,
            Chifoumi::Feuille => false,
            Chifoumi::Ciseaux => true
        }
    }
}


enum Tree {
    Leaf(i32),
    Node(Box<List>)
}

enum List{
    Nil,
    Cons(Tree, Box<List>)
}

impl Tree{
    fn display(&self) {
        match self {
            Tree::Leaf(n) => print!("{}", n),
            Tree::Node(liste) => liste.display(),
        }
    }

    fn reverse(&mut self){
        match self{
            Tree::Leaf(n) => {},
            Tree::Node(liste) => liste.reverse()
        }
    }
}

impl List{
    fn push(&mut self, x: Tree){
        let ancienne = std::mem::replace(self, List::Nil);
        *self = List::Cons(x, Box::new(ancienne))
    }

    fn display(&self){
        print!("[ ");
        let mut current = self;
        while let List::Cons(tree, next) = current {
            tree.display();
            print!(" ");
            current = next;
        }
        print!("]")
    }

    fn reverse(&mut self){
        let mut current = std::mem::replace(self, List::Nil);
        let mut reversed  = List::Nil;
        while let List::Cons(mut tree, next) = current{
            tree.reverse();
            reversed.push(tree);
            current = *next;
        }
        *self = reversed;
    }
}


fn main() {
    // 1. Création de la liste imbriquée [ 32 -2 0 53 ]
    let mut liste_interne = List::Nil;
    liste_interne.push(Tree::Leaf(53));
    liste_interne.push(Tree::Leaf(0));
    liste_interne.push(Tree::Leaf(-2));
    liste_interne.push(Tree::Leaf(32));

    // 2. Création de la liste principale
    let mut liste_principale = List::Nil;

    // On ajoute un nœud vide [ ] à la fin
    liste_principale.push(Tree::Node(Box::new(List::Nil)));

    // On ajoute la feuille 12
    liste_principale.push(Tree::Leaf(12));

    // On ajoute la liste interne comme un Nœud [ 32 -2 0 53 ]
    liste_principale.push(Tree::Node(Box::new(liste_interne)));

    // On ajoute la feuille 17 au début
    liste_principale.push(Tree::Leaf(17));

    // 3. Affichage final
    println!("Résultat attendu : [ 17 [ 32 -2 0 53 ] 12 [ ] ]");
    print!("Résultat obtenu  : ");
    liste_principale.display();
    println!(); 
    print!("Renverséé: "); 
    liste_principale.reverse();
    liste_principale.display();
}


