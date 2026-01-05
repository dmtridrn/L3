package annale2018;
import java.util.Map;

import java.util.HashMap;

final class Piece {

    private final Valeur val;
    private final Couleur col;
    private static final Map<Couleur, Map<Valeur, Piece>> cache = new HashMap<>();


    private Piece(Valeur val, Couleur col){
        this.val = val;
        this.col = col;
    }
    static{
        for(Couleur cou : Couleur.values()){
            Map<Valeur, Piece> sousliste = new HashMap<>();
            for(Valeur val : Valeur.values()){
                Piece p = new Piece(val, cou);
                sousliste.put(val, p);
            }
            cache.put(cou, sousliste);
        }
    }

    public Piece of(Couleur c, Valeur v){
        return cache.get(c).get(v);
    }

}