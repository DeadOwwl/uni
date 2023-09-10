package application.server;

import application.message.*;
import application.message.connection.*;
import application.message.order.*;
import application.message.menu.MessageMenuResult;
import application.protocol.command.Command;
import application.protocol.result.Result;
import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;

public class ServerThread extends Thread implements Closeable{

	private static final String fileName = "menu.txt";
	private static Integer orderNum = 1;

	private boolean isRunning;
	private final Server server;
	private final Socket client;
	private final ObjectOutputStream oos;
	private final ObjectInputStream ois;
	private final InetAddress ia;

	public ServerThread(Server server, Socket socket) throws IOException {
		this.client = socket;
		this.server = server;
		client.setSoTimeout(500);
		oos = new ObjectOutputStream(client.getOutputStream());
		ois = new ObjectInputStream(client.getInputStream());
		ia = client.getInetAddress();
	}

	public void close() throws IOException{
		oos.close();
		ois.close();
		client.close();
		System.out.println("Disconnected: " + ia.getHostName());
		server.removeThread(this);
	}

	public InetAddress getClientInetAddress() {
		return ia;
	}

	private static synchronized String[] readMenu(String fName) throws IOException {
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
				br.write(order.getAddress() + '\n' + order.getOrder());
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

		System.out.println("New message. From " + ia.getHostName() + ". Command: " + msg.getId());

		switch (msg.getId()) {
			case Command.START:
				return new MessageConnectResult(Result.OK);

			case Command.MENU:
				return new MessageMenuResult(Result.OK, readMenu(fileName));

			case Command.ORDER:

				MessageOrderResult orderResult = saveOrder((MessageOrder)msg);
				if (!orderResult.checkError()) {
					System.out.println(
							"\nNew order. #" + orderResult.getNumber() +
							"\n\tAddress: " + ((MessageOrder) msg).getAddress() +
							"\n\tOrder: " + ((MessageOrder) msg).getOrder()
					);
				}
				return orderResult;

			case Command.END:
				try {
					isRunning = false;
					return new MessageDisconnectResult(Result.OK);
				} catch (Exception e) {
					return new MessageDisconnectResult(Result.UNKNOWN_ERROR);
				}
			default:
				return new MessageResult(Command.INVALID, Result.UNKNOWN_ERROR);
		}
	}

	@Override
	public void run() {
		System.out.println("Connected: " + ia.getHostAddress());
		isRunning = true;

		while (isRunning) {
			Message msg = null;
			try {
				msg = (Message) ois.readObject();
			}catch (SocketTimeoutException e){ continue; }
			 catch (Exception e) {
				 isRunning = false;
			 }

			try {
				oos.writeObject(processMessage(msg));
			} catch (IOException e) {
				try {
					oos.writeObject(new MessageResult(msg.getId(), Result.IO_ERROR));
					e.printStackTrace();
				} catch (IOException | MessageException err) { }
			} catch (MessageException e) { System.err.println(e.getMessage()); }
		}

		try {
			close();
		}
		catch (IOException e){ }
	}
}