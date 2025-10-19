package ratexpr;
import ratexpr.*;

public final class Symbol implements Rat{

    private char car;
    
    public Symbol(char car){
        this.car = car;
    }

    public Rat derivee(char c){
        if(c == this.car){
            return new Epsilon();
        }
        return new EmptySet();
    }

    public boolean contains(String str){
        
        char c = str.charAt(0);
        String nvstr = str.substring(1);
        
    }

    public boolean containsUnit(){
        return false;
    }
    
    @Override
    public String toString(){
        return String.valueOf(car);
    }

    public char getChar(){
        return this.car;
    }
}
