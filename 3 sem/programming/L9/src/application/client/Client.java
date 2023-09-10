package application.client;

import application.message.*;
import application.message.connection.*;
import application.message.menu.*;
import application.message.order.*;
import application.protocol.Config;
import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;

import java.io.*;
import java.net.ConnectException;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;
import java.util.Scanner;

public class Client extends Thread{

	private static final String sLostConnection = "Потеряно соединение с сервером";
	private static final String sUnknownCommand = "Неизвестная команда";
	private static final String sResponseError = "Не удалось получить ответ от сервера";
	private static final String sConnectionFailed = "Не удалось подключиться к серверу";
	private static final String sMenu = "Меню:";
	private static final String sOrderNumber = "Номер вашего заказа: ";
	private static final String sInputAddress = "Введите адресс доставки:";
	private static final String sInputOrder = "Выберите блюда из списка:";
	private static final String sHaveANiceDay = "Удачного дня";
	private static final String sExit = "<Press ENTER to exit>";
	private static final String sHelp =
					"_____________________\n" +
					"| 1. Меню и цены    |\n" +
					"| 2. Сделать заказ  |\n" +
					"| 3. Выйти          |\n" +
					"|___________________|";

	private boolean isRunning;
	private Socket clientSocket;
	private ObjectInputStream ois;
	private ObjectOutputStream oos;

	public Client(String host, int port) throws IOException{
			clientSocket = new Socket();
			clientSocket.connect(new InetSocketAddress(host, port), 5000);
			clientSocket.setSoTimeout(10000);
			oos = new ObjectOutputStream(this.clientSocket.getOutputStream());
			ois = new ObjectInputStream(this.clientSocket.getInputStream());
	}

	private void exit(String exitMessage) throws IOException{
		if (exitMessage != null)
			System.err.println(exitMessage);
		System.out.println(sExit);
		System.in.read();
		System.exit(1);
	}

	private MessageResult sendMessage(Message msg) throws IOException,ClassNotFoundException {
		oos.writeObject(msg);
		return (MessageResult)ois.readObject();
	}

	private byte translateCommand(int cmd) throws Exception{
		System.out.println(cmd);
		switch (cmd){
			case 1:
				return Command.MENU;
			case 2:
				return Command.ORDER;
			case 3:
				return Command.END;
			default:
				return Command.INVALID;
		}
	}

	private void readMenu() throws MessageException, IOException,ClassNotFoundException{
		oos.writeObject(new MessageMenu());
		MessageMenuResult result = (MessageMenuResult)ois.readObject();
		if (!result.checkError()) {
			System.out.println(sMenu);
			for (String line : result.getOptions()) {
				System.out.println(line);
			}
		}
		else {
			System.out.println(sResponseError);
		}
	}

	private void makeOrder() throws MessageException, IOException, ClassNotFoundException{
		Scanner sc = new Scanner(System.in);
		System.out.println(sInputAddress);
		String address = sc.nextLine();
		System.out.println(sInputOrder);
		String choice = sc.nextLine();
		oos.writeObject(new MessageOrder(address, choice));
		MessageOrderResult result = (MessageOrderResult)ois.readObject();
		if (!result.checkError())
			System.out.println(sOrderNumber + result.getNumber());
		else
			System.out.println(sResponseError);
	}

	private void processCommand(byte command) throws MessageException,IOException, ClassNotFoundException {
		switch (command){
			case Command.MENU:
				readMenu();
				break;

			case Command.ORDER:
				makeOrder();
				break;

			case Command.END:
				disconnect();
				exit(null);
				break;

			default:
				throw new CommandException(command);
		}
	}

	@Override
	public void run() {
		isRunning = true;
		try {
			if (sendMessage(new MessageConnect()).getResult() != Result.OK) {
				exit(sConnectionFailed);
			}
			Scanner sc = new Scanner(System.in);
			while (isRunning) {
				try {
					System.out.println(sHelp);

					byte command = translateCommand(sc.nextInt());

					if (!Message.isValid(command)) {
						System.err.println(sUnknownCommand);
						continue;
					}
					try {
						processCommand(command);
					}
					catch (SocketException e){
						exit(sLostConnection);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		}catch (Exception e){
			e.printStackTrace();
		}
	}

	private void disconnect() throws IOException, MessageException,ClassNotFoundException {
		isRunning = false;
		if (sendMessage(new MessageDisconnect()).getResult() == Result.OK)
			System.out.println(sHaveANiceDay);
		else
			System.out.println(sLostConnection);
		ois.close();
		oos.close();
		clientSocket.close();
	}

	@Override
	public void interrupt() {
		try {
			disconnect();
		}
		catch (Throwable e){ }
	}

	@Override
	protected void finalize() throws Throwable {
		disconnect();
	}

	public static void main(String[] args) throws Exception{
		new Client(Config.HOST, Config.PORT).start();
	}
}
