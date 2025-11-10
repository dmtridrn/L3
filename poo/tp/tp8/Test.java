package tp.tp8;

import java.util.function.Consumer;

public class Test {
    
    public static void main(String[] args){
        MaListe<Integer> nombres = new MaListe<>();
        MaListe<Personnes> pers = new MaListe<>();
        nombres.add(10);
        nombres.add(10);
        nombres.add(10);
        nombres.add(10);
        nombres.add(10);
        nombres.add(10);
        nombres.add(10);
        nombres.add(81938091);
        Consumer<Integer> cons = new Consumer<Integer>() {
            int cpt = 1;
            @Override
            public void accept(Integer x){
                System.out.println(cpt++ + " : " + x);
            }
        };
        nombres.pourChacun(cons);
    }
}
