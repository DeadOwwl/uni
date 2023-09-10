package task_8;

interface t_8 { 
	void print (String... args); 
	}

public class task_8 implements t_8 {
	public static void main (String[] args) {
		new task_8().print(args);
}
	
public void print (String... args) {
	for (String str: args)
		System.out.println(str);
	}
}
