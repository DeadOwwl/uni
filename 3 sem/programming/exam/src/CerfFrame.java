import javax.swing.*;
import java.awt.*;

public class CerfFrame extends JFrame {

    int angle =0;
    Timer t;
    public CerfFrame(){
        super();
        setSize(500,500);
        t = new Timer(100, e-> {
            if (angle >= 360)
                angle = 0;
            angle += 6;
            repaint();
        });
        t.start();
    }

    @Override
    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D)g;
        g2d.rotate(Math.toRadians(angle),150,200);
        g2d.clearRect(0,0,getWidth(),getHeight());
        g2d.drawLine(100,100,100,300);
        g2d.drawLine(100,300,200,300);
        g2d.drawLine(200,300,100,100);
    }

    public static void main(String[] args) {
        new CerfFrame().setVisible(true);
    }
}
