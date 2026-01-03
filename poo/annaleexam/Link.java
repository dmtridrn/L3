package annaleexam;

public record Link<E>(E content, Chain<E> nextLink) implements Chain<E>{
    
}
