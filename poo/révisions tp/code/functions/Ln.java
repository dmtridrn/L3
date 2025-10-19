package functions;

import java.util.Optional;

public record Ln() implements RealFunction {
    @Override
    public String toString(){
        return "ln";
    }

    public Optional<Double> eval(double x){
        if(x<=0){
            return Optional.empty();
        }
        return Optional.of(Math.log(x));
    }

    public RealFunction diff(){
        return new Inverse();
    }
}
