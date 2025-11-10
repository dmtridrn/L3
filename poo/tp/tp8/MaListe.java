package tp.tp8;

import java.util.LinkedList;
import java.util.function.Consumer;

class MaListe<E> extends LinkedList<E>{

    void pourChacun(Consumer<E> action){
        for(E elt : this){
            action.accept(elt);
        }
    }
}