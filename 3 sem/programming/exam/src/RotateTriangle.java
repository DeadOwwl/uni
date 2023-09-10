
import javax.swing.*;
import java.awt.*;

public class RotateTriangle extends JFrame{
    private static final long serialVersionUID = 1L;

    static final int CX = 600, CY = 600;
    static int counts = 3;
    static double xCentre = 300, yCentre = 300;
    static int[] masx = new int [3];
    static int[] masy = new int [3];
    int angle=0;
    Timer  t;
    int radius = 100;

    int step = 5;
    public RotateTriangle(){
        setSize(CX, CY);
        createTriangle(masx, masy, counts);
        t = new Timer(50, e -> doMove());
        t.start();
    }

    public void createTriangle(int [] xArr, int [] yArr, int counts){
        double part = 360 * 1.0 / (counts);
        for (int i = 0 ; i < counts; i++){
                xArr[i] = (int)xCentre + (int)(Math.cos(Math.toRadians(i * part + angle)) * radius);
                yArr[i] = (int)yCentre + (int)(Math.sin(Math.toRadians(i * part + angle)) * radius);
        }

    }

    public void doMove()
    {
        angle += step;
        if (angle % 360 == 0)
            angle = 0;

        createTriangle(masx,masy,counts);
        repaint();
    }

    public void paint(Graphics g) {
        g.clearRect(0,0,getWidth(),getHeight());
        g.drawPolygon(new Polygon(masx,masy,3));
    }

    public static void main(String[] args) {
        RotateTriangle rt = new RotateTriangle();
        rt.setVisible(true);
    }
}
