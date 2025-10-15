package tp3;


public class SequenceMots implements Sequencable{

MotComparable[] sequence;

    public SequenceMots(String[] tab){
        MotComparable[] temp = new MotComparable[tab.length];
        for(int i = 0; i<tab.length; ++i){
            temp[i] = new MotComparable(tab[i]);
        }
        this.sequence = temp;
    }
    @Override
    public int longueur() {
        return sequence.length;
    }

    @Override
    public Comparable get(int i) {
        if((i<this.sequence.length) && i>-1){
            return sequence[i];
        }
        throw new IllegalArgumentException("indice trop élevé ou négatif");
    }

    @Override
    public void echange(int i, int j) {
        if((i<this.sequence.length) && (i>-1) && (j<this.sequence.length) && (j>-1)){
            MotComparable temp = this.sequence[i];
            this.sequence[i] = this.sequence[j];
            this.sequence[j] = temp;
        }
        else{
            throw new IllegalArgumentException("indices incorrects");
        }
    }

    public static void main(String[] args){
        String[] temp = new String[20];
        for(int i = 0; i<20; ++i){
            temp[i] = Integer.toString((int)(Math.random()*5000));
        }
        SequenceMots test = new SequenceMots(temp);
        test.affiche();
        System.err.println("TRI");
        test.triBulle();
        test.affiche();
    }

}