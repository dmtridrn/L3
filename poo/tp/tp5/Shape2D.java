package tp5;

public interface Shape2D{
    double permieter();
    double surface();

    default boolean checkInvariant(){
        return true;
    }
    
}