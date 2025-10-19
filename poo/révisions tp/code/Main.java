import static functions.RealFunction.*;

import functions.RealFunction;

/* tests fournis, à ne pas modifier */
public class Main {
    public static void main(String[] args) {

    /* définir les classes section 2.1 */
        RealFunction a = constant(1); // 1
        RealFunction l = linear(2); // 2x
        RealFunction m = linear(-1); // -x
        RealFunction i = inverse();
        RealFunction exp = exp();
        RealFunction ln = ln();

        RealFunction af = plus(a, l); // 1 + 2x
        RealFunction para = times(l,l); // 4x² 
        RealFunction rExp = compose(exp, m); // exp(-x)


        System.out.println("******** toString()  section 2.2 *********");
        System.out.println("a=" + a);
        System.out.println("l=" + l);
        System.out.println("m=" + m);
        System.out.println("i=" + i);
        System.out.println("exp=" + exp);
        System.out.println("ln=" + ln);
        System.out.println("af=" + af);
        System.out.println("para=" + para);
        System.out.println("rExp=" + rExp);

        
     
        System.out.println("******** eval ********");
        System.out.println("a(2)=" + a.eval(2));
        System.out.println("l(2)=" + l.eval(2));
        System.out.println("m(2)=" + m.eval(2));
        System.out.println("i(2)=" + i.eval(2));
        System.out.println("i(0)=" + i.eval(2)); // Empty!
        System.out.println("exp(2)=" + exp.eval(2));
        System.out.println("ln(2)=" + ln.eval(2));
        System.out.println("af(2)=" + af.eval(2));
        System.out.println("para(2)=" + para.eval(2));
        System.out.println("rExp(2)=" + rExp.eval(2));

        System.out.println("******** diff ********");
        System.out.println("a'=" + a.diff());
        System.out.println("l'=" + l.diff());
        System.out.println("m'=" + m.diff());
        System.out.println("i'=" + i.diff());
        System.out.println("exp'=" + exp.diff());
        System.out.println("ln'=" + ln.diff());
        System.out.println("af'=" + af.diff());
        System.out.println("para'=" + para.diff());
        System.out.println("rExp'=" + rExp.diff());



    }

}