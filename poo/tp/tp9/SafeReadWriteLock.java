package tp.tp9;

import java.util.function.Supplier;

public class SafeReadWriteLock implements VerrouFonc{
    
    private ReadWriteLock verrou = new ReadWriteLock();

    public <T> T lecture(Supplier<T> action){
        T res = null;
        try{
            verrou.debutLecture();
            res = action.get();
        }
        catch(InterruptedException e){
            e.printStackTrace();
        }
        finally{
            verrou.finLecture();
        }
        return res;
    }

    public void ecriture(Runnable action){
        try{
            verrou.debutEcriture();
            action.run(); 
        }
        catch(InterruptedException e){
            e.printStackTrace();
        }w
        finally{
            verrou.finEcriture();
        }
    }

}
