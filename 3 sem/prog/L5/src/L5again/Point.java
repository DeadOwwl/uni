package L5again;

public class Point {
	
	private double x;
	private double y;
	
	public Point(double userX, double userY){
		x = userX;
		y = userY;
	}
	
	public double GetX() {
		return this.x;
	}
	
	public double GetY() {
		return this.y;
	}
	
	public void SetX(double userX) {
		this.x = userX;
	}
	
	public void SetY(double userY) {
		this.y = userY;
	}
	
	public static double Distance(Point p1, Point p2){
		return (Math.sqrt(Math.pow((p1.x - p2.x), 2) + Math.pow((p1.y - p2.y), 2)));
	}
}
