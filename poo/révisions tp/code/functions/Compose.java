package functions;

import java.util.Optional;

public record Compose(RealFunction a, RealFunction b) implements RealFunction {
    @Override
    public String toString(){
        return "(" + a.toString() + "◦" + b.toString()+ ")";
    }

    public Optional<Double> eval(double x){
        return Optional.of(a.eval(b.eval(x).get()).get());
    }


    public RealFunction diff(){
        return new Times(b.diff(), new Compose(a.diff(), b));
    }
}
