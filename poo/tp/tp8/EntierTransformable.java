package tp8;

import java.util.function.UnaryOperator;
import java.util.function.;

public class EntierTransformable implements Transformable<Integer> {

    Integer element;

    public EntierTransformable(Integer elt){
        this.element = elt;
    }

    @Override
    public Integer getElement() {
        return element;
    }

    @Override
    public void transform(UnaryOperator<Integer> trans) {
        element = trans.apply(element);
    }

    public static void main(String[] args){
        Transformable<Integer> test = new EntierTransformable(0);
        test.transform(e -> e * 2);
        test.transform(e -> e + 15);
        test.transform(e -> e * 0);
    }
    
}
