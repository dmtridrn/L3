package stats;
import java.util.List;
import java.util.ArrayList;;

public class Main {

    public static void main(String[] args){
        List<Double> liste = new ArrayList<>();
        liste.add(64.51);
        liste.add(138.89);
        liste.add(-25.5);
        liste.add(22.87);

        DataSeries data = new List2DataSeriesAdaptater(liste);

        double moyenne = Stats.average(data);
        double ecartType = Stats.stddev(data);

        System.out.println("Moyenne : " + moyenne);
        System.out.println("Écart-type : " + ecartType);
    }
}
