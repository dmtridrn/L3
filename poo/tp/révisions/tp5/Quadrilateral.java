package révisions.tp5;

import java.awt.geom.Point2D;

public class Quadrilateral implements Shape2D {
    private final Point2D.Double s1;
    private final Point2D.Double s2;
    private final Point2D.Double s3;
    private final Point2D.Double s4;

    public Quadrilateral(Point2D.Double s1, Point2D.Double s2, Point2D.Double s3, Point2D.Double s4) {
        this.s1 = new Point2D.Double(s1.x, s1.y);
        this.s2 = new Point2D.Double(s2.x, s2.y);
        this.s3 = new Point2D.Double(s3.x, s3.y);
        this.s4 = new Point2D.Double(s4.x, s4.y);
    }

    public double perimeter(){
        return s1.distance(s2) + s2.distance(s3) + s3.distance(s4) + s4.distance(s1);
    }
    public double surface(){
        double x1 = s3.x - s1.x;
        double y1 = s3.y - s1.y;

        double x2 = s4.x - s2.x;
        double y2 = s4.y - s2.y;

        return 0.5 * (x1 * y2 - x2 * y1);
    }
}
