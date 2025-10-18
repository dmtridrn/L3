import java.util.List;
import java.util.Map;

public class Test4 {
    public static void main(String[] args) {
        Context.Formule tt = Context.Value(true);
        Context.Formule ff = Context.Value(false);

        Context.Formule p = Context.Variable("p"); // p
        Context.Formule q = Context.Variable("q"); // q

        System.out.println(Context.And(List.of(p, tt))); // p
        System.out.println(Context.Or(List.of(q, ff))); // false

        System.out.println(Context.And(List.of(tt, tt))); // true
        System.out.println(Context.And(List.of(tt, ff))); // false
        System.out.println(Context.And(List.of(ff, ff))); // false

        System.out.println(Context.Or(List.of(tt, tt))); // true
        System.out.println(Context.Or(List.of(tt, ff))); // true
        System.out.println(Context.Or(List.of(ff, ff))); // false

        System.out.println(Context.Neg(q)); // (not q)
        System.out.println(Context.Neg(Context.Neg(q))); // q

        Context.Formule ex1 = Context.And(List.of(p, q, tt));
        System.out.println(ex1); // (and p q)
        Context.Formule ex2 = Context.Neg(q);
        Context.Formule ex3 = Context.Or(List.of(ex1, ex2, ff));
        System.out.println(ex3); // (or (and p q) (not q))

        System.out.println(ex1.substitute(Map.of(
                "p", tt,
                "q", ff
        ))); // true
    }
}
