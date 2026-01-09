package annale2017;

public class Download {

    public void download(){
        try { 
            Thread.sleep((long) (10000 * Math.random())); 
        }
        catch (InterruptedException e) { 
            System.out.println("Téléchargement interrompu."); 
        }
    }
    
}
