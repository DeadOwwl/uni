package application.xml.schema.generator;

import application.protocol.Config;
import application.xml.Xml;
import application.xml.message.connection.XmlMessageConnect;
import application.xml.message.connection.XmlMessageConnectResult;
import application.xml.message.connection.XmlMessageDisconnect;
import application.xml.message.connection.XmlMessageDisconnectResult;
import application.xml.message.menu.XmlMessageMenu;
import application.xml.message.menu.XmlMessageMenuResult;
import application.xml.message.order.XmlMessageOrder;
import application.xml.message.order.XmlMessageOrderResult;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import java.io.IOException;

public abstract class XsdGenerator {


	public static void create(String fileName, Class<? extends Xml> what)
			throws JAXBException, IOException {
		JAXBContext context = JAXBContext.newInstance(what);
		context.generateSchema(new XsdOutputResolver(Config.xsdDirServer, fileName));
	}

	public static void generateAll() throws JAXBException, IOException {
		XsdGenerator.create(XmlMessageConnect.class.getSimpleName(), XmlMessageConnect.class);
		XsdGenerator.create(XmlMessageConnectResult.class.getSimpleName(), XmlMessageConnectResult.class);
		XsdGenerator.create(XmlMessageDisconnect.class.getSimpleName(), XmlMessageDisconnect.class);
		XsdGenerator.create(XmlMessageDisconnectResult.class.getSimpleName(), XmlMessageDisconnectResult.class);
		XsdGenerator.create(XmlMessageMenu.class.getSimpleName(), XmlMessageMenu.class);
		XsdGenerator.create(XmlMessageMenuResult.class.getSimpleName(), XmlMessageMenuResult.class);
		XsdGenerator.create(XmlMessageOrder.class.getSimpleName(), XmlMessageOrder.class);
		XsdGenerator.create(XmlMessageOrderResult.class.getSimpleName(), XmlMessageOrderResult.class);
	}


}
