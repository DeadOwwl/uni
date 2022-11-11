import java.io.BufferedReader;
import java.io.PrintWriter;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

public class MudPerson extends UnicastRemoteObject implements Mud.MailClientInterface{
    private String name;
    private PrintWriter out;
    private final BufferedReader in;
    private ArrayList<String> orders;
    MudPerson(String name, PrintWriter out, BufferedReader in) throws RemoteException {
        this.name = name;
        this.out = out;
        this.in = in;
        orders = new ArrayList<>();
    }
    @Override
    public String getName() throws RemoteException {
        return name;
    }
    @Override
    public String showMessage() throws RemoteException{
        String res=(name+"'s orders:\n");
        for(String i: orders){
            res+=i+"\n";
        }
        return res;
    }
    @Override
    public void addOrder(String letter) throws RemoteException {
            orders.add(letter);
    }

    @Override
    public String toString() {
        return "{" + name + "}";
    }

}