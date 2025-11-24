package tp.tp9;

import java.util.function.Supplier;

public interface VerrouFonc {
    <T> T lecture(Supplier<T> action);
    void ecriture(Runnable action);
}
