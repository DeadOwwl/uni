package L4;

import java.util.Random;
import java.util.Date;

class boolVector {
    int n = 0;
    boolean [] vectors = null;

    public boolVector() {
        n = 0;
        vectors = null;
    }
    
    public boolVector( int userN ) {
    	//assert( userN > 0 );
    	n = userN;
    	vectors = new boolean [userN];
        Random myRand = new Random( (new Date()).getTime() );
        for( int i = 0; i < userN; i++ ) { 
           vectors[i] = (myRand.nextInt(2) == 0 ? false : true);
        }
    }
    
    public boolVector( int userN, boolean[] userVectors) {
    	//assert( userN > 0 );
    	n = userN;
    	vectors = new boolean [userN];
    	for (int i = 0; i < userN; i++){
    		vectors[i] = userVectors[i];
    	}
    }
    
    public boolVector Conjunction(boolVector secondBoolVector){
    	//assert(this.n == secondBoolVector.n);
    	boolVector finalBoolVector = new boolVector(this.n);
    	for (int i = 0; i < this.n; i++)
    	{
    		finalBoolVector.vectors[i] = this.vectors[i] & secondBoolVector.vectors[i];
    	}
    	
    	return finalBoolVector;
    }
    
    public boolVector Disjunction(boolVector secondBoolVector){
    	//assert(this.n == secondBoolVector.n);
    	boolVector finalBoolVector = new boolVector(this.n);
    	for (int i = 0; i < this.n; i++)
    	{
    		finalBoolVector.vectors[i] = this.vectors[i] | secondBoolVector.vectors[i];
    	}
    	return finalBoolVector;
    }
    
    public boolVector Negation(){
    	for (int i = 0; i < this.n; i++)
    	{
    		this.vectors[i] = (this.vectors[i] == false ? true : false);
    	}
    	return this;
    }
    
    public int[] ElementsNumber(){
    	int elementsNumber[] = new int[2];
    	for (int i = 0; i < this.n; i++)
    	{
    		if (this.vectors[i] == false)
    			elementsNumber[0]++;
    		else
    			elementsNumber[1]++;
    	}
    	return elementsNumber;
    }
    
    public void Print(){
    	for (int i = 0; i < this.n; i++)
    	{
    		if (this.vectors[i] == false)
    			System.out.print("0");
    		else
    			System.out.print("1");
    	}
    }
}
