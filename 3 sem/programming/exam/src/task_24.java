import javax.swing.*;
import javax.swing.Timer;
import java.awt.*;
/* Вариант 24
   Создать апплет со строкой, которая движется горизонтально,
 * отражаясь от границ апплета и меняя при этом свой цвет на цвет.
 * Строка вводится через параметры апплета.
 */
public class task_24 extends JFrame {
    int winS = 600, winY = 600;
    int x, y;
    Timer t;
    int speed = 10;
    Color c;
    String line = "I HOPE I'LL DIE";
    Font font = new Font("Times New Roman", Font.BOLD, 30);
    boolean toRight = true;

    public task_24(){
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize(winS, winY);
        setBackground(Color.black);
        x = 0;
        y = winY / 2;
        t = new Timer(30, e -> doMove());
        t.start();
    }

    public void doMove(){
        if (toRight){
            x += speed;
            if (x + getFontMetrics(font).stringWidth(line) >= getWidth()) {
                c = Color.cyan;
                toRight = false;
            }
        }
        else {
            x -= speed;
            if (x <= 0) {
                c = Color.green;
                toRight = true;
            }
        }
        repaint();
    }

    public void paint(Graphics g){
        g.clearRect(0, 0, getWidth(), getHeight());
        g.setFont(font);
        g.setColor(c);
        g.drawString(line, x, y);
    }

    public static void main(String[] args) {
        new task_24().setVisible(true);
    }
}

//static final int CX = 600, CY = 500;
//    int x,y;
//    final int speed = 5;
//    Timer  t;
//    Color c = Color.GREEN;
//    String str;
//    Font font = new Font("Times New Roman", Font.BOLD, 30);
//    boolean toRight = true;
//
//    public task_24 () {
//        setDefaultCloseOperation(EXIT_ON_CLOSE);
//        setSize(CX, CY);
//        x=0;
//        y = CY/2;
//        str = "god help me";
//        t = new Timer(50, e -> doMove());
//        t.start();
//    }
//
//    @Override
//    public void paint(Graphics g) {
//        g.clearRect(0,0,getWidth(),getHeight());
//        g.setFont(font);
//        g.setColor(c);
//        g.drawString(str, x,y);
//    }
//
//    public void doMove () {
//        if ( toRight ) {
//            x+=speed;
//            if ( x >= (getWidth() - getFontMetrics(font).stringWidth(str))) {
//                c = Color.BLUE;
//                toRight = false;
//            }
//        }
//        else {
//            x-=speed;
//            if ( x <= 0 ) {
//                c = Color.pink;
//                toRight = true;
//            }
//        }
//        y = getHeight() / 2;
//        repaint();
//    }