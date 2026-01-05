package annale2017;
import java.util.function.Predicate;

public class DataStructure {
	private int[] tab;

	public DataStructure(int taille, int b) {
		tab = new int[taille];
		for (int i = 0; i < taille; i++)
			tab[i] = (int) (Math.random() * b);
	}

	public void choisir(Predicate<Integer> p) {
		for (int e : tab)
			if (p.test(e))
				System.out.println(e);
	}
}

class Test {
	public static void main(String[] args) {
		DataStructure data = new DataStructure(10, 20);
		// insérer ici les instructions demandées
        data.choisir(p -> true);
        //
        System.out.println();
        data.choisir(new Predicate<Integer>(){
            public boolean test(Integer e){
                return e%2 == 0;
            }
        });
        System.out.println();
        //
        data.choisir(p -> (p>10));
        
	}
}
