package tp10;

import java.util.ArrayList;
import java.util.List;
import java.util.ListIterator;

public final class Fusion {
    private Fusion() {}

    static <E extends Comparable<? super E>> List<E> fusion(List<E> l1, List<E> l2) {
        // ArrayList plutôt que LinkedList (pour get en temps constant)
        List<E> l3 = new ArrayList<>(l1.size() + l2.size());
        ListIterator<E> it1 = l1.listIterator(), it2 = l2.listIterator();
        System.out.println("Fusion dans thread " 
            + Thread.currentThread().getName() + " Listes de taille "
            + l1.size() + " et " + l2.size());
        while (it1.hasNext() && it2.hasNext()) {
            E e1 = it1.next();
            E e2 = it2.next();
            if (e1.compareTo(e2) <= 0) {
                l3.add(e1);
                it2.previous();
            } else {
                l3.add(e2);
                it1.previous();
            }
        }
        if (it1.hasNext()) {
            l3.addAll(l1.subList(it1.nextIndex(), l1.size()));
        }
        if (it2.hasNext()) {
            l3.addAll(l2.subList(it2.nextIndex(), l2.size()));
        }
        return l3;
    }
}