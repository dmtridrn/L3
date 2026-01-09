package annale2017;
import java.util.concurrent.LinkedBlockingQueue;

public class PooledDM implements DownloadManager{

    LinkedBlockingQueue<Download> queue;
    int nombreThreads;

    public PooledDM(int n){
        this.queue = new LinkedBlockingQueue<>();
        for(int i= 0; i < n; i++){
            Thread.ofPlatform().start(() -> {
                try{
                    while(true){
                        Download dl = queue.take();
                        dl.download();
                    }
                }
                catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
            });
        }
    }

    @Override
    public void submit(Download dl) {
        queue.offer(dl);
    }
    
}
