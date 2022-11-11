package L4;

public class test {
	static final int NUM = 6;
	
    public static void main(String[] args) {
        boolVector [] arrayOfBools = new boolVector[NUM];
        for ( int i = 0; i < NUM; i++ ) {
            System.out.print("Random boolean vector #" + (i + 1) + ": ");
            arrayOfBools[i] = new boolVector(5);
            arrayOfBools[i].Print();
            System.out.print("\n");
        }
        
        System.out.print("\n");
        arrayOfBools[0].Print();
        System.out.print(" ^ ");
        arrayOfBools[1].Print();
        System.out.print(" = ");
        arrayOfBools[0].Conjunction(arrayOfBools[1]).Print();
        System.out.print("\n\n");
        
        arrayOfBools[2].Print();
        System.out.print(" v ");
        arrayOfBools[3].Print();
        System.out.print(" = ");
        arrayOfBools[2].Disjunction(arrayOfBools[3]).Print();
        System.out.print("\n");
        
        System.out.print("_____\n");
        arrayOfBools[4].Print();
        System.out.print(" = ");
        arrayOfBools[4].Negation().Print();
        System.out.print("\n\n");
        
        System.out.print("The number of 0s and 1s in ");
        arrayOfBools[5].Print();
        System.out.print(" : ");
        System.out.print(arrayOfBools[5].ElementsNumber()[0] + " '0s' and " + arrayOfBools[5].ElementsNumber()[1] + " '1s'\n");
    }
}
