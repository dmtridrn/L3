import java.util.List;

public class Test2 {
    public static void main(String[] args) {
        Context.Formule tt = Context.Value(true);
        System.out.println(tt); // true

        Context.Formule ff = Context.Value(false);
        System.out.println(ff); // false

	    Context.Formule p = Context.Variable("p"); // p
        Context.Formule q = Context.Variable("q"); // q
        System.out.println(p); // p
        System.out.println(q); // p

        System.out.println(Context.And(List.of(p, tt))); // (and p true)
        System.out.println(Context.Or(List.of(q, ff))); // (and q false)

        System.out.println(Context.Neg(q)); // (not q)
        System.out.println(Context.Neg(Context.Neg(q))); // (not (not q))

        Context.Formule ex1 = Context.And(List.of(p, q, tt));
        System.out.println(ex1); // (and p q true)
        Context.Formule ex2 = Context.Neg(q);
        Context.Formule ex3 = Context.Or(List.of(ex1, ex2, ff));
        System.out.println(ex3); // (or (and p q true) (not q) false)
    }
}
