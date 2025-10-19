/*
My Name
*/

import java.util.List;
import java.util.Map;

public class Test {
    public static void main(String[] args) {


	/* Tests 1.1 */
	Context.Formule tt = Context.Value(true); // true
	Context.Formule ff = Context.Value(false); // false
	Context.Formule p = Context.Variable("p"); // p
	Context.Formule q = Context.Variable("q"); // q
	Context.Formule ex1 = Context.Futur(p); // F p
	Context.Formule ex2 = Context.Next(q); // X q
	Context.Formule ex3 = Context.Until(p,ex2); // p U (X q)
	Context.Formule ex4 = Context.Or(List.of(p, q, ff)); // p || q || false
	Context.Formule ex5 = Context.Neg(q); // !q
	Context.Formule ex6 = Context.And(List.of(ex3, ex4, tt)); // (p U (X q)) && (p || q || false) && true


	/* Test 2.2 */
	System.out.println(tt); // true
	System.out.println(ff); // false
	System.out.println(p); // p
	System.out.println(q); // q
	System.out.println(ex1); // (F p)
	System.out.println(ex2); // (X q)
	System.out.println(ex3); // (U p (X q))
	System.out.println(ex4); // (or p  q false)
	System.out.println(ex5); // (not q)
	System.out.println(ex6); // (and (U p (X q)) (or p q false) true)


	
	/* Tests 2.3 */
	/*
	Context.Formule ex7 = Context.And(List.of(p, q));
        System.out.println(ex7); // (and p q)
        System.out.println(ex7.substitute(Map.of(
                "q", p
        ))); // (and p p)
        System.out.println(ex7.substitute(Map.of(
                "p", q,
                "q", p
        ))); // (and q p)
        System.out.println(ex7.substitute(Map.of(
                "p", tt,
                "q", ff
        ))); // (and true false)
        System.out.println(ex7.substitute(Map.of(
                "q", ex7
        ))); // (and p (and p q))
	*/

	
	/* Tests 2.4.1 */
	/*
	System.out.println(Context.And(List.of(p, tt))); // p
        System.out.println(Context.Or(List.of(q, ff))); // false

        System.out.println(Context.And(List.of(tt, tt))); // true
        System.out.println(Context.And(List.of(tt, ff))); // false
        System.out.println(Context.And(List.of(ff, ff))); // false

        System.out.println(Context.Or(List.of(tt, tt))); // true
        System.out.println(Context.Or(List.of(tt, ff))); // true
        System.out.println(Context.Or(List.of(ff, ff))); // false

        System.out.println(Context.Neg(q)); // (not q)
	System.out.println(Context.Neg(tt)); // false
        System.out.println(Context.Neg(Context.Neg(q))); // q

        Context.Formule ex8 = Context.And(List.of(p, q, tt));
        System.out.println(ex8); // (and p q)
        Context.Formule ex9 = Context.Neg(q);
        Context.Formule ex10 = Context.Or(List.of(ex8, ex9, ff));
        System.out.println(ex10); // (or (and p q) (not q))

        System.out.println(ex8.substitute(Map.of(
                "p", tt,
                "q", ff
        ))); // true
	// Remarquez que les résultats des tests des parties précédentes sont aussi modifiés. 
	*/

	
	/* Bonus 4.2.2 */
	/*
	// Définitions de R et G
	Context.Formule np = Context.Neg(p); // (neg p)
	Context.Formule ex11 = Context.Globally(p); // G p
	Context.Formule ex12 = Context.Release(nq,np); // (neg q) R (neg p)

	// toString()
	System.out.println(ex11); // (G p)
	System.out.println(ex12); // (R (not q) (not p))

	// Pour la simplification
	Context.Formule ex13 = Context.Futur(tt); // true
	Context.Formule ex13 = Context.Until(ff,p); // p 
	System.out.println(ex12); // true
	System.out.println(ex13); // p
	*/
    }
}

