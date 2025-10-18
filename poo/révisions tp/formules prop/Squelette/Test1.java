import java.util.List;

public class Test1 {
    public static void main(String[] args) {
        Context.Formule tt = Context.Value(true); // true
        Context.Formule ff = Context.Value(false); // false
	    Context.Formule p = Context.Variable("p"); // p
        Context.Formule q = Context.Variable("q"); // q
        Context.Formule ex1 = Context.And(List.of(p, q, tt)); // p && q && true
        Context.Formule ex2 = Context.Neg(q); // !q
        Context.Formule ex3 = Context.Or(List.of(ex1, ex2, ff)); // (p && q && true) || !q
    }
}
