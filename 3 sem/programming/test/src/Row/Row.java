package Row;

import java.util.ArrayList;
import java.util.StringTokenizer;

public class Row implements Comparable<Row>{
    private String  rowStr;
    private ArrayList<Double> row;
    private int line;
    private double M;
    private double D;
    private double S;
    private double C;

    public Row(String rowStr, ArrayList<Double> row, int line)
    {
        this.rowStr = rowStr.replaceAll("\\s", " ").trim();
        this.row = row;
        this.line = line;

        createM();
        createD();
        createS();
        createC();

    }
    public static ArrayList<Double> getRow(String line)
    {
        ArrayList<Double> row = new ArrayList<>();
        StringTokenizer tokenizer = new StringTokenizer(line, " \n\r\t");
        while(tokenizer.hasMoreElements())
        {
            String word = tokenizer.nextToken();
            try {
                double number = Double.parseDouble(word);
                row.add(number);
            }
            catch(NumberFormatException e)
            {
                return null;
            }
        }
        return row;
    }
    private void createM(){
        double sum = 0.0;
        for(Double n : row)
        {
            sum += n;
        }
        this.M = sum / row.size();
    }
    private void createD()
    {
        double sum = 0.0;
        for(Double x : row)
        {
            sum += Math.pow(x - this.M, 2);
        }
        this.D = sum / (row.size()-1);
    }
    private void createS()
    {
        this.S = Math.sqrt(this.D);
    }
    private void createC()
    {
        this.C = (this.S / this.M);
    }

    public ArrayList<Double> getRow() {
        return row;
    }

    public int getLine() {
        return line;
    }

    public double getM() {
        return M;
    }

    public double getD() {
        return D;
    }

    public double getS() {
        return S;
    }

    public double getC() {
        return C;
    }

    public String getRowStr() {
        return rowStr;
    }

    @Override
    public int compareTo(Row o) {
        return new Double(this.C).compareTo(o.C);
    }
    @Override
    public String toString(){
        return "Ряд: " + rowStr + "; Номер строки: " + line + "; M = " + M + "; D = " + D + " ; C = " + C;
    }
}
