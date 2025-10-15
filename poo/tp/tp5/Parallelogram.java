package tp5;

import java.awt.geom.Point2D;

public class Parallelogram extends Quadrilateral{

    public Parallelogram(Point2D.Double s1, Point2D.Double s2, Point2D.Double s3, Point2D.Double s4){
        super(s1, s2, s3, s4);
        if (!checkInvariant()) {
            throw new IllegalArgumentException("Les côtés opposés doivent être parallèles");
        }
    }

    @Override
    public boolean checkInvariant() {
        double dx1 = getS2().x - getS1().x;
        double dy1 = getS2().y - getS1().y;
        double dx2 = getS3().x - getS4().x;
        double dy2 = getS3().y - getS4().y;
        
        return Math.abs(dx1 * dy2 - dx2 * dy1) < 1e-10;
    }
}
