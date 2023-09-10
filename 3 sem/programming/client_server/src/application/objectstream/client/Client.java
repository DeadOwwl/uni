package application.objectstream.client;

import application.objectstream.message.*;
import application.objectstream.message.connection.*;
import application.objectstream.message.menu.*;
import application.objectstream.message.order.*;
import application.protocol.*;
import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;
import org.omg.PortableInterceptor.SYSTEM_EXCEPTION;

import java.io.*;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.net.SocketException;
import java.util.Scanner;

public class Client extends Thread {

	protected static final String sLostConnection = "Потеряно соединение с сервером";
	protected static final String sUnknownCommand = "Неизвестная команда";
	protected static final String sResponseError = "Не удалось получить ответ от сервера";
	protected static final String sConnectionFailed = "Не удалось подключиться к серверу";
	protected static final String sMenu = "Меню:";
	protected static final String sOrderNumber = "Номер вашего заказа: ";
	protected static final String sInputAddress = "Введите адресс доставки:";
	protected static final String sInputOrder = "Выберите блюда из списка:";
	protected static final String sHaveANiceDay = "Удачного дня";
	protected static final String sExit = "<Press ENTER to exit>";
	protected static final String sHelp =
			"_____________________\n" +
					"| 1. Меню и цены    |\n" +
					"| 2. Сделать заказ  |\n" +
					"| 3. Выйти          |\n" +
					"|___________________|";

	protected boolean isRunning;
	protected Socket clientSocket;
	private ObjectInputStream ois;
	private ObjectOutputStream oos;

	public Client() throws IOException {
		this(Config.HOST, Config.PORT);
	}

	public Client(String host, int port) throws IOException {
		clientSocket = new Socket();
		clientSocket.connect(new InetSocketAddress(host, port), 5000);
		clientSocket.setSoTimeout(5000);
	}

	protected void exit(String exitMessage) {
		if (exitMessage != null)
			System.err.println(exitMessage);
		System.out.println(sExit);
		new Scanner(System.in).nextLine();
		System.exit(1);
	}

	protected byte translateCommand(String cmd) throws Exception {
		int command;
		try {
			command = Integer.parseInt(cmd);
		} catch (NumberFormatException e) {
			return Command.INVALID;
		}
		switch (command) {
			case 1:
				return Command.MENU;
			case 2:
				return Command.ORDER;
			case 3:
				return Command.DISCONNECT;
			default:
				return Command.INVALID;
		}
	}

	private MessageResult sendMessage(Message msg) throws IOException, ClassNotFoundException {
		if (msg == null)
			return null;
		oos.writeObject(msg);
		return (MessageResult) ois.readObject();
	}

	protected void readMenu() throws MessageException, IOException, ClassNotFoundException {
		MessageMenuResult result = (MessageMenuResult) sendMessage(new MessageMenu());
		if (result == null)
			return;

		if (result.checkError()) {
			System.out.println(sMenu);
			for (String line : result.getOptions()) {
				System.out.println(line);
			}
		} else {
			System.out.println(sResponseError);
		}
	}

	protected void makeOrder() throws MessageException, IOException, ClassNotFoundException {
		Scanner sc = new Scanner(System.in);
		System.out.println(sInputAddress);
		String address = sc.nextLine();
		System.out.println(sInputOrder);
		String choice = sc.nextLine();
		MessageOrderResult result = (MessageOrderResult) sendMessage(new MessageOrder(address, choice));
		if (result.checkError())
			System.out.println(sOrderNumber + result.getNumber());
		else
			System.out.println(sResponseError);
	}

	protected void processCommand(byte command) throws MessageException, IOException, ClassNotFoundException {
		switch (command) {
			case Command.MENU:
				readMenu();
				break;

			case Command.ORDER:
				makeOrder();
				break;

			case Command.DISCONNECT:
				disconnect();
				exit(null);
				break;

			default:
				throw new CommandException(command);
		}
	}

	@Override
	public void run() {
		try {
			oos = new ObjectOutputStream(this.clientSocket.getOutputStream());
			ois = new ObjectInputStream(this.clientSocket.getInputStream());
		} catch (IOException e) {
			System.err.println(sConnectionFailed);
		}

		isRunning = true;
		try {
			if (sendMessage(new MessageConnect()).getResult() != Result.OK) {
				exit(sConnectionFailed);
			}
			Scanner sc = new Scanner(System.in);
			while (isRunning) {
				try {
					System.out.println(sHelp);

					byte command = translateCommand(sc.nextLine());

					if (!Message.isValid(command)) {
						System.err.println(sUnknownCommand);
						continue;
					}
					try {
						processCommand(command);
					} catch (SocketException e) {
						exit(sLostConnection);
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	protected void disconnect() throws IOException, MessageException, ClassNotFoundException {

		if (sendMessage(new MessageDisconnect()).getResult() == Result.OK)
			System.out.println(sHaveANiceDay);
		else
			System.out.println(sLostConnection);
		isRunning = false;
		ois.close();
		oos.close();
		clientSocket.close();
	}

	@Override
	public void interrupt() {
		try {
			disconnect();
		} catch (Throwable e) {
		}
	}

	@Override
	protected void finalize() throws Throwable {
		disconnect();
	}
}
