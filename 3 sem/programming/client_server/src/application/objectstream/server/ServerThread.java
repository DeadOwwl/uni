package application.objectstream.server;

import application.objectstream.message.Message;
import application.objectstream.message.MessageException;
import application.objectstream.message.MessageResult;
import application.objectstream.message.connection.MessageConnectResult;
import application.objectstream.message.connection.MessageDisconnectResult;
import application.objectstream.message.order.MessageOrder;
import application.objectstream.message.order.MessageOrderResult;
import application.objectstream.message.menu.MessageMenuResult;
import application.protocol.Config;
import application.protocol.command.Command;
import application.protocol.result.Result;
import application.xml.message.order.XmlMessageOrder;
import application.xml.message.order.XmlMessageOrderResult;

import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.URISyntaxException;
import java.nio.charset.StandardCharsets;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;

public class ServerThread extends Thread implements Closeable {

	protected static String fileName = Config.menuDIr;
	protected static Integer orderNum = 1;

	protected boolean isRunning;
	protected final Server server;
	protected final Socket client;
	private ObjectOutputStream oos;
	private ObjectInputStream ois;
	protected final InetAddress ia;

	public ServerThread(Server server, Socket socket) throws IOException, URISyntaxException {
		this.client = socket;
		this.server = server;
		client.setSoTimeout(500);
		ia = client.getInetAddress();
	}

	public void close() throws IOException {
		if (oos != null)
			oos.close();
		if (ois != null)
			ois.close();
		if (client != null)
			client.close();
		server.removeThread(this);
	}

	public InetAddress getClientInetAddress() {
		return ia;
	}

	public static synchronized String[] readMenu(String fName) throws IOException {
		ArrayList<String> lines = new ArrayList<>();
		try (BufferedReader br = new BufferedReader(new InputStreamReader(new FileInputStream(fName), StandardCharsets.UTF_8))) {
			String line;
			while ((line = br.readLine()) != null) {
				lines.add(line);
			}
		}
		return lines.toArray(new String[0]);
	}

	private synchronized MessageOrderResult saveOrder(MessageOrder order) throws MessageException {
		try {
			String orderName = "orders\\" + (orderNum).toString() + ".txt";
			File f = new File(orderName);
			if (!f.exists())
				f.createNewFile();

			try (BufferedWriter br = new BufferedWriter(
					new OutputStreamWriter(
							new FileOutputStream(orderName)))) {
				br.write("Address: " + order.getAddress() + '\n'+
						"Date: " + new SimpleDateFormat().format(new Date()) +'\n' +
						"Order: " + order.getOrder());
				br.flush();
			}
			return new MessageOrderResult(Result.OK, orderNum++);
		} catch (IOException e) {
			return new MessageOrderResult(Result.IO_ERROR, -1);
		} catch (MessageException e) {
			return new MessageOrderResult(Result.MSG_ERROR, -1);
		} catch (Exception e) {
			return new MessageOrderResult(Result.UNKNOWN_ERROR, -1);
		}
	}

	private MessageResult processMessage(Message msg) throws
			IOException, MessageException {

		if (msg == null)
			return null;

		System.out.println("New message. From " + ia.getHostAddress() + ". Command: " + msg.getId());

		switch (msg.getId()) {
			case Command.CONNECT:
				return new MessageConnectResult(Result.OK);

			case Command.MENU:
				return new MessageMenuResult(Result.OK, readMenu(fileName));

			case Command.ORDER:

				MessageOrderResult orderResult = saveOrder((MessageOrder) msg);
				if (orderResult.checkError()) {
					System.out.println(
							"New order. #" + (orderResult).getNumber() +
									"\n\tAddress: " + ((MessageOrder) msg).getAddress() +
									"\n\tDate: " + new SimpleDateFormat().format(new Date())+
									"\n\tOrder: " + ((MessageOrder) msg).getOrder()
					);
				}
				return orderResult;

			case Command.DISCONNECT:
				isRunning = false;
				System.out.println("Disconnected: " + ia.getHostName());
				return new MessageDisconnectResult(Result.OK);
			default:
				return new MessageResult(Command.INVALID, Result.UNKNOWN_ERROR);
		}
	}

	private boolean initConnection() {
		try {
			ois = new ObjectInputStream(client.getInputStream());
			oos = new ObjectOutputStream(client.getOutputStream());
			System.out.println("Connected: " + ia.getHostAddress());
			return true;
		} catch (IOException e) {
			return false;
		}
	}

	@Override
	public void run() {

		isRunning = initConnection();

		while (isRunning) {
			Message msg = null;
			try {
				msg = (Message) ois.readObject();
			} catch (SocketTimeoutException e) {
				continue;
			} catch (Exception e) {
				isRunning = false;
			}

			try {
				oos.writeObject(processMessage(msg));
			} catch (IOException e) {
				try {
					oos.writeObject(new MessageResult(msg.getId(), Result.IO_ERROR));
					e.printStackTrace();
				} catch (IOException | MessageException err) {
				}
			} catch (MessageException e) {
				System.err.println(e.getMessage());
			}
		}

		try {
			close();
		} catch (IOException e) {
		}
	}
}