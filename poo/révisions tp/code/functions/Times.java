package functions;

import java.util.Optional;

public record Times(RealFunction a, RealFunction b) implements RealFunction {
    @Override
    public String toString(){
        return "(" + a.toString() + "·" + b.toString()+ ")";
    }

    public Optional<Double> eval(double x){
        return Optional.of(a.eval(x).get() * b.eval(x).get());
    }

    public RealFunction diff(){
        return new Plus(new Times(a.diff(), b), new Times(a, b.diff()));
    }
}
