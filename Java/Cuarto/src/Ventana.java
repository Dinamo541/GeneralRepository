import javax.swing.*;

public class Ventana {

    private JFrame frame = null;

    public Ventana() {
        frame = new JFrame("Ventana inutil");

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    
        frame.setSize(400, 200);
    
        frame.setLocationRelativeTo(null);
    
        frame.getContentPane().add(new JLabel("Hola mundo, esta es una ventana que no hace nada", SwingConstants.CENTER));
    
        frame.setVisible(true);
    }

    public void run(String[] args) {
        SwingUtilities.invokeLater(() -> {
            frame.setVisible(true);
        });

    }
}