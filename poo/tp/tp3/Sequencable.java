package tp3;
public interface Sequencable {

    public int longueur();
    public Comparable get(int i);
    public void echange (int i, int j);
    
    public default void affiche(){
        for(int i = 0; i<longueur(); ++i){
            System.out.println(get(i).toString());
        }
    }
    public default void triBulle(){
        boolean change = false;
        do{
            change = false;
            for(int i = 0; i<longueur()-1; ++i){
                Comparable a = get(i);
                Comparable b = get(i+1);
                if(a.estPlusGrand(b)){
                    echange(i, i+1);
                    change = true;
                }
            }
        }
        while (change);
    }
}