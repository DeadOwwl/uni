package task;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.*;

class WitchOfAgnesi implements Shape {
    private final int param;
    private final double startAngle = 0.01;
    private final double endAngle = startAngle + Math.PI - 2 * 0.01;
    private final float centerX;
    private float centerY ;

    public WitchOfAgnesi(int param, int centerX, int centerY) {
        this.param = param;
        this.centerX = centerX;
        this.centerY = centerY;
    }

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
        return new PlotIterator(at);
    }

    @Override
    public PathIterator getPathIterator(AffineTransform at, double flatness) {
        return new PlotIterator(at, flatness);
    }


    class PlotIterator implements PathIterator {
        AffineTransform transform;
        double flatness;
        double angle = startAngle;
        double step = 10;
        boolean done = false;

        public PlotIterator(AffineTransform transform, double flatness) {
            this.transform = transform;
            this.flatness = flatness;
        }

        public PlotIterator(AffineTransform transform) {
            this.transform = transform;
            this.flatness = 0;
        }

        @Override
        public int getWindingRule() {
            return WIND_NON_ZERO;
        }

        @Override
        public boolean isDone() {
            return done;
        }

        @Override
        public void next() {
            if (done) return;
            if (flatness == 0) step = 0.05;
            else step = 0;
            angle += step;
            if (angle > endAngle) done = true;
        }

        @Override
        public int currentSegment(float[] coords) {
            coords[0] = (float) (param * Math.tan(angle)) + centerX;
            coords[1] = -(float) (param * Math.pow(Math.cos(angle), 2)) + centerY;
            if (angle > endAngle) done = true;
            if (angle == startAngle) return SEG_MOVETO;
            else return SEG_LINETO;
        }

        @Override
        public int currentSegment(double[] coords) {
            coords[0] = (float) (param * Math.tan(angle)) + centerX;
            coords[1] = -(float) (param * Math.pow(Math.cos(angle), 2)) + centerY;
            if (angle > endAngle) done = true;
            if (angle == startAngle) return SEG_MOVETO;
            else return SEG_LINETO;
        }
    }
}

class MyStroke implements Stroke {
    private BasicStroke stroke;

    public MyStroke(float amplitude) {
        this.stroke = new BasicStroke(amplitude);
    }

    public Shape createStrokedShape(Shape shape) {
        GeneralPath result = new GeneralPath();
        PathIterator it = new FlatteningPathIterator(shape.getPathIterator(null), 1);
        float points[] = new float[2];
        float moveX = 0, moveY = 0;
        float lastX = 0, lastY = 0;
        float thisX = 0, thisY = 0;
        int type = 0;
        float next = 0;
        int phase = 0;

        while (!it.isDone()) {
            type = it.currentSegment(points);
            switch (type) {
                case PathIterator.SEG_MOVETO:
                    moveX = lastX = points[0];
                    moveY = lastY = points[1];
                    result.moveTo(moveX, moveY);
                    next = 5;
                    break;

                case PathIterator.SEG_CLOSE:
                    points[0] = moveX;
                    points[1] = moveY;
                case PathIterator.SEG_LINETO:
                    thisX = points[0];
                    thisY = points[1];
                    float dx = thisX - lastX;
                    float dy = thisY - lastY;
                    float distance = (float) Math.sqrt(dx * dx + dy * dy);
                    if (distance >= next) {
                        float r = 1.0f / distance;
                        while (distance >= next) {
                            float x = lastX + next * dx * r;
                            float y = lastY + next * dy * r;
                            if ((phase % 3) == 1)
                                result.lineTo(x + 5 * dy * r, y - 5 * dx * r);
                            else
                                result.lineTo(x,y);
                            next += 5;
                            phase++;
                        }
                    }
                    next -= distance;
                    lastX = thisX;
                    lastY = thisY;
                    if (type == PathIterator.SEG_CLOSE) {
                        result.closePath();
                    }
                    break;
            }
            it.next();
        }
        return stroke.createStrokedShape(result);
    }
}

public class Test extends JFrame {

    WitchOfAgnesi witchOfAgnesi;

    class WOA extends JComponent{
        public void paintComponent(Graphics g){
            Graphics2D g1 = (Graphics2D) g;
            g.setColor(Color.black);
            g.fillRect(0, 0, getWidth(), getHeight());
            MyStroke stroke = new MyStroke(2f);
            g1.setColor(new Color(0, 120, 95));
            g1.draw(stroke.createStrokedShape(witchOfAgnesi));
        }
    }

    public Test(WitchOfAgnesi woa){
        super("Task ¹3, variant ¹13 (dead.owwl)");
        this.setBounds(0, 0, 640, 480);
        setLayout(new BorderLayout());
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        witchOfAgnesi = woa;
        WOA sn = new WOA();
        add(sn);
    }

    public static void main(String [] args){
        WitchOfAgnesi woa = new WitchOfAgnesi(100, 320, 360);
        Frame frame = new Test(woa);
        frame.setVisible(true);
    }
}