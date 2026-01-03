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
        Try<Integer> r1 = divide(1, 0);
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
        switch (r3) {
            case Try.Success(Integer r) -> System.out.println("Resultat : " + r);
            case Try.Failure(Throwable e) -> System.out.println("Echec : " + e);
        } // doit afficher "Resultat : 10"

    }
}
