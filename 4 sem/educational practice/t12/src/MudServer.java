import java.io.File;
import java.rmi.Naming;
import java.rmi.RemoteException;
import java.rmi.registry.LocateRegistry;
import java.rmi.server.UnicastRemoteObject;
import java.util.*;

public class MudServer extends UnicastRemoteObject implements Mud.MailServerInterface {
    static int PORT = 5050;
    ArrayList<Mud.MailClientInterface> ClientList;
    private String userName;
    public void printMes(String str)
    {
        System.out.println(str);
    }

    public MudServer(String name) throws RemoteException{
        this.userName=name;
        ClientList=new ArrayList<>();
    }
    public static void main(String[] args) {
        try {
            MudServer server = new MudServer(args[0]);

            LocateRegistry.createRegistry(5050);
            System.setProperty("java.rmi.server.hostname","192.168.0.12");
            Naming.rebind("rmi://" + Mud.mudPrefix + ":" + PORT + "/" + server.userName,server);
            System.out.println("Server connecting!");
        } catch (Exception e) {
            System.err.println(e.getMessage());
            System.out.println("Usage: java FreeTimeServer <username> \n");
            System.exit(1);
        }
    }
    @Override
    public Mud.MailClientInterface getPerson(String name) throws RemoteException {
        Optional<Mud.MailClientInterface> optional = ClientList.stream().filter(p -> {
            try {
                return Objects.equals(p.getName(), name);
            } catch (RemoteException e){
                System.err.println(e.getMessage());
            }
            return false;
        }).findFirst();
//        System.out.println("Persons are:");
//        for (Mud.MailClientInterface person : ClientList) {
//            System.out.println(person.getName());
//        }
//        System.out.println("\n");
        return optional.orElse(null) ;
    }
    @Override
    public void delClient(Mud.MailClientInterface current) throws RemoteException{
        ClientList.remove(current);
    }
    @Override
    public boolean addPerson(Mud.MailClientInterface current) throws RemoteException {
        Optional<Mud.MailClientInterface> optional = ClientList.stream().filter(p -> {
            try {
                return Objects.equals(p.getName(), current.getName());
            } catch (RemoteException e) {
                System.err.println(e.getMessage());
            }
            return false ;
        }).findFirst();
        if (!optional.isPresent()) {
            ClientList.add(current);
            return true;
        }
        return false;
    }
}
