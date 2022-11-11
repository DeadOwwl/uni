package L5again;

import java.util.Arrays;

public class Test {
	
    static void sortAndPrint(Trapezium[] T, int sortBy )  {
    	System.out.println( "-Sorted by: " + Trapezium.getSortByName(sortBy));
    Arrays.sort( T, Trapezium.getComparator(sortBy));
    System.out.printf( Trapezium.format() );
    System.out.println();
    for (Trapezium tIt : T)
    	System.out.println(Trapezium.format(tIt));
    
}
	
	public static void main(String[] args){
	    try {
	    	Trapezium[] figures = new Trapezium[4];
		    Point A1 = new Point(0, 0);
		    Point B1 = new Point(0, 4);
		    Point C1 = new Point(4, 4);
		    Point D1 = new Point(6, 0);
		    figures[0] = new Trapezium(A1, B1, C1, D1, "black", "blue");
		    System.out.println(figures[0].toString());
		    
		    Point A2 = new Point(0, 0);
		    Point B2 = new Point(0, 10);
		    Point C2 = new Point(4, 10);
		    Point D2 = new Point(15, 0);
		    figures[1] = new Trapezium(A2, B2, C2, D2, "white", "green");
		    System.out.println(figures[1].toString());
		    
		    figures[2] = new Trapezium("4 7 5 10 pink blue");
		    System.out.println(figures[2].toString());
		
		    figures[3] = new Trapezium("5 9 5 17 gray purple");
		    System.out.println(figures[3].toString());
		    
		    // D E M O 
		    
		    sortAndPrint(figures, 0);
		    sortAndPrint(figures, 1);
		    sortAndPrint(figures, 2);
		    sortAndPrint(figures, 3);
		    
		    figures[4] = new Trapezium("-9 9 5 17 gray green");
		
		} catch (Exception e) {
			System.out.println( "Exception: " + e );
		}
	}
}
