package tp.tp7;

import java.util.List;
import java.util.NoSuchElementException;

public class Optionnel<T> {
    private T element;
    @SuppressWarnings("rawtypes")
    private static final Optionnel VIDE = new Optionnel<>(null);

    private Optionnel(T element){
        this.element = element;
    }

    public boolean estVide(){
        if(element == null){
            return true;
        }
        return false;
    }

    public T get(){
        if(!this.estVide()){
            return this.element;
        }
        throw new NoSuchElementException("ne contient pas d'élément");
    }

    public T ouSinon(T sinon){
        if(this.estVide()){
            return sinon;
        }
        return this.element;
    }

    public static <T> Optionnel<T> de(T elt){
        if(elt == null){
            throw new IllegalArgumentException();
        }
        return new Optionnel<>(elt);
    }

    @SuppressWarnings("unchecked")
    public static <T> Optionnel<T> vide(){
        return VIDE;
    }

    public static Optionnel<Integer> pairOuPas(List<Integer> liste){
        for(Integer e : liste){
            if(e%2 == 0){
                return de(e);
            }
        }
        return vide();
    }


}
