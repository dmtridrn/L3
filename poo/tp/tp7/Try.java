package tp.tp7;

import java.util.function.Consumer;
import java.util.function.Function;

public sealed interface Try<R> permits Success, Failure {
    
    public static <R> Success<R> success(R result){
        return new Success<>(result);
    }

    public static <R> Failure<R> failure(Throwable error){
        return new Failure(error);
    }

    boolean isSucess();

    R get();
    
    Throwable getError();
    
    void tryCatch(Consumer<R> onSuccess, Consumer<Throwable> onFailure);
    
    <U> Try<U> map(Function<R, U> onSuccess);
    
    <U> Try<U> flatMap(Function<R, Try<U>> onSuccess);
}
