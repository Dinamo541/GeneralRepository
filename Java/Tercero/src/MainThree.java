
class CuentaBancaria {

    private String titular;
    private double saldo;
    private int numeroCuenta;

    public CuentaBancaria(String newTitular, Double newSaldo, int newNumeroCuenta) {
        titular = newTitular;
        saldo = newSaldo;
        numeroCuenta = newNumeroCuenta;
    }

    public void depositar(double monto) {
        saldo += monto;
    }

    public void retirar(double monto) {
        if (saldo < monto) {
            System.out.println("Fondos insuficientes");
        } else {
            saldo -= monto;
        }
    }

    public void mostrarInfo() {
        System.out.println("Titular: " + titular);
        System.out.println("Saldo: " + saldo);
        System.out.println("Cuenta: " + numeroCuenta);
    }
}

public class MainThree {

    public static void main(String[] args) {

        CuentaBancaria cuenta1 = new CuentaBancaria("Carlos", 12345.0, 1000);

        cuenta1.depositar(500);
        cuenta1.retirar(200);

        cuenta1.mostrarInfo();
    }
}