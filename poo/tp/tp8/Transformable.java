package tp8;

import java.util.function.UnaryOperator;

public interface Transformable<T> {
    T getElement();
    void transform(UnaryOperator<T> trans);
}
