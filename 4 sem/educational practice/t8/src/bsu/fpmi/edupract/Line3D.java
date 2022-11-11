package bsu.fpmi.edupract;

import java.awt.*;

public class Line3D extends Canvas{
	private int lineHeight;
        private final int lineWidth = 15;
	private Color strokeColor;
	private Color fillColor;

	public Line3D() {
	    strokeColor = Color.black;
	    fillColor = Color.green;
	    this.lineHeight = 400;
	}

	public Line3D(int height) { 
            this.lineHeight = height; 
        }

	@Override
	public void paint(Graphics g1) {
		int startY = getHeight() / 2 - lineHeight / 2, endY = getHeight() / 2 + lineHeight / 2;
		int x = getWidth()/2 - lineWidth / 2;

		Graphics2D g = (Graphics2D)g1;
		g.setColor(fillColor);
		g.fillRect(x , startY - lineHeight / 4,lineWidth, endY-startY );
		g.fillArc(x,endY - lineHeight / 3,lineWidth, lineHeight / 8,180,180);
		g.fillOval(x,startY- lineHeight /3,lineWidth, lineHeight /8);

		g.setColor(strokeColor);
		g.drawOval(x,startY - lineHeight / 3,lineWidth, lineHeight /8);
		g.drawArc(x,endY- lineHeight /3,lineWidth, lineHeight /8,180,180);

		g.drawLine(x,startY- lineHeight /4,x,endY- lineHeight /4);
		g.drawLine(x + lineWidth,startY- lineHeight /4,x + lineWidth,endY- lineHeight /4);

		for (int i = startY; i < endY ; i+=lineHeight/ 4)
			g.drawArc(x,i - lineHeight / 3,lineWidth, lineHeight / 8, 180, 180);

		Stroke dashed = new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_BEVEL,
				0, new float[]{3}, 0);
		g.setStroke(dashed);

		for (int i = startY; i < endY ; i+=lineHeight/4)
			g.drawArc(x,i - lineHeight / 3,lineWidth, lineHeight / 8, 0, 180);

		g.drawArc(x,endY- lineHeight /3,lineWidth, lineHeight /8,0,180);
	}

	public void setLineHeight(int heignt) { this.lineHeight = heignt;}
        

	public int getLineHeight() { return this.lineHeight;}
}