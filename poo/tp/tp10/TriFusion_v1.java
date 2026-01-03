import java.util.*;

public class TriFusion {

    private TriFusion() {     }

    public static <E extends Comparable<? super E>> List<E> triMonoThread(List<E> l) {
        if (l.size() <= 1) return l;

        int pivot = Math.floorDiv(l.size(), 2);
        List<E> l1 = triMonoThread(l.subList(0, pivot));
        List<E> l2 = triMonoThread(l.subList(pivot, l.size()));
        return Fusion.fusion(l1, l2);
    }
}






