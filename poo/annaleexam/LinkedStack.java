package annaleexam;

public class LinkedStack<E> implements Stack<E>{
    Chain<E> chaine;

    public LinkedStack(){
        this.chaine = new Nothing<>();
    }

    public synchronized void push(E elt){
        Chain<E> nv = new Link<>(elt, chaine);
        chaine = nv;
    }
    
    public boolean isEmpty(){
        return chaine instanceof Nothing;

    }

    public synchronized E pop(){
        return switch (chaine) {
            case Link<E> l -> {
                this.chaine = l.nextLink();
                yield l.content();
            }
            case Nothing<E> n -> null;  
        };
    }
}
