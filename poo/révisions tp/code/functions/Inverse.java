package functions;

import java.util.Optional;

public record Inverse() implements RealFunction{
    @Override
    public String toString(){
        return "(1/•)";
    }

    public Optional<Double> eval(double x){
        if(x == 0.0){
            return Optional.empty();
        }
        return Optional.of(1/x);
    }

    public RealFunction diff(){
        return new Times(new Constant(-1), new Times(new Inverse(), new Inverse()));
    }
}
