import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

class Frame extends JFrame {
    public static class lineSegment implements Shape {
        @Override
        public Rectangle getBounds() {
            return null;
        }
        @Override
        public Rectangle2D getBounds2D() {
            return null;
        }
        @Override
        public boolean contains(double x, double y) {
            return false;
        }
        @Override
        public boolean contains(Point2D p) {
            return false;
        }
        @Override
        public boolean intersects(double x, double y, double w, double h) {
            return false;
        }
        @Override
        public boolean intersects(Rectangle2D r) {
            return false;
        }
        @Override
        public boolean contains(double x, double y, double w, double h) {
            return false;
        }
        @Override
        public boolean contains(Rectangle2D r) {
            return false;
        }
        @Override
        public PathIterator getPathIterator(AffineTransform at) {
            return null;
        }
        @Override
        public PathIterator getPathIterator(AffineTransform at, double flatness) {
            return null;
        }

        Shape[] linePoint;
        public lineSegment() {
            linePoint = new Shape[]{new Line2D.Double(200, 300, 350, 300),
                    new Ellipse2D.Double(194, 294, 12, 12)};
        }
        void pointMove(double delta) {
            linePoint[1] = new Ellipse2D.Double(194 + delta, 294, 12, 12);
        }
    }

    public lineSegment lp = new lineSegment();
    public Frame() {
        setSize(Toolkit.getDefaultToolkit().getScreenSize().width / 2,
                Toolkit.getDefaultToolkit().getScreenSize().width / 2);
        setBackground(Color.black);
        setDefaultCloseOperation(EXIT_ON_CLOSE);
    }
    @Override
    public void paint(Graphics g) {
        Graphics2D g2d = (Graphics2D) g;
        int thickness;
        Color firstColor;
        Color secondColor;
        if (argsFlag){
            thickness = argsT[0];
            firstColor = new Color(argsT[1], argsT[2], argsT[3]);
            secondColor = new Color(argsT[4], argsT[5], argsT[6]);
        }
        else{
            thickness = 2;
            firstColor = new Color(0, 255, 239);
            secondColor = new Color(188, 0, 84);
        }
        g.clearRect(0, 0, getWidth(), getHeight());
        AffineTransform at = AffineTransform.getRotateInstance(Math.PI / 30 * ang,
                lp.linePoint[1].getBounds().getX() + 150,
                lp.linePoint[1].getBounds().getY() + 150);
        g2d.setTransform(at);
        g2d.setStroke(new BasicStroke(thickness));
        g2d.setColor(firstColor);
        g2d.draw(lp.linePoint[0]);
        g2d.draw(lp.linePoint[1]);
        g2d.setColor(secondColor);
        g2d.fill(lp.linePoint[1]);
        try {
            repaint();
            Thread.sleep(75);
        } catch (Exception ignored) { }

        try { mov();}
        catch (InterruptedException e) { e.printStackTrace();}
    }

    double ang = 0;
    boolean rotation = true;
    public void mov() throws InterruptedException {
        if (rotation) ang++;
        else ang--;
        if (ang > 150) {
            rotation = false;
            Thread.sleep(500);
        }
        if (ang <= 0) {
            rotation = true;
            Thread.sleep(500);
        }
        lp.pointMove(ang);
    }

    static boolean argsFlag = false;
    public static int[] checkArgs(String[] args) {
        if (args.length == 0)
            argsFlag = false;
        else {
            if (args.length != 7) {
                System.out.println("Invalid number of arguments. Example: 1 255 255 255 0 0 0,\n" +
                        "where first two triples of numbers are two RGB colors, the last one is thickness of pen.");
                System.exit(1);
            }
            for (int i = 1; i < 7; i++)
                if (Integer.parseInt(args[i]) > 255) {
                    System.out.println("Invalid number of arguments. Example: 1 255 255 255 0 0 0,\n" +
                            "where first two triples of numbers are two RGB colors, the last one is thickness of pen.");
                    System.exit(1);
                }
            if (Integer.parseInt(args[0]) < 0) {
                System.out.println("Invalid argument type. Example: 255 255 255 0 0 0 1.");
                System.exit(1);
            }
            argsFlag = true;
        }
        if (argsFlag)
            return new int[]{Integer.parseInt(args[0]), Integer.parseInt(args[1]), Integer.parseInt(args[2]),
                    Integer.parseInt(args[3]), Integer.parseInt(args[4]), Integer.parseInt(args[5]),
                    Integer.parseInt(args[6])};
        else
            return new int[]{0};
    }

    static int[] argsT;
    public static void main(String[] args) {
        argsT = checkArgs(args);
        new Frame().setVisible(true);
    }
}
