package tp11;

import java.util.ArrayList;
import java.util.concurrent.CompletableFuture;

public class Main {
    
    private static void printThread(int i) {
        System.out.println("Lambda " + i + " exécutée dans le thread: " + Thread.currentThread().getName());
    }
    
    public static int f(int i) {
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) { }
        finally{
            printThread(i);
        }
        return i * i;
    }
    
    public static void main(String[] args){
        long startTime = System.currentTimeMillis();
        
        var futures = new ArrayList<CompletableFuture<Integer>>(5);
        futures.add(CompletableFuture.supplyAsync(() -> f(1)));
        futures.add(CompletableFuture.supplyAsync(() -> f(2)));
        futures.add(CompletableFuture.supplyAsync(() -> f(3)));
        futures.add(CompletableFuture.supplyAsync(() -> f(4)));
        futures.add(CompletableFuture.supplyAsync(() -> f(5)));
        
        CompletableFuture<Integer> result = futures.get(0).thenCombine(futures.get(1), (a, b) -> {
            printThread(10);
            return a + b;
        }).thenCombine(futures.get(2), (a, b) -> {
            printThread(11);
            return a + b;
        }).thenCombine(futures.get(3), (a, b) -> {
            printThread(12);
            return a + b;
        }).thenCombine(futures.get(4), (a, b) -> {
            printThread(13);
            return a + b;
        });
        
        int sum = result.join();
        long endTime = System.currentTimeMillis();
        
        System.out.println("\nRésultat final: " + sum);
        System.out.println("Temps d'exécution: " + (endTime - startTime) + " ms");
    }
}