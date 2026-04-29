import static java.lang.Math.*;

public class MainFour {
    public static void main(String[] args) {
        // double angulo = atan2(sqrt(3), 1);

        double respuesta = (magnitud(-3, 4) * magnitud(12, 9)) / 2;
        System.out.println("Angulo: " + respuesta);
    }

    public static double magnitud(int x, int y) {
        return sqrt(pow(x, 2) + pow(y, 2));
    }

    public static double pow(float base, float expo) {
        for (int i = 1; i < expo; i++) {
            base = base * base;
        }
        return base;
    }
}