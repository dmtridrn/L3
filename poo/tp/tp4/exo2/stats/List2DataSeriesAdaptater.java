package stats;

import java.util.List;

public class List2DataSeriesAdaptater implements DataSeries{

    private List<Double> liste;

    public List2DataSeriesAdaptater(List<Double> liste){
        this.liste = liste;
    }
    
    public double read(int i){
        return this.liste.get(i);
    }
    public int length(){
        return this.liste.size  ();
    }
}
