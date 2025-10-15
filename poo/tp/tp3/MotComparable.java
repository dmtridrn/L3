package tp3;

public class MotComparable implements Comparable{

    String mot;

    public MotComparable(String mot){
        this.mot = mot;
    }

    @Override
    public Object value() {
        return mot;
    }

    @Override
    public String toString(){
        return mot;
    }

    @Override
    public boolean estPlusGrand(Comparable i) {
        if(!(i.value() instanceof String)){
            throw new IllegalArgumentException("mets un string");
        }
        String mot2 = (String)i.value();
        String mot1 = (String)this.value();
        return mot1.compareTo(mot2) > 0;
    }
    
}
