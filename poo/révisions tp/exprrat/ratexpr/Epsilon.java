package ratexpr;

import ratexpr.*;

public final class Epsilon implements Rat{
    
    public Rat derivee(char c){
        return new EmptySet();    
    }

    public boolean containsUnit(){
        return true;
    }

    @Override
    public String toString(){
        return "Ɛ";
    }

    public Rat getEpsilon(){
        return new Epsilon();
    }

}
