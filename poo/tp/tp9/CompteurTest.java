package tp.tp9;

public class CompteurTest {
    private final Compteur compteur = new Compteur();

    public void incrementerTest(){
        synchronized(compteur){
            compteur.incrementer();
            System.out.println(compteur.getCompte() + " obtenu après incrémentation");
            compteur.notifyAll();
        }
    }

    public void decrementerTest(){
        synchronized(compteur){
            while(compteur.getCompte() == 0){
                try {
                    compteur.wait();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            compteur.decrementer();
            System.out.println(compteur.getCompte() + " obtenu après décrémentation");
        }
    }

    public static void main(String[] args){
        CompteurTest test = new CompteurTest();

        Runnable incr1 = new Runnable() {
            @Override
            public void run(){
                test.incrementerTest();
            }
        };
        Thread t1 = new Thread(incr1);
        t1.start();

        Runnable incr2 = () -> test.incrementerTest();
        Thread.ofVirtual().start(incr2);

        Runnable decr1 = test::decrementerTest;
        Thread.ofPlatform().start(decr1);

        //decr2
        Thread.ofVirtual().start(test::decrementerTest);
    }
}
