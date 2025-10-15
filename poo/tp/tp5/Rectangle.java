package tp5;

import java.awt.geom.Point2D;

public class Rectangle extends Parallelogram {
    
    public Rectangle(Point2D.Double s1, Point2D.Double s2, Point2D.Double s3, Point2D.Double s4) {
        super(s1, s2, s3, s4);
        if (!checkInvariant()) {
            throw new IllegalArgumentException("Les angles doivent être droits");
        }
    }

    @Override
    public boolean checkInvariant() {
        if (!super.checkInvariant()) {
            return false;
        }

        double dx1 = getS2().x - getS1().x;
        double dy1 = getS2().y - getS1().y;
        
        double dx2 = getS4().x - getS1().x;
        double dy2 = getS4().y - getS1().y;
        
        return Math.abs(dx1 * dx2 + dy1 * dy2) < 1e-10;
    }
}