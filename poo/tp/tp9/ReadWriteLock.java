package tp.tp9;

public class ReadWriteLock {
    
    private boolean ecrAutorise;
    private int nbLecteurs = 0;

    synchronized void debutLecture() throws InterruptedException{
        while(ecrAutorise){
            wait();
        }
        nbLecteurs++;
    }

    synchronized void debutEcriture() throws InterruptedException{
        while(ecrAutorise || nbLecteurs>0){
            wait();
        }
        ecrAutorise = true;
    }

    synchronized void finLecture(){
        nbLecteurs--;
        if(nbLecteurs == 0){
            notify();
        }
    }

    synchronized void finEcriture(){
        ecrAutorise = false;
        notifyAll();
    }

    


}
