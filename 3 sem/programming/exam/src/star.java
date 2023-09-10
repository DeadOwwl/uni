import javax.swing.*;
import java.awt.*;

class Star extends JFrame{
    static final int CX = 600, CY = 600;
    int counts = 5;
    Color bgColor = Color.blue;
    Color startColor = Color.yellow;
    int radius = 100;
    int smallradius = radius / 2;
    int xPos = 300;
    int yPos = 300;
    int [] xArr = new int[counts * 2];
    int [] yArr = new int[counts * 2];
    double startAngle = 0;
    Timer t;

    int step = 5;
    public Star(){
        setSize(CX, CY);
        createStar(xArr, yArr, counts);
        t = new Timer(50, e -> doMove());
        t.start();
    }

    public void createStar(int [] xArr, int [] yArr, int counts){

        double part = 360 * 1.0 / (counts * 2);

        for (int i = 0 ; i < counts * 2; i++){
            if (i % 2 == 0){
                xArr[i] = xPos + (int)(Math.cos(Math.toRadians(i * part + startAngle)) * radius);
                yArr[i] = yPos + (int)(Math.sin(Math.toRadians(i * part + startAngle)) * radius);
            }
            else{
                xArr[i] = xPos + (int)(Math.cos(Math.toRadians(i * part + startAngle)) * smallradius);
                yArr[i] = yPos + (int)(Math.sin(Math.toRadians(i * part + startAngle)) * smallradius);
            }
        }

    }

    public void doMove() {
        startAngle += step;
        if (startAngle % 360 == 0)
            startAngle = 0;

        createStar(xArr,yArr,counts);
        repaint();
    }

    public void paint(Graphics gr){
        gr.setColor(bgColor);
        gr.fillRect(0,0,this.getWidth(),this.getHeight());
        gr.setColor(startColor);
        gr.fillPolygon(xArr,yArr,counts * 2);
    }

    public static void main(String[]args){
        Star s = new Star();
        s.setVisible(true);
    }
}

