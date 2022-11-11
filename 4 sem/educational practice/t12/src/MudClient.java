import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.rmi.Naming;
import java.util.ArrayList;

public class MudClient {
    private static ArrayList<String> messages;
    private static BufferedReader in = new BufferedReader(new InputStreamReader(System.in));

    public static void main(String[] args) {
        try {
            messages = new ArrayList<>();
            String hostname = "localhost";
            String serverName = "MyServer";
            Mud.MailServerInterface server = (Mud.MailServerInterface) Naming.lookup("rmi://" + hostname
                    + ":" + MudServer.PORT + "/" + serverName);
            System.out.println("You are connected to MailServerInterface!");
            runUser(serverName, server);
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
        System.out.println("Usage: java FreeTimeClient <host> <user>");
        System.exit(1);
    }

    private static void runUser(String username, Mud.MailServerInterface server) throws IOException, InterruptedException {
        String currentPersonName = welcome(username, server);
     //   Mud.MailClientInterface curname=server.getPerson(currentPersonName);
        String cmd;
        for(;;) {

            try {
                 try {
                 Thread.sleep(300);
                 } catch (InterruptedException ignored) {
                 }
                 cmd = getLine(">> ");

                switch (cmd) {
                    case "s":
                        sendOrder(server, currentPersonName);
                        break;
                    case "sh":
                        showOrders(server,currentPersonName);
                        break;
                    case "m":
                        System.out.println(menu);
                        break;
                    case "help":
                    case "h":
                        System.out.println(help);
                        break;
                    case "quit":
                    case "q":
                        delClient(server,currentPersonName);
                        System.out.println("Bye!");
                        System.out.flush();
                        System.exit(0);
                     default:
                        System.out.println("Unknown command.  Try 'help'.\n");
                }
            } catch (Exception e) {
                System.out.println("Syntax or other error:");
                System.out.println(e);
                System.out.println("Try using the 'help' command.");
            }
        }
    }
    private static String welcome(String serverName, Mud.MailServerInterface server) throws IOException, InterruptedException {
        Mud.MailClientInterface currentPerson = null;
        do {
            String cmd = getLine("[" + serverName + "]:" + "Do you want to register or login?\n" +
                    "\tr : register\n" +
                    "\tl : login\n" +
                    ">> ");
            String name = getLine(">> Input your name: ");
            switch (cmd) {
                case "r": {
                    PrintWriter out = new PrintWriter(System.out);
                    MudPerson current = new MudPerson(name, out, in);
                    if (server.addPerson(current)) {
                        System.out.println(">> You are successful registered as \"" + name + "\"");
                        currentPerson = server.getPerson(name);
                    } else {
                        System.out.println(">> Name \"" + name + "\" is already used.");
                    }
                    break;
                }
                case "l": {
                    currentPerson = server.getPerson(name);
                    if (currentPerson != null) {
                        System.out.println(">> You are logged in as \"" + currentPerson.getName() + "\".");
                    } else {
                        System.out.println(">> No user with this name was found.");
                    }
                    break;
                }
                default: {
                    System.out.println(">> Incorrect key + \"" + cmd + "\"");
                    currentPerson = null;
                    break;
                }
            }
        } while (currentPerson == null);
        System.out.println(menu);
        return currentPerson.getName();
    }
    private static String getLine(String prompt) throws InterruptedException {
        String line = null;
        do {
            try {
                System.out.print(prompt);
                System.out.flush();
                line = in.readLine();
                if (line != null) line = line.trim();
                } catch (Exception ignored) {

            }
        } while ((line == null) || (line.length() == 0));
        return line;
    }
    private  static  void delClient(Mud.MailServerInterface server,String personName)throws IOException, InterruptedException{
        Mud.MailClientInterface person = server.getPerson(personName);
        server.delClient(person);
    }
    private static void showOrders(Mud.MailServerInterface server, String personName)throws IOException, InterruptedException{
       // String secondPersonName = getLine(">> Whose messages do you want to see ?\n" +
    //            ">> ");
        Mud.MailClientInterface person = server.getPerson(personName);
 //       Mud.MailClientInterface secondPerson = server.getPerson(secondPersonName);
        if (personName != null) {
            System.out.println(person.showMessage());
        }
        else {
            System.out.println(">> No user with this name was found.\n");
        }
        System.out.flush();
    }
    private static void sendOrder(Mud.MailServerInterface server, String personName) throws IOException, InterruptedException {
        String secondPersonName = getLine(">> Input your address\n" +
                ">> ");        Mud.MailClientInterface person = server.getPerson(personName);
                Mud.MailClientInterface secondPerson = server.getPerson(personName);
                String message="Name: "+ personName +"\nAdderss: " + secondPersonName+"\n"+"Order:  "+getLine(">> input your order\n" + "\n>> ");
                secondPerson.addOrder(message);
                server.printMes(message);
                System.out.flush();
    }
    private static final String help = "Commands:\n" +
            "s : send order\n" +
            "sh: show your orders\n" +
            "m: menu"+
            "help | h: display this message\n" +
            "q : quit\n";

    private static final String menu = "1) Драники\tЦена: 3.76 руб.\n"+
            "2) Салат Цезарь.\tЦена: 2.24 руб.\n"+
                    "3) Яйца.\tЦена: 0.87 руб.\n"+
                    "4) Каша вязкая.\tЦена: 0.79 руб.\n"+
                    "5) Суп.\tЦена: 1.01 руб.\n"+
                    "6) Кока-Кола.\tЦена: 0.95 руб.\n";
}