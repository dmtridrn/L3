package annaleexam;

public interface BlockingStack<E> extends Stack<E>{
    E popBlocking() throws InterruptedException;
}
