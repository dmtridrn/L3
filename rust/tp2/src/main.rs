fn _premier_mot(s: &str) -> &str{
    let bytes = s.as_bytes();
    for (i, &val) in bytes.iter().enumerate(){
        if val == b' '{
            return &s[0..i];
        }
    }
        return &s;
}

fn verifier_partition(tableau: &[i32], pivot: usize) -> bool{
    let mut rencontre = false;
    for (i,&val)  in tableau.iter().enumerate(){
        if i == pivot {
            rencontre = true;
        }
        if !rencontre {
            if val >= tableau[pivot] {
                return false;
            }
        }
        else {
            if val < tableau[pivot] {
                return false;
            }
        }
    }
    true
}

fn partition(tableau: &mut [i32], pivot: &mut usize){
    let dernier_indice = tableau.len()-1;
    tableau.swap(*pivot, dernier_indice);
    let valeur_pivot: i32 = tableau[dernier_indice];
    let mut i: usize = 0;

    for j in 0..dernier_indice{
        if tableau[j] < valeur_pivot{
            tableau.swap(j, i);
            i+=1;
        }
    }

    tableau.swap(dernier_indice, i);
    *pivot = i;
    debug_assert!(verifier_partition(tableau, *pivot))
}

fn verifier_tri(tableau: &[i32]) -> bool{
    if tableau.len() <= 1 {
        return true;
    }
    for i in 0..tableau.len()-1{
        if tableau[i] > tableau[i+1]{
            return false;
        }
    }
    true
}

fn quicksort(tableau: &mut [i32]){
    if tableau.len() < 2{
        return
    }
    let mut pivot: usize = tableau.len()/2;
    partition(tableau, &mut pivot);
    let (gauche, droite) = tableau.split_at_mut(pivot);
    quicksort(gauche);
    quicksort(&mut droite[1..]);

}

fn main() {
    // --- Test 1 : Un tableau normal en désordre ---
    let mut t1 = [3, 1, 4, 1, 5, 9, 2, 6];
    println!("Avant : {:?}", t1);
    quicksort(&mut t1);
    println!("Après : {:?}", t1);
    // Le assert! fera planter le programme si verifier_tri renvoie false
    assert!(verifier_tri(&t1)); 
    println!("Test 1 OK !");

    // --- Test 2 : Déjà trié (Le pire cas pour certains pivots !) ---
    let mut t2 = [1, 2, 3, 4, 5];
    quicksort(&mut t2);
    assert!(verifier_tri(&t2));
    println!("Test 2 OK !");

    // --- Test 3 : Trié à l'envers ---
    let mut t3 = [5, 4, 3, 2, 1];
    quicksort(&mut t3);
    assert!(verifier_tri(&t3));
    println!("Test 3 OK !");

    // --- Test 4 : Avec des doublons ---
    let mut t4 = [2, 1, 2, 1, 2];
    quicksort(&mut t4);
    assert!(verifier_tri(&t4)); // Doit donner [1, 1, 2, 2, 2]
    println!("Test 4 OK !");
    
    // --- Test 5 : Tableau vide (Ne doit pas planter) ---
    let mut t5: [i32; 0] = [];
    quicksort(&mut t5);
    assert!(verifier_tri(&t5));
    println!("Test 5 OK !");
}
