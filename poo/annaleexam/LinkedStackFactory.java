package annaleexam;

public class LinkedStackFactory<E> implements StackFactory<E>{
    public LinkedStack<E> create(){
        return new LinkedStack<>();
    }
}
