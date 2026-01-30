use std::io;

fn affiche_grille(grille: &[[char; 15]; 15]){
    for l in grille.iter() {
        for c in l.iter() {
            print!(" {c}");
        }
        println!(""); 
    }
}

fn placer_pion(grille: &mut[[char; 15]; 15], joueur: bool, x: usize, y: usize) -> bool{
    let pion: char = if joueur { 'X' } else { 'O' };

    if x < 15 && y < 15  && grille[x][y] == '.'{
        grille[x][y] = pion;
        return true
    }
    false
}

fn check_etat(grille: &[[char; 15]; 15]) -> bool {
    for y in 0..15 {
        for x in 0..15 {
            let pion = grille[x][y];
            if pion == '.' {continue;}
            
            if x + 4 < 15 &&
               grille[y][x+1] == pion &&
               grille[y][x+2] == pion &&
               grille[y][x+3] == pion &&
               grille[y][x+4] == pion {
                   return true;
            }

            if y + 4 < 15 &&
               grille[y+1][x] == pion &&
               grille[y+2][x] == pion &&
               grille[y+3][x] == pion &&
               grille[y+4][x] == pion {
                   return true;
            }

            if x + 4 < 15 && y + 4 < 15 &&
               grille[y+1][x+1] == pion &&
               grille[y+2][x+2] == pion &&
               grille[y+3][x+3] == pion &&
               grille[y+4][x+4] == pion {
                   return true;
            }

            if x >= 4 && y + 4 < 15 &&
               grille[y+1][x-1] == pion &&
               grille[y+2][x-2] == pion &&
               grille[y+3][x-3] == pion &&
               grille[y+4][x-4] == pion {
                   return true;
            }
        }
    }
    false
}

fn jouer_tour(joueur: bool, grille: &mut[[char; 15]; 15]){

    loop{
        println!("Entrez les coordonnées du pion que vous voulez placer. (X -> entrée -> Y)");
        let mut saisie = String::new();
        io::stdin().read_line(&mut saisie).expect("lecture foirée");
        let x: usize = saisie.trim().parse().expect("entrez un entier");

        let mut saisie = String::new();
        io::stdin().read_line(&mut saisie).expect("lecture foirée");
        let y: usize = saisie.trim().parse().expect("entrez un entier");
        
        if placer_pion(grille, joueur, x, y){
            break;
        }
        println!("placez votre pion dans la grille sur une case innocupée");
    }

}


fn main() {

    let mut grille: [[char; 15]; 15] = [['.'; 15]; 15];

    let mut joueur = true;
    
    for i in 0..225 {
        affiche_grille(&grille);
        println!("TOUR JOUEUR {}: ", (i%2)+1);
        jouer_tour(joueur, &mut grille);
        if check_etat(&grille) {
            println!("Partie terminée. Grille finale: ");
            affiche_grille(&grille);
            break
        }
        joueur = !joueur;
    }

}
