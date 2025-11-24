package tp.tp9;

public class VerrouTest {
    public static void main(String[] args) throws InterruptedException{
        ThreadSafeReadWriteBox ent = new ThreadSafeReadWriteBox("Init");        Thread.ofVirtual().start(() -> ent.setRessource("A"));
        for(int i = 0; i < 5; i++){
            Thread.ofVirtual().start(() -> System.out.println(ent.getRessource()));
        }
        Thread.ofVirtual().start(() -> ent.setRessource("B"));
        for(int i = 0; i < 5; i++){
            Thread.ofVirtual().start(() -> System.out.println(ent.getRessource()));
        }
        Thread.sleep(5000);
    }

}
