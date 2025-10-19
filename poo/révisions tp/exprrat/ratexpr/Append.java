package ratexpr;

import ratexpr.*;

public final class Append implements Rat{
    
    final Rat first;
    final Rat second;

    public Append(Rat first, Rat second){
        this.first = first;
        this.second = second;
    }

    private Rat phi(Rat r){
        if(r.containsUnit()){
            return new Epsilon();
        }
        else return new EmptySet();
    }

    public Rat derivee(char c){
        return new Union(new Append(first.derivee(c), second), new Append(phi(first), second.derivee(c)));
    }

    public boolean containsUnit(){
        return this.first.containsUnit() && this.second.containsUnit();
    }

    public String toString(){
        return "(" + first.toString() + "." + second.toString() + ")";
    }

    public Rat getFirst(){
        return this.first;
    }

    public Rat getSecond(){
        return this.second;
    }

}
