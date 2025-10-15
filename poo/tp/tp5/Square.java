package tp5;

import java.awt.geom.Point2D;

public class Square extends Rectangle {
    
    public Square(Point2D.Double s1, Point2D.Double s2, Point2D.Double s3, Point2D.Double s4) {
        super(s1, s2, s3, s4);
        if (!checkInvariant()) {
            throw new IllegalArgumentException("Tous les côtés doivent être égaux");
        }
    }

    @Override
    public boolean checkInvariant() {
        if (!super.checkInvariant()) {
            return false;
        }
        
        double side1 = getS1().distance(getS2());
        double side2 = getS2().distance(getS3());
        double side3 = getS3().distance(getS4());
        double side4 = getS4().distance(getS1());
        
        return Math.abs(side1 - side2) < 1e-10 
            && Math.abs(side2 - side3) < 1e-10 
            && Math.abs(side3 - side4) < 1e-10;
    }
}