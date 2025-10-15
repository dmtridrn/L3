package tp3bis;

import java.util.Collection;
import java.util.Iterator;

public class Adaptateur implements Generateur{

    public Iterator<Integer> iter;


    Adaptateur(Collection<Integer> c){
        this.iter = c.iterator();
    }

    @Override
    public int suivant() {
        if(this.iter.hasNext()){
            return this.iter.next().intValue();
        }
        return 0;
    }

    
}
