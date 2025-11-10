package tp.tp8;

import java.util.function.UnaryOperator;

public interface Transformable<T> {
    T getElement();
    void transorm(UnaryOperator<T> trans);
}
