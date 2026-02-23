import javax.swing.*;
import java.awt.*;

// 👇 Panel personalizado con fondo escalable
class FondoPanel extends JPanel {

    private Image fondo;

    public FondoPanel(String rutaImagen) {
        fondo = new ImageIcon(rutaImagen).getImage();
    }

    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);

        // dibuja la imagen ajustándola al tamaño del panel
        g.drawImage(fondo, 0, 0, getWidth(), getHeight(), this);
    }
}

public class MainFour {

    public static void main(String[] args) {

        JFrame frame = new JFrame("Fondo escalable");
        frame.setSize(800, 500);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);

        // Panel con imagen de fondo
        // ejemplo de componente encima del fondo
        JLabel texto = new JLabel("Hola mundo");
        texto.setFont(new Font("Arial", Font.BOLD, 40));
        texto.setForeground(Color.WHITE);

        FondoPanel fondo = new FondoPanel("java/Cuarto/img/gbmframes_000.png");
        fondo.setLayout(new GridBagLayout()); // centra elementos
        fondo.add(texto);

        // usamos el panel como contenido
        frame.setContentPane(fondo);
        frame.setVisible(true);
    }
}