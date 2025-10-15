public class Complexe {
    private double reel;
    private double imag;

    private static final Complexe I = new Complexe(0, 1);
    private static final Complexe UN = new Complexe(1, 0);
    private static final Complexe ZERO = new Complexe(0, 0);

    public static Complexe fromPolarCoordinates(double rho, double theta){
        double reel = rho * Math.cos(theta);
        double imag = rho * Math.sin(theta);
        return new Complexe(reel, imag);
    }

    public static Complexe fromCarCoordinates(double reel, double imag){
        return new Complexe(reel, imag);
    }

    private Complexe (double reel, double imag){
        this.reel = reel;
        this.imag = imag;
    }
        public double getReel() {
            return reel;
        }

        public double getImag() {
            return imag;
        }

        public Complexe conjugue() {
            return new Complexe(reel, -imag);
        }

        public double module() {
            return Math.sqrt(reel * reel + imag * imag);
        }

        public double argument() {
            return Math.atan2(imag, reel);
        }

    @Override
    public String toString(){
        return String.format("(%d + %d i)", reel, imag);
    }

    public static Complexe add(Complexe c1, Complexe c2){
        return new Complexe(c1.reel + c2.reel, c1.imag + c2.imag);
    }

    public static Complexe mult(Complexe c1, Complexe c2){
        return new Complexe((c1.reel*c2.reel)-(c1.imag*c2.imag),
                            (c1.reel*c2.imag)+(c1.imag*c2.reel));
    }

    public static Complexe subs(Complexe c1, Complexe c2){
        return new Complexe(c1.reel - c2.reel, c1.imag - c2.imag);
    }

    public static Complexe div(Complexe c1, Complexe c2){
        return new Complexe(((c1.reel*c2.reel)+(c1.imag*c2.imag))/
                            ((c2.reel)*(c2.reel)+(c2.imag)*(c2.imag)),
                            ((c1.imag*c2.reel)-(c1.reel*c2.imag))/
                            (c2.reel)*(c2.reel)+(c2.imag)*(c2.imag));
    }

    @Override
    public boolean equals(Object other) {
        if (!(other instanceof Complexe)) return false;
        Complexe c = (Complexe) other;
        return this.reel == c.reel && this.imag == c.imag;
    }

}
