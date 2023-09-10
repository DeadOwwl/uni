package task_15;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;
import java.util.StringTokenizer;
import java.util.TreeMap;

/*Вариант 15
 * найти длинные числа, отсортировать и вывести с 
 * номерами строк, в которых они встречались
 */

public class task_15{
	
	public static void main(String[] args) {
		
		Scanner n = new Scanner (System.in);
		try {
			int number = 1;
			HashMap<Long, StringBuilder> longs = new HashMap<Long, StringBuilder>();
			String l = "";
			while(n.hasNext() && !(l = n.nextLine()).equals("")) {
				StringTokenizer st = new StringTokenizer( l," ");
				while(st.hasMoreTokens()) {
					String division = st.nextToken();	
					if(division.charAt(division.length()-1)=='L' || division.charAt(division.length()-1)=='l') {
						String nw  = division.substring(0, division.length()-1);
						try {
						    if(!longs.containsKey(Long.valueOf(nw)))
						    	longs.put(Long.valueOf(nw), new StringBuilder("" + number));
						    else
								longs.put(Long.valueOf(nw), new StringBuilder( longs.get(Long.valueOf(nw))+" "+number));
						} 
						catch(Exception e){}
					}		
				} 
				number++;
			}
			Map<Long, StringBuilder> treeMap = new TreeMap<Long, StringBuilder>(longs);
			System.out.println(treeMap.toString());
		} catch(Exception c) {
			System.out.println(c.toString());
		}finally{
			n.close();
		}
	}
}