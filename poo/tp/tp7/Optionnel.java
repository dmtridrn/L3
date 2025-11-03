package tp7;

import java.util.NoSuchElementException;

public class Optionnel<T> {
    private T element;

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

    public static <T> Optionnel<T> vide(){
        return new Optionnel<>(null);
    }
    

}
