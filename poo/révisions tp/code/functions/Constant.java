package functions;

import java.util.Optional;

public record Constant(double a) implements RealFunction{
    @Override
    public String toString(){
        return Double.toString(a);
    }

    public Optional<Double> eval(double x){
        return Optional.of(this.a);
    }

    public RealFunction diff(){
        return new Constant(0);
    }
}
