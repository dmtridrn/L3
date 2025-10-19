package ratexpr;

public final class Union implements Rat{
    final Rat first;
    final Rat second;

    public Union(Rat first, Rat second){
        this.first = first;
        this.second = second;
    }


    public Rat derivee(char c){
        return new Union(first.derivee(c), second.derivee(c));
    }

    public boolean containsUnit(){
        return this.first.containsUnit() || this.second.containsUnit();
    }

    public String toString(){
        return "(" + first.toString() + "+" + second.toString() + ")";
    }

    public Rat getFirst(){
        return this.first;
    }

    public Rat getSecond(){
        return this.second;
    }
}
