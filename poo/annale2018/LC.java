package annale2018;

public abstract class LC<T> {
    private LC() { }
    public static <T> LC<T> vide() { return new Vide<>(); }
    public static <T> LC<T> cons(T tete, LC<T> queue) { return new Cons<>(tete, queue); }
    
    public abstract T tete();
    public abstract boolean estVide();
    
    public static class OperationSurListeVideException extends RuntimeException { }
    
    private static final class Vide<T> extends LC<T> {
        @Override
        public T tete() { throw new OperationSurListeVideException(); }
        @Override
        public boolean estVide() { return true; }
    }
    
    private static final class Cons<T> extends LC<T> {
        private final T tete; private final LC<T> queue;
        private Cons(T tete, LC<T> queue) { this.tete = tete; this.queue = queue; }
        @Override
        public T tete() { return tete; }
        @Override
        public boolean estVide() { return false; }
    }
}
