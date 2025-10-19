package functions;

import java.util.Optional;

public record Linear(double a) implements RealFunction{
    @Override
    public String toString(){
        return "(" + Double.toString(a) + "·•)";
    }

    public Optional<Double> eval(double x){
        return Optional.of(this.a*x);
    }

    public RealFunction diff(){
        return new Constant(this.a);
    }
}
