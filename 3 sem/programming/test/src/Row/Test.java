package Row;

import java.io.*;
import java.util.ArrayList;
import java.util.Collections;

public class Test {
    public static final String fileNameIn = "in.txt";
    public static final String fileNameOut = "out.txt";

    private static ArrayList<Row> list = new ArrayList<>();
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new FileReader(fileNameIn))){
            int count = 0;
            while (reader.ready()) {
                String line = reader.readLine();
                getRaw(line, count);
                count++;
            }


        } catch (IOException e) {

        }
        Collections.sort(list);
        try(BufferedWriter writer = new BufferedWriter(new FileWriter(fileNameOut)))
        {
            for(Row row : list)
            {
                writer.write(row.toString() + "\n");
            }
        }
        catch(IOException e)
        {
            e.printStackTrace();
        }
    }
    public static void getRaw(String line, int count)
    {
        ArrayList<Double> numbers = Row.getRow(line);
        if(numbers != null)
        {
            Row row = new Row(line, numbers, count);
            list.add(row);
        }
    }
}
