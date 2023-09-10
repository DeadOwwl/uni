import javax.swing.*;
import java.applet.Applet;
import java.awt.*;


public class task_23 extends JFrame {

    public static void main(String[] args) {
        new task_23().setVisible(true);
    }

    private static final long serialVersionUID = 1L;

    static final int CX = 400, CY = 400;
    static String str = "Odin";
    static int pose1 = 10;
    static int pose2 = 10;
    static int pose3 = 10;
    static int pose4 = 10;
    static int next =0;
    static String our="";
    static int point=0;
    static char cur1=str.charAt(point);
    static char cur2=str.charAt(++point);
    static char cur3=str.charAt(++point);
    static char cur4=str.charAt(++point);
    Timer t;
    boolean stFlag  = false;
    public task_23()
    {
        setDefaultCloseOperation(EXIT_ON_CLOSE);
        setSize( CX, CY );
        setLayout( null );
        Color col = new Color(9, 154, 125);
        setBackground( col );
        Color colx = new Color(226, 226, 226);
        col = Color.WHITE;
        t = new Timer(100,e -> doMove());
        t.start();

    }
    public void paint(Graphics g)
    {
        g.clearRect(0,0,getWidth(),getHeight());
        g.drawString(cur1+" ",pose1,pose1);
        g.drawString(cur2+" ",400-pose2,pose2);
        g.drawString(cur3+" ",400-pose3,400-pose3);
        g.drawString(cur4+" ",pose4,400-pose4);
        g.drawString(our,100,200);

    }

    public void doMove()
    {
        if(next==0)
        {
            pose1+=10;
            repaint();
            if(pose1==200)
            {
                pose1=10;
                next+=1;
                our+=cur1;
                point++;
                if(point>=str.length())
                {
                    cur1=' ';
                }
                else
                {
                    cur1=str.charAt(point);
                }
                if ( cur1 == ' ' && cur2 == ' ' &&cur3 == ' ' && cur4 == ' ')
                {
                    stFlag = true;
                }

            }
        }
        else if(next==1)
        {
            pose2+=10;
            repaint();
            if(pose2==200)
            {
                pose2=10;
                next+=1;
                our+=cur2;
                point++;
                if(point>=str.length())
                {
                    cur2=' ';
                }
                else
                {
                    cur2=str.charAt(point);
                }
                if ( cur1 == ' ' && cur2 == ' ' &&cur3 == ' ' && cur4 == ' ')
                {
                    stFlag = true;
                }
            }
        }
        else if(next==2)
        {
            pose3+=10;
            repaint();
            if(pose3==200)
            {
                pose3=10;
                next+=1;
                our+=cur3;
                point++;
                if(point>=str.length())
                {
                    cur3=' ';
                }
                else
                {
                    cur3=str.charAt(point);
                }
                if ( cur1 == ' ' && cur2 == ' ' &&cur3 == ' ' && cur4 == ' ')
                {
                    stFlag = true;
                }
            }
        }
        else
        {
            pose4+=10;
            repaint();
            if(pose4==200)
            {
                pose4=10;
                next=0;
                our+=cur4;
                point++;
                if(point>=str.length())
                {
                    cur4=' ';
                }
                else
                {
                    cur4=str.charAt(point);
                }
                if ( cur1 == ' ' && cur2 == ' ' &&cur3 == ' ' && cur4 == ' ')
                {
                    stFlag = true;
                }
            }
        }

    }

}