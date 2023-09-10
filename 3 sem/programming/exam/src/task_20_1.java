import javax.swing.*;
import javax.swing.Timer;
import java.awt.*;

/* Вариант 24
 В окне апплета по горизонтали двигается окружность, отражаясь от границ апплета.
Да не просто отражается, а происходит упругое столкновение. */


public class task_20_1 extends JFrame {

    static final int CX = 600, CY = 500;
    int x,y;
    final int speed = 5;
    Timer  t;
    Color c = Color.GREEN;
    boolean toRight = true;
    int dx = 0;

    public task_20_1 () {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(CX, CY);
        x=0;
        y = CY/2;
        t = new Timer(50, e -> doMove());
        t.start();
    }

    @Override
    public void paint(Graphics g) {
        g.clearRect(0,0,getWidth(),getHeight());
        if (dx != 0)
            g.setColor(Color.RED);
        else
            g.setColor(Color.BLACK);
        g.fillOval(x,y,100 - 4 * dx,100 - dx * 4);
        dx = 0;
    }
    void doMove () {
        if (x + 50 >= getWidth() - 50) {
            toRight = false;
            dx = 10;
        }
        if (x - 50 <= 0) {
            toRight = true;
            dx = 10;
        }
        if (toRight)
            x += 10;
        else
            x -= 10;
        repaint();
    }

    public static void main(String[] args) {
        new task_20_1().setVisible(true);
    }
}