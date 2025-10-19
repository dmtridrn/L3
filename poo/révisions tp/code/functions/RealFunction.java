package functions;

import java.util.Optional;

public interface RealFunction {

    /* les méthodes d’instance */

    Optional<Double> eval(double x);

    RealFunction diff();

    /* les fabriques statiques */

    public static RealFunction constant(double a) {
        return new Constant(a);
    }

    public static RealFunction linear(double a) {
        return new Linear(a);
    }

    public static RealFunction inverse() {
        return new Inverse();
    }

    public static RealFunction exp() {
        return new Exp();
    }

    public static RealFunction ln() {
        return new Ln();
    }

    public static RealFunction plus(RealFunction a, RealFunction b) {
        return new Plus(a, b);
    }

    public static RealFunction times(RealFunction a, RealFunction b) {
        return new Times(a, b);
    }

    public static RealFunction compose(RealFunction a, RealFunction b) {
        return new Compose(a, b);
    }

}
