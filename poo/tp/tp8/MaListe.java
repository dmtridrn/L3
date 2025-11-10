package tp.tp8;

import java.util.LinkedList;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;

class MaListe<E> extends LinkedList<E>{

    void pourChacun(Consumer<E> action){
        for(E elt : this){
            action.accept(elt);
        }
    }

    List<E> filter(Predicate<E> pred){
        List<E> liste = new MaListe<>();
        for(E elt : this){
            if(pred.test(elt)){
                liste.add(elt);
            }
        }
        return liste;
    }

    <U> List<U> map(Function<E,U> f){
        List<U> liste = new MaListe<>();
        for(E elt : this){
            liste.add(f.apply(elt));
        }
        return liste;
    }

    <U> U fold(U z, BiFunction<U, E, U> f){
        for(E elt : this){
            z = f.apply(z, elt);
        }
        return z;
    }
}