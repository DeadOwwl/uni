import java.rmi.Remote;
import java.rmi.RemoteException;
import java.util.ArrayList;
public class Mud {
    static String mudPrefix = "localhost";

    public interface MailServerInterface extends Remote {
        MailClientInterface getPerson(String name) throws RemoteException;
        void delClient(MailClientInterface current) throws RemoteException;
        boolean addPerson(MailClientInterface current) throws RemoteException;
        void printMes(String str) throws RemoteException;
    }
    public interface MailClientInterface extends Remote {
        String showMessage() throws RemoteException;
        String getName() throws RemoteException;
        void addOrder(String letter) throws RemoteException;
    }
}
