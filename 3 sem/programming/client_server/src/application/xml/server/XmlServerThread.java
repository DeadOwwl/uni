package application.xml.server;

import application.objectstream.message.MessageException;
import application.objectstream.server.Server;
import application.objectstream.server.ServerThread;
import application.protocol.Config;
import application.protocol.command.Command;
import application.protocol.result.Result;
import application.xml.Xml;
import application.xml.message.XmlMessage;
import application.xml.message.XmlMessageResult;
import application.xml.message.connection.XmlMessageConnectResult;
import application.xml.message.connection.XmlMessageDisconnectResult;
import application.xml.message.menu.XmlMessageMenuResult;
import application.xml.message.order.XmlMessageOrder;
import application.xml.message.order.XmlMessageOrderResult;
import application.xml.schema.validator.InvalidSchemaException;
import application.xml.schema.validator.ValidationRequester;
import application.xml.schema.validator.ValidationType;

import javax.xml.bind.JAXBException;
import java.io.*;
import java.net.Socket;
import java.net.SocketTimeoutException;
import java.net.URISyntaxException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class XmlServerThread extends ServerThread {

	DataInputStream dis;
	DataOutputStream dos;

	public XmlServerThread(Server server, Socket socket) throws IOException, URISyntaxException {
		super(server, socket);
	}

	@Override
	public void close() throws IOException {
		dis.close();
		dos.close();
		client.close();
		server.removeThread(this);
	}

	private synchronized XmlMessageOrderResult saveOrder(XmlMessageOrder order) throws MessageException {
		try {
			String orderName = Config.orderDir + File.separator + (orderNum).toString() + ".txt";
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
			return new XmlMessageOrderResult(Result.OK, orderNum++);
		} catch (IOException e) {
			return new XmlMessageOrderResult(Result.IO_ERROR, -1);
		} catch (MessageException e) {
			return new XmlMessageOrderResult(Result.MSG_ERROR, -1);
		} catch (Exception e) {
			return new XmlMessageOrderResult(Result.UNKNOWN_ERROR, -1);
		}
	}

	protected String readFile(String fName) throws FileNotFoundException {
		StringBuilder s = new StringBuilder();
		try (Scanner in = new Scanner(new File(fName))){
			while (in.hasNext())
				s.append(in.nextLine()).append("\r\n");
		}
		return s.toString();
	}


	private void sendSchemas(XmlMessageConnectResult mcr) throws IOException {
		for(int i =0;i< mcr.getSchemaCount();i++){
			dos.writeUTF(Config.xsdFileNames[i]);
			dos.writeUTF(readFile(Config.xsdDirServer + File.separator + Config.xsdFileNames[i]));
			dos.writeUTF(Config.dtdFileNames[i]);
			dos.writeUTF(readFile(Config.dtdDirServer + File.separator + Config.dtdFileNames[i]));
		}
	}

	private XmlMessage createMessage(byte type, String xmlData) throws IOException, JAXBException, InvalidSchemaException {
		return (XmlMessage) Xml.fromXml(Xml.getMessageClass(type), xmlData, ValidationRequester.Server,ValidationType.FULL);
	}

	private XmlMessageResult getResult(XmlMessage msg) throws MessageException, IOException {

		XmlMessageResult xmr = null;

		switch (msg.getId()) {
			case Command.CONNECT:
				xmr = new XmlMessageConnectResult(Result.OK);
				break;

			case Command.MENU:
				xmr = new XmlMessageMenuResult(Result.OK, readMenu(fileName));
				break;

			case Command.ORDER:
				xmr = saveOrder((XmlMessageOrder) msg);

				if (xmr.checkError())
					System.out.println("New order. #" + ((XmlMessageOrderResult) xmr).getNumber() +
							"\n\tAddress: " + ((XmlMessageOrder) msg).getAddress() +
							"\n\tDate: " + new SimpleDateFormat().format(new Date())+
							"\n\tOrder: " + ((XmlMessageOrder) msg).getOrder());

				break;

			case Command.DISCONNECT:
				isRunning = false;
				System.out.println("Disconnected: " + ia.getHostName());
				xmr = new XmlMessageDisconnectResult(Result.OK);
				break;
			default:
				xmr = new XmlMessageResult(msg.getId(), Result.UNKNOWN_ERROR, "404 Not Found");
		}

		return xmr;
	}

	private boolean processMessage(byte command, String xmlRequest) throws
			IOException, MessageException, JAXBException {

		if (xmlRequest == null)
			return false;

		XmlMessage msg = null;
		try {
			msg = createMessage(command, xmlRequest);
		} catch (InvalidSchemaException e) {
			System.err.println(e.getMessage());
		}

		if (msg == null)
			return false;

		System.out.println("\n" + ia.getHostAddress() + " Request: " + xmlRequest);

		XmlMessageResult xmr = getResult(msg);

		try {
			dos.writeUTF(xmr.toString());
		} catch (Exception e) {
			return false;
		}
		System.out.println("Response data: " + xmr.toString());

		if (xmr.getCommand() == Command.CONNECT){
			sendSchemas((XmlMessageConnectResult)xmr);
		}

		return true;
	}


	private boolean initConnection() {
		try {
			dis = new DataInputStream(client.getInputStream());
			dos = new DataOutputStream(client.getOutputStream());
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
			String xmlRequest = null;
			XmlMessageResult msg = null;
			byte command = Command.INVALID;

			try {
				command = dis.readByte();
				xmlRequest = dis.readUTF();
			} catch (SocketTimeoutException e) {
				continue;
			} catch (Exception e) {
				isRunning = false;
				System.err.println(e.getMessage());
			}

			try {
				if (!processMessage(command, xmlRequest))
					dos.writeUTF(new XmlMessageResult(command, Result.UNKNOWN_ERROR, "Unknown error").toString());
			} catch (IOException | MessageException | JAXBException e) {
				System.err.println(e.getMessage());
			}
		}

		try {
			close();
		} catch (IOException e) {
		}
	}
}
