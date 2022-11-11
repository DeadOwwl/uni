package L5;

import java.util.*;
import java.util.function.Consumer;

public class Trapezium extends Figure implements Comparable<Trapezium>, Iterator<Object> {
	private int iter = 0;
	//angles
	private Point A;
	private Point B;
	private Point C;
	private Point D;
	//sides
	private double AB;
	private double BC;
	private double CD;
	private double DA;
	//angles
	private double DAB;
	private double ABC;
	private double BCD;
	private double CDA;
	//colors
	public String fillColor;
	public String circuitColor;
	
	public double GetAB(){
		return this.AB;
	}
	
	public double GetBC(){
		return this.AB;
	}
	
	public double GetCD(){
		return this.AB;
	}
	
	public double GetDA(){
		return this.AB;
	}
	
	public double GetABC(){
		return this.ABC;
	}
	
	public double GetBCA(){
		return this.BCD;
	}
	
	public double GetCDA(){
		return this.CDA;
	}
	
	public double GetDAB(){
		return this.DAB;
	}
	
	public void SetFillColor(String col){
		fillColor = col;
	}

	public void SetCircuitColor(String col){
		circuitColor = col;
	}
	
 	public Trapezium(Point a, Point b, Point c, Point d)throws Exception{
		this.A = a;
		this.B = b;
		this.C = c;
		this.D = d;
		
		IsTrapezium(this);
		
		this.AB = Point.Distance(a, b);
		this.BC = Point.Distance(b, c);
		this.CD = Point.Distance(c, d);
		this.DA = Point.Distance(d, a);
		
		this.DAB = Math.acos(Math.abs((this.A.GetX() * this.A.GetY() + this.B.GetX() * this.B.GetY()) / 
				(Math.sqrt(Math.pow(this.A.GetX(), 2) + Math.pow(this.B.GetX(), 2))) * 
				Math.sqrt(Math.pow(this.A.GetY(), 2) + Math.pow(this.B.GetY(), 2))));
		this.ABC = Math.acos(Math.abs((this.B.GetX() * this.B.GetY() + this.C.GetX() * this.C.GetY()) / 
				(Math.sqrt(Math.pow(this.B.GetX(), 2) + Math.pow(this.C.GetX(), 2))) * 
				Math.sqrt(Math.pow(this.B.GetY(), 2) + Math.pow(this.C.GetY(), 2))));
		this.BCD = Math.acos(Math.abs((this.C.GetX() * this.C.GetY() + this.D.GetX() * this.D.GetY()) / 
				(Math.sqrt(Math.pow(this.C.GetX(), 2) + Math.pow(this.D.GetX(), 2))) * 
				Math.sqrt(Math.pow(this.C.GetY(), 2) + Math.pow(this.D.GetY(), 2))));
		this.CDA = Math.acos(Math.abs((this.D.GetX() * this.D.GetY() + this.A.GetX() * this.A.GetY()) / 
				(Math.sqrt(Math.pow(this.D.GetX(), 2) + Math.pow(this.A.GetX(), 2))) * 
				Math.sqrt(Math.pow(this.D.GetY(), 2) + Math.pow(this.A.GetY(), 2))));
	}
	
	public static boolean IsTrapezium(Trapezium T)throws Exception{
		boolean fPar = Math.abs((T.A.GetX() * T.A.GetY() + T.C.GetX() * T.C.GetY()) / 
				(Math.sqrt(Math.pow(T.A.GetX(), 2) + Math.pow(T.C.GetX(), 2))) * 
				Math.sqrt(Math.pow(T.A.GetY(), 2) + Math.pow(T.C.GetY(), 2))) == 1 ? true : false;
		boolean sPar = fPar = Math.abs((T.B.GetX() * T.B.GetY() + T.D.GetX() * T.D.GetY()) / 
				(Math.sqrt(Math.pow(T.B.GetX(), 2) + Math.pow(T.D.GetX(), 2))) * 
				Math.sqrt(Math.pow(T.B.GetY(), 2) + Math.pow(T.D.GetY(), 2))) == 1 ? true : false;
		if (fPar != sPar)
			return true;
		else
			throw new Exception("Points isn't a trapezium.");
	}
	
    double Perimeter(){
        return (AB + BC + CD + DA);
    }

    double Area() {
        return (Math.abs(Math.pow(DA, 2) - Math.pow(BC, 2)) / 2 * Math.sin(DAB) * Math.sin(CDA) / Math.sin(DAB + CDA));
    }
    

	public boolean hasNext() {
		return (iter <= 12);
	}
	

	public Object next() {
		if (iter > 12)
            throw new IndexOutOfBoundsException("Outcome of borders.");
        switch (iter)
        {
            case 0:
                iter++;
                return A;
            case 1:
                iter++;
                return B;
            case 2:
                iter++;
                return C;   
            case 3:
                iter++;
                return D;
            case 4:
                iter++;
                return AB;
            case 5:
                iter++;
                return BC;
            case 6:
                iter++;
                return CD;
            case 7:
                iter++;
                return DA;
            case 8:
                iter++;
                return DAB;
            case 9:
                iter++;
                return ABC;
            case 10:
                iter++;
                return BCD;
            case 11:
                iter++;
                return CDA;
            default:
                return 0;
        }
	}


	
    static int sortMarker = 0;
    public void setMarker(int inMarker) {
        if((inMarker == 0) || (inMarker == 1)) {
            sortMarker = inMarker;
        }
    }
    
    public int compareTo(Trapezium t) {
    	switch (sortMarker) {
        case 0:
            if(Perimeter() > t.Perimeter()) {
                return 1;
            }
            else {
                if (Perimeter() < t.Perimeter()){
                    return -1;
                }
                else {
                    return 0;
                }
            }
        case 1:
            if(Area() > t.Area()) {
                return 1;
            }
            else {
                if (Area() < t.Area()){
                    return -1;
                }
                else{
                    return 0;
                }
            }
        default: 
        	return -1;
    	}
	}
   
    public void remove() {
        //
  }
    
    public static Comparator<Trapezium> getComparator(int sortBy) {
        if ( sortBy >= 2 || sortBy < 0 ) {
            throw new IndexOutOfBoundsException();
        }
    	return new Comparator<Trapezium> () {
			public int compare(Trapezium c0, Trapezium c1) {
		        return c0.compareTo( c1);
			}
    	};
    }
    
    
    
    
    
    
}
