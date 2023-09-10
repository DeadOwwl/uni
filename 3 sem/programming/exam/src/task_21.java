import javax.swing.*;
import java.awt.*;
import java.awt.Graphics;
import java.util.function.Function;

/* ������� 21
 * ���������� � ���� ������� ������������� ��������� ����� ����� ����������
 * ��������������� �������. ���� ����� ������� ����� q, �� ���������� �� ����� �� ������
 * ����� � ������ ������� t ����� ������� ������ q(1+cos(wt))/2,��� w - ��������� ���������.
 * ��������� �������� �������� ����� ��������� �������.
 */

public class task_21 extends JFrame {

    final int CX = 600, CY = 500;
    Timer timer;
    final int q = 350, w = 7;
    int x, t;
    Function<Integer,Integer> func = (t) -> (int)(0.5 * q * (1 + Math.cos(1.0 * w * t)));

    public task_21 () {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        t=0;
        x=func.apply(t);
        setSize(CX, CY);
        timer = new Timer(100, e ->  doMove());
        timer.start();
    }

    @Override
    public void paint(Graphics g) {
        g.clearRect(0,0,getWidth(),getHeight());
        g.setColor(Color.GREEN);
        g.drawLine(0,getHeight()/2,getWidth(),getHeight()/2);
        g.setColor(Color.BLACK);
        g.fillOval(t, x,10,10);
    }

    void doMove () {
        if (t>getHeight())
            t=0;
        t += 10;
        x = func.apply(t);
        repaint();
    }

    public static void main(String[] args) {
        new task_21().setVisible(true);
    }
}
