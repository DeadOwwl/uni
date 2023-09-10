package loman;

import java.util.ArrayList;

public class loman implements Comparable<loman>{
    int line;
    double length;
    ArrayList<Double> xCoord;
    ArrayList<Double> yCoord;

    public loman(ArrayList<Double>x, ArrayList<Double> y, int l) {
        line=l;
        xCoord=new ArrayList<Double>();
        yCoord=new ArrayList<Double>();
        xCoord.addAll(x);
        yCoord.addAll(y);
        length=countLength(xCoord, yCoord);
    }

    private double countLength(ArrayList<Double> x, ArrayList<Double> y) {
        double sum;
        double sqr;
        double l=0;
        for (int i=0;i<x.size()-1; i++) {
            sum=0;
            sum += ((y.get(i) - y.get(i + 1)) * (y.get(i) - y.get(i + 1)) + (x.get(i) - x.get(i + 1)) * (x.get(i) - x.get(i + 1)));
            sqr= Math.sqrt(sum);
            l+=sqr;
        }
        return l;
    }

    @Override
    public int compareTo(loman l) {
        return (new Double(l.length)).compareTo(new Double(length));
    }

    public String toString() {
        String str="";
        str+="#"+line+" ";
        for (int i=0; i<xCoord.size(); i++)
            str+="("+xCoord.get(i)+":"+yCoord.get(i)+") ";
        str+="length = "+length;
        return str;
    }
}