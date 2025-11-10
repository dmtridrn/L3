package tp.tp8;

import java.util.function.UnaryOperator;

public class EntierTranformable implements Transformable<Integer>{
    Integer entier;
    public EntierTranformable(Integer i){
        this.entier = i;
    }

    public Integer getElement() {
        return this.entier;
    }

    @Override
    public void transorm(UnaryOperator<Integer> trans) {
        entier = trans.apply(entier);
    }

    @Override
    public String toString(){
        return this.entier.toString();
    }
    

    public static void main(String[] args){
        EntierTranformable e = new EntierTranformable(Integer.valueOf(0));
        e.transorm(new Additionner(15));
        System.out.println(e.toString());
        e.transorm((x) -> x*2);
        System.out.println(e.toString());
        e.transorm((x) -> x = 0);
        System.out.println(e.toString());
    }
}
