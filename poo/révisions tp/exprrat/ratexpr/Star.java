package ratexpr;

public final class Star implements Rat{
    final Rat expr;

    public Star(Rat expr){
        this.expr = expr;
    }

    public Rat derivee(char c){
        return new Append(expr.derivee(c), new Star(expr));   
    }

    public boolean containsUnit(){
        return true;
    }

    public String toString(){
        return "(" + expr.toString() + "*)";
    }

    public Rat getExpr(){
        return this.expr;
    }
}
