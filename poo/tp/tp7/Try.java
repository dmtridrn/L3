package tp.tp7;

import java.util.function.Consumer;
import java.util.function.Function;

public abstract sealed class Try<R> permits Try.Success, Try.Failure{
    private R res;

    //FONCTIONS ABSTRAITES
    abstract boolean isSuccess();
    abstract R get();
    abstract Throwable getError();
    abstract void tryCatch(Consumer<R> onSuccess, Consumer<Throwable> onFailure);
    abstract <U> Try<U> map(Function<R, U> onSuccess);
    abstract <U> Try<U> flatMap(Function<R, Try<U>> onSuccess);
    
    //CLASSES INTERNES
    public final static class Success<R> extends Try<R>{
        private R res;
        private Success(R res){
            this.res = res;
        }

        public boolean isSuccess(){
            return true;
        }

        public R get(){
            return this.res;
        }
        
        public Throwable getError(){
            throw new IllegalStateException("pas d'erreur");
        }

        public void tryCatch(Consumer<R> onSuccess, Consumer<Throwable> onFailure){
            onSuccess.accept(res);
        }

        public <U> Try<U> map(Function<R, U> onSuccess){
            try{
                U result = onSuccess.apply(res);
                return success(result);
            }
            catch(Exception e){
                return failure(e);
            }
        }

        public <U> Try<U> flatMap(Function<R, Try<U>> onSuccess){
            try{
                return onSuccess.apply(res);
            }
            catch(Exception e){
                return failure(e);
            }
        }
    }

    public final static class Failure<R> extends Try<R>{
        Throwable error;
        private Failure(Throwable error){
            this.error = error;
        }

        public boolean isSuccess(){
            return false;
        }

        public R get(){
            throw new IllegalStateException(error);
        }

        public Throwable getError(){
            return error;
        }

        public void tryCatch(Consumer<R> onSuccess, Consumer<Throwable> onFailure){
            onFailure.accept(error);
        }

        public <U> Try<U> map(Function<R, U> onSuccess){
            return failure(error);
        }

        public <U> Try<U> flatMap(Function<R, Try<U>> onSuccess){
            return failure(error);
        }
    }

    //FABRIQUES
    public static <R> Success<R> success(R res){
        return new Success<>(res);
    }

    public static <R> Failure<R> failure(Throwable e){
        return new Failure<>(e);
    }
}
