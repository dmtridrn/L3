
import static ratexpr.Rat.*;

import java.util.List;

import ratexpr.Rat;

public class Main {
    public static void main(String[] args) {
        testsSujet();
        // ajoutez vos tests ici (nouvelles méthodes)
    }

    /* tests fournis, à ne pas modifier */
    private static void testsSujet() {
        /* définir les classes section 2.1 */
        Rat a = symbol('a');
        Rat b = symbol('b');
        Rat c = symbol('c');
        Rat d = symbol('d');
        Rat u = union(append(star(union(a, epsilon())), emptySet()), star(d));

        System.out.println("******** toString()  section 2.2 *********");
        System.out.println("u=" + u);
        Rat p = star(append(append(a, b), c));
        System.out.println(p);
        Rat z = union(p, epsilon());
        System.out.println(z);
        Rat q = star(union(append(d, c), c));
        System.out.println(append(q, p));

        System.out.println("******** dérivée ********");
        Rat i = star(append(append(a, b), c));
        System.out.println("i=" + i);
        System.out.println("D_a(i)=" + i.derivee('a'));

        Rat h = star(union(a, b));
        System.out.println(h.derivee('a'));

        System.out.println("*************contains******");
        System.out.println(p.derivee('a').derivee('b').containsUnit());
        System.out.println(p.contains("abc"));

        /*************** miroir *********/
        System.out.println("p=" + p);
        System.out.println("miroir =" + miroir(p));
    }

    public static Rat miroir(Rat r) { return null; /* compléter ! */ }


}