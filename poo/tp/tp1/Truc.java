class Truc {
    static int v1 = 0;
    int v2 = 0;

    public int getV1() {
        return v1;
    }

    public int getV2() {
        return v2;
    }

    public Truc() {
        v1++;
        v2++;
    }

    public static void main(String args[]) {
        System.out.println(new Truc().getV1());
        System.out.println(new Truc().getV2());
        System.out.println(new Truc().getV1());
    }
}