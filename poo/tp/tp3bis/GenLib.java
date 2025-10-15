package tp3bis;

import java.util.List;
import java.util.Collection;

public class GenLib {
    

    //CLASSE LOCALE
    public static Generateur nouveauGenerateurAleatoire(int m){
        class Randm implements Generateur{
            public int suivant(){
                return (int)(Math.random()*m);
            }
        }
        return new Randm();
    }

    //CLASSE MEMBRE
    static class GenerateurArithmetique implements Generateur{
        int actuel= 0;
        int raison;
        public GenerateurArithmetique(int r){
            this.raison = r;
        }

        public int suivant(){
            if(this.raison == 0){
                return 0;
            }
            this.actuel = this.actuel + this.raison;
            return this.actuel;
        }
    }
    public static Generateur nouveauGenerateurArithmetique(int r) {
        return new GenerateurArithmetique(r);
    }

    //CLASSE ANONYME
    public static Generateur nouveauGenerateurGeometrique(int r){
        if(r == 0 || r == 1){
            return new Generateur() {
                public int suivant(){
                    if(r == 0){
                        return 0;
                    }
                    return 1;
                }
            };
        }
        return new Generateur(){
            int actuel = 1;
            int raison = r;

            public int suivant(){
                this.actuel = this.actuel * raison;
                return this.actuel;
            }
        };
    }

    //LAMBDA EXPRESSION
    public static Generateur nouveauGenerateurFibo(){
        final int[] fib = {0,1};
        return()->{
            int result = fib[0];
            int temp = fib[0] + fib[1];
            fib[0] = fib[1];
            fib[1] = temp;
            return result;
        };
    }


    static int somme(Generateur gen, int n){
        int acc = 0;
        for(int i = 0; i < n; ++i){
            acc += gen.suivant();
        }
        return acc;
    }

    public static Generateur nouveauGenerateurCollection(Collection<Integer> collection){
        return new Adaptateur(collection);
    }


    public static void main(String[] args) {
        Collection<Integer> maCollection = List.of(56, 23, 78, 64, 19);
        Generateur genCollection = nouveauGenerateurCollection(maCollection);
        System.out.println(somme(genCollection, 90));
        System.out.println(56+23+78+64+19);
    }
}
