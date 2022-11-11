import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.awt.geom.*;

import javax.swing.*;

class RoadSign implements Shape {
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

    private final Rectangle2D rectangle;
    private final Color colorRectangleAndInscription;

    public RoadSign(int x, int y, int w, int h, Color ri){
        rectangle = new Rectangle2D.Double(x, y, w, h);
        colorRectangleAndInscription = ri;
    }

    public void paint(Graphics2D gf){
        gf.setPaint(new GradientPaint((int)rectangle.getX(),(int)rectangle.getY() + 150,new Color(50, 50, 50),
                (int)rectangle.getX(),(int)rectangle.getY(),new Color(150, 150, 150)));
        gf.fillRect((int)rectangle.getX(),(int)rectangle.getY(),200,150);
        gf.setColor(colorRectangleAndInscription);
        gf.draw(rectangle);
        Font font = new Font("Century", Font.BOLD, 40);
        gf.setFont(font);
        FontMetrics f = gf.getFontMetrics(font);
        gf.drawString("STOP", (int) (rectangle.getX() + 1.5 * f.charWidth('S')),
                (int) (rectangle.getY() + f.getHeight() * 1.8));
    }
}

class Frame extends JFrame {
    public static final int width = 200;
    public static final int height = 150;

    public static void main(String[] Args) {
        JFrame fr = new JFrame();
        fr.setPreferredSize(new Dimension(750, 400));
        final JPanel pan = new JPanel();
        fr.add(pan);
        fr.setVisible(true);
        fr.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        fr.pack();

        int X = 20, Y = 20;
        RoadSign roadsign;

        Graphics2D g2d = (Graphics2D) pan.getRootPane().getGraphics();
        GeneralPath path = new GeneralPath();
        Rectangle R = new Rectangle(0,0,750,500);
        path.append(R, true);
        g2d.setPaint(Color.white);
        g2d.fill(path);
        g2d.setStroke(new BasicStroke(7));
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

        roadsign = new RoadSign(X, Y, width, height, Color.red);
        AffineTransform save = g2d.getTransform();
        g2d.setPaint(new Color(0, 0, 0, 75));
        g2d.translate(75, 75);
        AffineTransform shadow = AffineTransform.getShearInstance(-1, 0.0);
        shadow.scale(1.0, 0.5);
        g2d.fill(shadow.createTransformedShape(new Rectangle2D.Double(X+20, Y+20, width, height)));
        g2d.setTransform(save);
        roadsign.paint(g2d);

        g2d.setTransform(save);
        g2d.translate(100, 0);
        AffineTransform rotate = AffineTransform.getRotateInstance(Math.PI / 4,100,250);
        AffineTransformOp filter = new AffineTransformOp(rotate, AffineTransformOp.TYPE_BILINEAR);
        BufferedImage bimage = new BufferedImage(width + X + 70, height + Y, BufferedImage.TYPE_INT_ARGB);
        Graphics2D img = bimage.createGraphics();

        img.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        img.setStroke(new BasicStroke(7));
        AffineTransform save1 = img.getTransform();
        img.setPaint(new Color(0, 0, 0, 75));
        img.translate(75, 75);
        img.fill(shadow.createTransformedShape(new Rectangle2D.Double(X, Y, width, height)));
        roadsign = new RoadSign(10, 10, width, height, Color.red);

        img.setTransform(save1);
        roadsign.paint(img);
        g2d.drawImage(filter.filter(bimage, null), 200, 5, null);
    }
}