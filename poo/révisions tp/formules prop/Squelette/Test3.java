import java.util.List;
import java.util.Map;

public class Test3 {
    public static void main(String[] args) {
        Context.Formule tt = Context.Value(true); // true
        Context.Formule ff = Context.Value(false); // false
        Context.Formule p = Context.Variable("p"); // p
        Context.Formule q = Context.Variable("q"); // q
        Context.Formule ex1 = Context.And(List.of(p, q));
        System.out.println(ex1); // (and p q)
        System.out.println(ex1.substitute(Map.of(
                "q", p
        ))); // (and p p)
        System.out.println(ex1.substitute(Map.of(
                "p", q,
                "q", p
        ))); // (and q p)
        System.out.println(ex1.substitute(Map.of(
                "p", tt,
                "q", ff
        ))); // (and true false)
        System.out.println(ex1.substitute(Map.of(
                "q", ex1
        ))); // (and p (and p q))
    }
}
