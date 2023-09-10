package application.manage;

import application.objectstream.message.MessageException;
import application.protocol.Config;
import application.xml.message.order.XmlMessageOrder;
import org.xml.sax.SAXException;

import javax.xml.bind.JAXBException;
import java.io.*;
import java.net.URISyntaxException;

public class Test {

	public static void main(String[] args) throws JAXBException, IOException, MessageException, SAXException, URISyntaxException {
		String xmlRequest = "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?><xmlMessageConnect><data id=\"0\"/></xmlMessageConnect>";
		String lClassName = XmlMessageOrder.class.getSimpleName();
		lClassName = Character.toLowerCase(lClassName.charAt(0)) + lClassName.substring(1);

		StringBuilder sb = new StringBuilder(xmlRequest);
		sb.insert(xmlRequest.indexOf('>') + 1, String.format("<!DOCTYPE %s SYSTEM \"%s\">",
				lClassName, Config.dtdDirServer + File.separatorChar + XmlMessageOrder.class.getSimpleName() + ".dtd"));
		System.out.println(sb.toString().indexOf("standalone=\"yes\""));
		sb.delete(sb.indexOf("standalone=\"yes\""), sb.indexOf("standalone=\"yes\"") + "standalone=\"yes\"".length());
		System.out.println(sb.toString());
	}
}
