import java.util.HashMap;
import java.util.Map;

public class MainFive {
    public static void main(String[] args) {

        HashMap<String, Integer> estudiantes = new HashMap<>();

        estudiantes.put("Juan", 85);
        estudiantes.put("Ana", 30);
        estudiantes.put("Luis", 90);

        for (Map.Entry<String, Integer> estudiante : estudiantes.entrySet()) {
            if (estudiante.getValue() >= 85) {
                System.out.println(estudiante.getKey() + " : " + estudiante.getValue());
            }
        }
    }
}