package tp.tp9;

public class ThreadSafeReadWriteBox {
    private SafeReadWriteLock verrou = new SafeReadWriteLock();
    private String ressource;

    public ThreadSafeReadWriteBox(String ressource){
        this.ressource = ressource;
    }

    public String getRessource(){
        return verrou.lecture(() -> this.ressource);
    }

    public void setRessource(String str){
        verrou.ecriture(() -> {
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            this.ressource = str;
        });
    }
}
