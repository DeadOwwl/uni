//Вариант 22.
//        Задача с параболой - одна из лабораторных по апплетам Y = X^2-1
//        X[-1,2] dx=0.05


import javax.swing.*;
import java.awt.*;

class Points {
    int centerX;
    int centerY;
    double x;
    double y;
    int conclX;
    int conclY;

    public Points(int centerX, int centerY, double x, double y){
        this.centerX = centerX;
        this.centerY = centerY;
        this.x = x;
        this.y = y;
        conclX = this.centerX + (int)(this.x*75);
        conclY = this.centerY - (int)(this.y*75);
    }

    public Points (Points p){
        conclX = p.conclX;
        conclY = p.conclY;
    }

    public int p_x(){
        return conclX;
    }

    public int p_y(){
        return conclY;
    }
}

class Draw_Graph extends Canvas{
    final static int centerX = (task_22.Size_win_X / 2),
            centerY = (task_22.Size_win_Y / 2);
    Color graph;
    Color deck;
    Dimension dim = new Dimension(task_22.Size_win_X, task_22.Size_win_Y);

    public Draw_Graph(Color graph, Color deck){
        this.graph = graph;
        this.deck = deck;
        setBounds(0, 0, dim.width, dim.height);
    }

    public void paint(Graphics g){
        g.setColor(graph);
        graph_x_x(g);
        g.setColor(deck);
        deck_graph(g);
    }

    public double func(double x){
        return (Math.pow(x, 2) - 1);
    }

    void deck_graph(Graphics g){
        g.drawLine(0, centerY, task_22.Size_win_X, centerY);
        g.drawLine(centerX, 0, centerX, task_22.Size_win_Y);

        g.drawLine(175, 255, 175, 245);
        g.drawLine(400, 255, 400, 245);
        g.drawLine(325, 255, 325, 245);

        g.drawLine(255, 175, 245, 175);
        g.drawLine(255, 325, 245, 325);
        g.drawLine(255, 100, 245, 100);
        g.drawLine(255, 25, 245, 25);

        g.drawString("0", 253, 262);
        g.drawString("-1", 176, 262);
        g.drawString("1", 326, 262);
        g.drawString("2", 401, 262);

        g.drawString("3", 257, 25);
        g.drawString("2", 257, 100);
        g.drawString("1", 257, 175);
        g.drawString("-1", 257, 334);

    }

    void graph_x_x(Graphics g){
        double x = -1;
        double dx = 0.05;
        Points p1, p2;
        p1 = new Points(centerX, centerY, x, func(x));
        while(x<=2)
        {
            p2 = new Points(p1);
            x += dx;
            p1 = new Points(centerX, centerY, x, func(x));
            g.drawLine(p2.conclX, p2.conclY, p1.conclX, p1.conclY);
        }
    }
}

public class task_22 extends JFrame {
    static final int Size_win_X = 500, Size_win_Y = 500;
    Canvas obj;

    public task_22(){
        setSize(Size_win_X, Size_win_Y);
        Color deck = new Color(0, 0, 0);
        Color graph = new Color(0, 250, 0);
        obj = new Draw_Graph(graph, deck);
        add(obj);
    }

    public static void main(String[] args) {
        task_22 t = new task_22();
        t.setVisible(true);
        t.repaint();
    }
}