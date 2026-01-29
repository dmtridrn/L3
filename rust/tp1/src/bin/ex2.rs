use std::io;

fn classer_note(note: f32) -> char {
    if note < 0.0 || note > 20.0 {
        println!("hhaha");
        return '?';
    }
    if note >= 18.0 {
        'A'
    }
    else if note >= 16.0{
        'B'
    }
    else if note >= 14.0{
        'C'
    }
    else if note >= 12.0{
        'D'
    }
    else {
        'F'
    }
}

fn moyenne(notes: &[f32]) -> Option<f32> {
    if notes.is_empty() {
        return None;
    }
    let mut somme = 0.0;
    let mut cpt = 0.0;
    for n in notes {
        somme += n;
        cpt += 1.0;
    };
    Some(somme/cpt)
}

fn note_max(notes: &[f32]) -> Option<f32> {
    if notes.is_empty() {
        return None;
    }
    let mut maxi = notes[0];
    for n in notes {
        if *n > maxi {
            maxi = *n
        }
    };
    return Some(maxi);
}

fn filtrer_notes(notes: &[f32]) -> Vec<f32> {
    let mut vec: Vec<f32> = Vec::new();
    for n in notes {
        if *n<=20.0 && *n>=0.0 {
            vec.push(*n);
        }
    };
    return vec;
}



fn main() {
    let note: f32 = loop{
        let mut saisie = String::new();
        io::stdin().read_line(&mut saisie).expect("Erreur de lecture");
        let n: f32 = saisie.trim().parse().expect("pas un nombre");
        if n <= 20.0 && n >= 0.0 {
            println!("haha");
            break n
        }
        else{
            println!("recomence");
        }
    };
    println!("vous avez eu {note}");
}
