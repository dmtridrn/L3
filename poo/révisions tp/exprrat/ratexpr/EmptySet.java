package ratexpr;

import ratexpr.*;

public final class EmptySet implements Rat{

    public boolean containsUnit(){
        return false;
    }

    public Rat derivee(char c){
        return new EmptySet();
    }
    
    @Override
    public String toString(){
        return "∅";
    }

    public EmptySet getEmptySet(){
        return new EmptySet();
    }
}
