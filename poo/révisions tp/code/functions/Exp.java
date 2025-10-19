package functions;

import java.util.Optional;

public record Exp() implements RealFunction {
    @Override
    public String toString(){
        return "exp";
    }

    public Optional<Double> eval(double x){
        return Optional.of(Math.exp(x));
    }

    public RealFunction diff(){
        return new Exp();
    }
}
