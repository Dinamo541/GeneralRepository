public class MainTwo {

    public static int A(int m, int n) {
        System.out.println("A(" + m + ", " + n + ")");
        if ((m > 0) && (n == 0)) {
            return A(m - 1, 1);
        } else if ((m > 0) && (n > 0)) {
            return A(m - 1, A(m, n -1));
        } else if ((m == 0) && (n > 0)) {
            return n + 1;
        }
        return 0;
    }

    public static void main(String[] args) {
        System.out.println("Akerman: " + A(4, 4));
    }
}