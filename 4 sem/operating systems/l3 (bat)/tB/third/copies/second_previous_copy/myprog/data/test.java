public class test{

	public static void main(string[] args){
		Square square = new Square();
		System.out.println(square);
		square.move(-5, 1);
		System.out.println(square);
		}
		
		
	}



abstract class Figure {
	private String color;
	private int x;
	private int y;
	public Figure(String color, int x, int y){
	this.color = color;
	this.y = y;
	this.x = x;
	}

	public Figure(){
		this.color = "White";	
		this.x = this.y = 0;
	}

	public String getColor(){
		return color;
	}

	public void setColor(String color){
	this.color = color;
	}

	public void getX(int x){
		this.x = x;
	}
	
	public void getX(int y){
		this.y = y;
	}

	public void move(int x, int y){
		this.x += x;
		this.y += y;
	}

	public abstract double getArea();

	public abstract String boundingRect();

	public String toString(){
		return getColor() + " " + bondingRect() + " " + getArea();
		}
	}

class Square extends Figure {
	private int a;

	public Square(int a, String color){
		super(color, 0, 0);	
		this.a = a;
	}

	public Square() {
		super();
		this.a = 1;	
	}

	public double getArea() {
		return a * a;
	}

	public String boundingRect() {
		return getX() + " " + (getX() + this.a + " " + (getY() + this.a);	
	}

	public String toString() {
	return "square" + " " +super.toString();	
	}

}

}