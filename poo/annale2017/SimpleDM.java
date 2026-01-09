package annale2017;

public class SimpleDM implements DownloadManager {

    @Override
    synchronized public void submit(Download dl) {
        Thread.ofVirtual().start(() -> {
            synchronized(this){
                dl.download();
            }
        });
    }
    
}
