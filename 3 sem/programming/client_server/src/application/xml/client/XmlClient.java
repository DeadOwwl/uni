package application.xml.client;

import application.objectstream.client.Client;
import application.objectstream.message.Message;
import application.objectstream.message.MessageException;
import application.objectstream.message.connection.MessageConnectResult;
import application.protocol.Config;
import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;
import application.xml.Xml;
import application.xml.message.XmlMessage;
import application.xml.message.XmlMessageResult;
import application.xml.message.connection.*;
import application.xml.message.menu.XmlMessageMenu;
import application.xml.message.menu.XmlMessageMenuResult;
import application.xml.message.order.XmlMessageOrder;
import application.xml.message.order.XmlMessageOrderResult;
import application.xml.schema.validator.InvalidSchemaException;
import application.xml.schema.validator.ValidationRequester;
import application.xml.schema.validator.ValidationType;
import com.sun.xml.internal.ws.policy.privateutil.PolicyUtils;

import javax.xml.bind.JAXBException;
import java.io.*;
import java.net.SocketException;
import java.util.Scanner;
import java.util.jar.JarException;

public class XmlClient extends Client {

	DataInputStream dataInputStream;
	DataOutputStream dataOutputStream;

	public XmlClient(String host, int port) throws IOException, MessageException, ClassNotFoundException {
		super(host, port);
	}


	protected XmlMessageResult sendMessage(XmlMessage msg) throws IOException, JAXBException, MessageException, InvalidSchemaException {
		if (msg == null)
			return null;

		dataOutputStream.write(msg.getId());
		dataOutputStream.writeUTF(Xml.toXml(msg));

		ValidationType vt = ValidationType.FULL;
		if (msg.getId() == Command.CONNECT)
			vt = ValidationType.NONE;

		return (XmlMessageResult) Xml.fromXml(Xml.getResultClass(msg.getClass()),
				dataInputStream.readUTF(), ValidationRequester.Client,vt);
	}

	@Override
	protected void readMenu() throws MessageException, IOException {
		XmlMessageMenuResult result = null;
		try {
			result = (XmlMessageMenuResult) sendMessage(new XmlMessageMenu());
		} catch (JAXBException | InvalidSchemaException e) {
			System.err.println(e.getMessage());
		}
		if (result != null && result.checkError()) {
			System.out.println(sMenu);
			for (String line : result.getOptions()) {
				System.out.println(line);
			}
		} else {
			System.out.println(sResponseError);
		}
	}

	@Override
	protected void makeOrder() throws MessageException, IOException, ClassNotFoundException {
		Scanner sc = new Scanner(System.in);
		System.out.println(sInputAddress);
		String address = sc.nextLine();
		System.out.println(sInputOrder);
		String choice = sc.nextLine();
		XmlMessageOrderResult result = null;
		try {
			result = (XmlMessageOrderResult) sendMessage(new XmlMessageOrder(address, choice));
		} catch (JAXBException | InvalidSchemaException e) {
			System.err.println(e.getMessage());
		}
		if (result != null && result.checkError())
			System.out.println(sOrderNumber + result.getNumber());
		else
			System.out.println(sResponseError);
	}

	@Override
	protected void disconnect() throws IOException, MessageException {
		try {
			if (sendMessage(new XmlMessageDisconnect()).getID() == Result.OK)
				System.out.println(sHaveANiceDay);
			else
				System.out.println(sLostConnection);
		} catch (JAXBException | InvalidSchemaException e) {
			System.err.println(e.getMessage());
		}
		isRunning = false;
		dataInputStream.close();
		dataOutputStream.close();
		clientSocket.close();
	}

	private void saveData(String fname, String data) throws IOException {
		File file = new File(fname);
		if (!file.exists())
			file.createNewFile();
		try (FileOutputStream fos = new FileOutputStream(file)){
			fos.write(data.getBytes());
			fos.flush();
		}
	}

	protected void saveXmlSchema(XmlMessageConnectResult mcr) {
		System.out.println("Обновление XML-схем...");
		try {
			for (int i = 0; i < mcr.getSchemaCount(); i++) {

				String fName = dataInputStream.readUTF();
				String fData = dataInputStream.readUTF();
				saveData(Config.xsdDirClient + File.separator + fName, fData);
				fName = dataInputStream.readUTF();
				fData = dataInputStream.readUTF();
				saveData(Config.dtdDirClient + File.separator + fName, fData);
			}
			System.out.println("Успешно.");
		} catch (IOException e) {
			exit("Ошибка.");
		}
	}

	protected void connect() throws MessageException {
		try {
			dataInputStream = new DataInputStream(clientSocket.getInputStream());
			dataOutputStream = new DataOutputStream(clientSocket.getOutputStream());

			XmlMessageConnectResult mcr = null;
			if ((mcr = (XmlMessageConnectResult) sendMessage(new XmlMessageConnect())).getID() != Result.OK) {
				exit(sConnectionFailed);
			}
			else
				System.out.println("Соединение с сервером установлено.");

			saveXmlSchema(mcr);
		} catch (InvalidSchemaException | JAXBException e) {
			exit("Не удалось получить XML схемы");
		}catch (IOException ee) {
			ee.printStackTrace();
			exit(sConnectionFailed);
		}
	}


	@Override
	public void run() {
		try {
			connect();
		}catch (MessageException eee){
			exit("");
		}
			isRunning = true;
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
	}
}