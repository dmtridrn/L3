package tp.tp12;

import java.util.*;

public class Appartement {
    public int nbPieces;
    public int prix;
    public String lieu;

    public Appartement(int nbPieces, int prix, String lieu) {
        this.nbPieces = nbPieces;
        this.prix = prix;
        this.lieu = lieu;
    }

    public String toString() {
        return "(" + nbPieces + ", " + prix + ", " + lieu + ")";
    }

    public static void main(String[] args) {
        List<Appartement> appartements = new ArrayList<>();
        appartements.add(new Appartement(5, 5_000_000, "Paris"));
        appartements.add(new Appartement(1, 200_000, "Paris"));
        appartements.add(new Appartement(5, 1_000_000, "Nancy"));
        appartements.add(new Appartement(4, 200_000, "Limoges"));
        appartements.add(new Appartement(1, 80_000, "Lille"));
        appartements.add(new Appartement(2, 200_000, "Brest"));
        appartements.add(new Appartement(1, 180_000, "Paris"));
        appartements.add(new Appartement(2, 500_000, "Paris"));
    }

}
