package tp.tp7;

import java.util.function.Consumer;
import java.util.function.Function;

public record Success<R>(R result) implements Try<R>{

    @Override
    public boolean isSucess() {
        return true;
    }

    @Override
    public R get() {
        return result;
    }

    @Override
    public Throwable getError() {
        throw new IllegalStateException("pas d'erreur");
    }

    @Override
    public void tryCatch(Consumer<R> onSuccess, Consumer<Throwable> onFailure) {
        onSuccess.accept(get());
    }

    @Override
    public <U> Try<U> map(Function<R, U> onSuccess) {
        
    }   

    @Override
    public <U> Try<U> flatMap(Function<R, Try<U>> onSuccess) {
        // TODO Auto-generated method stub
        throw new UnsupportedOperationException("Unimplemented method 'flatMap'");
    }

    
}
