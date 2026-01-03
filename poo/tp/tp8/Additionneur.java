package tp8;

import java.util.function.UnaryOperator;

public class Additionneur implements UnaryOperator<Integer>{

    Integer n;

    public Additionneur(Integer n) {
        this.n = n;
    }

    @Override
    public Integer apply(Integer arg0) {
        return n + arg0;
    }
    
}
