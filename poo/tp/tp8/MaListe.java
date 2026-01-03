package tp.tp8;

import java.util.LinkedList;
import java.util.List;
import java.util.function.BiFunction;
import java.util.function.Consumer;
import java.util.function.Function;
import java.util.function.Predicate;

public class MaListe<E> extends LinkedList<E>{
    
    void pourChacun(Consumer<E> action){
        for(E elt : this){
            action.accept(elt);
        }
    }

    List<E> filter(Predicate<E> pred){
        MaListe<E> nv = new MaListe<>();
        for(E elt : this){
            if(pred.test(elt)){
                nv.add(elt);
            }
        }
        return nv;
    }

    <U> List<U> map(Function<E,U> f){
        MaListe<U> nv = new MaListe<>();
        for(E elt : this){
            nv.add(f.apply(elt));
        }
        return nv;
    }

    <U> U fold(U z, BiFunction<U, E, U> f){
        U a = z;
        for(E elt : this){
            a = f.apply(a, elt);
        }
        return a;
    }
}
