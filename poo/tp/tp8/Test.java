package tp.tp8;

import java.util.function.Consumer;

public class Test {
    
    public static void main(String[] args){
        MaListe<Integer> nombres = new MaListe<>();
        nombres.add(2);
        nombres.add(5);
        nombres.add(3);

        // Produit
        int produit = nombres.fold(1, (a, x) -> a * x);
        System.out.println("Produit : " + produit); // Produit : 30

        // Maximum
        int max = nombres.fold(Integer.MIN_VALUE, (a, x) -> Math.max(a, x));
        System.out.println("Maximum : " + max); // Maximum : 5
    }
}

