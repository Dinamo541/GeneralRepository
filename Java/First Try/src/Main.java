import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        // Declaración de variables
        int intNumber = 10;
        double decimalNumber = 3.14;
        char character = 'A';
        boolean isTrue = true;
        String text = "Hola, Java";

        // Imprimir las variables
        System.out.println("Entero: " + intNumber);
        System.out.println("Decimal: " + decimalNumber);
        System.out.println("Carácter: " + character);
        System.out.println("Booleano: " + isTrue);
        System.out.println("text: " + text);

        // Crear un objeto Scanner
        Scanner scanner = new Scanner(System.in);

        // Leer un entero
        System.out.print("Ingresa un número entero: ");
        int numero = scanner.nextInt();

        // Leer un número decimal
        System.out.print("Ingresa un número decimal: ");
        double decimal = scanner.nextDouble();
        
        // Leer una cadena de texto
        System.out.print("Ingresa tu nombre: ");
        scanner.nextLine(); // Consumir el salto de línea pendiente
        String nombre = scanner.nextLine();
        
        // Mostrar los valores ingresados
        System.out.println("Número entero: " + numero);
        System.out.println("Número decimal: " + decimal);
        System.out.println("Nombre: " + nombre);
        
        // Cerrar el Scanner
        scanner.close();
    }
}