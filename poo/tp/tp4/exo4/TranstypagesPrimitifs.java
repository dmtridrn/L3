public class TranstypagesPrimitifs {
    public static void main(String[] args) {
        int vint = 1234567891;
        short vshort = 42;
        float vfloat = 9.2E11f;
        vshort = (short)vint;
        System.out.println("vint = " + vint +", vshort = " + vshort + ", vfloat = " + vfloat);
    }
}
