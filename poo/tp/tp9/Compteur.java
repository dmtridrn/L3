package tp.tp9;

public class Compteur {
    private int compte = 0;
    public synchronized int getCompte(){ return compte; }
    public synchronized void incrementer() { compte++; }
    public synchronized void decrementer() { compte--; }

}
