package révisions.tp5;

public interface Shape2D {
    double perimeter();
    double surface();

    default boolean checkInvariant(){
        return true;
    }
}
