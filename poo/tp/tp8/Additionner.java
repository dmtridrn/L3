package tp.tp8;

import java.util.function.BinaryOperator;
import java.util.function.UnaryOperator;

public class Additionner implements UnaryOperator<Integer>{
    Integer elt;
    public Additionner(Integer elt){
        this.elt = elt;
    }

    @Override
    public Integer apply(Integer a){
        return Integer.valueOf(elt + a);
    }
}
