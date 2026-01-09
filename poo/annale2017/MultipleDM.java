package annale2017;

public class MultipleDM implements DownloadManager {
    int n;
    int curr = 0;

    public MultipleDM(int n){
        this.n = n;
    }

    @Override
    public void submit(Download dl) {
        Thread.ofVirtual().start(() -> {
            try{
                synchronized(this){
                    while(curr > n){
                        wait();
                    }
                    curr ++;
                }

                dl.download();

                synchronized(this){
                    curr--;
                    notifyAll();
                }
            }
            catch (InterruptedException e){
                Thread.currentThread().interrupt();
            }
        });
    }
    
}
