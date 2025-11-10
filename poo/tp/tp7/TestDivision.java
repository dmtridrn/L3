package tp.tp7;

public class TestDivision {
    static Try<Integer> divide(int a, int b) {
        if (b == 0) return Try.failure(new ArithmeticException());
        else return Try.success(a / b);
    }

    public static void main(String[] args) {
        phase1();
        phase2();
    }

    private static void phase1() {
        Try<Integer> r1 = divide(9, 3);
        // premier test
        if (r1.isSuccess()) System.out.println("Resultat : " + r1.get()); // dans ce cas, n'affiche rien
        else System.out.println("Echec : " + r1.getError());// dans ce cas, affiche "Echec : java.lang.ArithmeticException"
        // deuxième test
        r1.tryCatch(
                result -> {
                    System.out.println("Resultat: " + result);
                },
                error -> {
                    System.out.println("Erreur : " + error);
                }
        ); // dans ce cas, affiche "Erreur : java.lang.ArithmeticException"
    }

    private static void phase2() {
        // troisième test
        var r3 = divide(50,2)
            .map(x -> x + 12)
            .flatMap(x -> divide(x, 9))
            .flatMap(x -> divide(x, 2))
            .map(x -> 5 * x);
        if (r3.isSuccess()) {
            System.out.println("Resultat : " + r3.get());
        } else {
            System.out.println("Echec : " + r3.getError());
        } // doit afficher "Resultat : 10"

    }
}
