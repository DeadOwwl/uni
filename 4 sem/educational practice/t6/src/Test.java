import java.awt.*;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.geom.*;
import java.io.Serializable;

class WitchOfAgnesi implements Shape, Serializable, Cloneable, Transferable {
    private final int param;
    private final double startAngle = 0.01;
    private final double endAngle = startAngle + Math.PI - 2 * 0.01;
    private float centerX;
    private float centerY;

    public WitchOfAgnesi(int param, int centerX, int centerY) {
        this.param = param;
        this.centerX = centerX;
        this.centerY = centerY;
    }

    @Override
    public Rectangle getBounds() {
        return new Rectangle((int)(centerX - param), (int)(centerY - param), 2 * param, 2 * param);
    }

    @Override
    public Rectangle2D getBounds2D() {
        return new Rectangle.Float(centerX - param, centerY - param, 2 * param, 2 * param);
    }

    @Override
    public boolean contains(double x, double y) {
        // NOT NECESSARY
        double x1 = x - centerX;
        double y1 = centerY - y;
        return Math.pow(x1, (float) 2 / 3) + Math.pow(y1, (float) 2 / 3) <= Math.pow(param, (float) 2 / 3);
    }

    @Override
    public boolean contains(Point2D p) {
        return contains(p.getX(), p.getY());
    }

    @Override
    public boolean intersects(double x, double y, double w, double h) {
        return getBounds().intersects(x, y, w, h);
    }

    @Override
    public boolean intersects(Rectangle2D r) {
        return getBounds().contains(r.getX(), r.getY(), r.getWidth(), r.getHeight());
    }

    @Override
    public boolean contains(double x, double y, double w, double h) {
        // NOT NECESSARY
        return contains(x, y) && contains(x + w, y) && contains(x, y + h) &&     contains(x + w, y + h);
    }

    @Override
    public boolean contains(Rectangle2D r) {
        // NOT NECESSARY
        return contains(r.getX(), r.getY(), r.getWidth(), r.getHeight());
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
        double flatness ;
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
            if (done)
                return;
            if (flatness == 0)
                step = 0.05;
            else
                step = flatness;
            angle += step;
            if (angle >= endAngle)
                done = true;
        }

        @Override
        public int currentSegment(float[] cords) {
            cords[0] = (float) (param * Math.tan(angle)) + centerX;
            cords[1] = -(float) (param * Math.pow(Math.cos(angle), 2)) + centerY;
            if (angle >= endAngle) done = true;
            if (angle == startAngle) return SEG_MOVETO;
            else return SEG_LINETO;
        }

        @Override
        public int currentSegment(double[] cords) {
            cords[0] = (float) (param * Math.tan(angle)) + centerX;
            cords[1] = -(float) (param * Math.pow(Math.cos(angle), 2)) + centerY;
            if (angle >= endAngle) done = true;
            if (angle == startAngle) return SEG_MOVETO;
            else return SEG_LINETO;
        }
    }

    // ################### NEW PART FOR T6 ###################

    static DataFlavor decDataFlavor = new DataFlavor(WitchOfAgnesi.class, "Witch of Agnesi");
    private static final DataFlavor[] supportedFlavors = {decDataFlavor, DataFlavor.stringFlavor};

    @Override
    public DataFlavor[] getTransferDataFlavors() {
        return supportedFlavors.clone();
    }

    @Override
    public boolean isDataFlavorSupported(DataFlavor dataFlavor) {
        return (dataFlavor.equals(decDataFlavor) || dataFlavor.equals(DataFlavor.stringFlavor));
    }

    @Override
    public Object getTransferData(DataFlavor dataFlavor) throws UnsupportedFlavorException {
        if (dataFlavor.equals(decDataFlavor)) {
            return this;
        } else if (dataFlavor.equals(DataFlavor.stringFlavor)) {
            return toString();
        } else
            throw new UnsupportedFlavorException(dataFlavor);
    }

    @Override
    public Object clone() {
        try {
            return super.clone();
        } catch (CloneNotSupportedException e) {
            return this;
        }
    }

    @Override
    public String toString() {
        return param + " " + centerX + " " + centerY ;
    }

    static WitchOfAgnesi getFromString(String line) {
        String[] arr = line.split(" ");
        return new WitchOfAgnesi(Integer.parseInt(arr[0]), Integer.parseInt(arr[1]),
                Integer.parseInt(arr[2]));
    }

    void translate(int x, int y) {
        centerX += x;
        centerY += y;
    }
}

class MyStroke implements Stroke {
    private final BasicStroke stroke;

    public MyStroke(float amplitude) {
        this.stroke = new BasicStroke(amplitude);
    }

    public Shape createStrokedShape(Shape shape) {
        GeneralPath result = new GeneralPath();
        PathIterator it = new FlatteningPathIterator(shape.getPathIterator(null), 1);
        float[] points = new float[2];
        float moveX = 0, moveY = 0;
        float lastX = 0, lastY = 0;
        float thisX, thisY;
        int type;
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
