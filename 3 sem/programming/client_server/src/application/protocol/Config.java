package application.protocol;

import java.io.File;

public interface Config {
	int PORT = 8888;
	String HOST = "localhost";
	int XML_MAX = 1024;
	String orderDir = "orders";
	String xsdDirServer = "res" + File.separator + "server" +  File.separator + "xsd";
	String dtdDirServer = "res" + File.separator + "server"  + File.separator + "dtd";
	String xsdDirClient = "res" + File.separator + "client" + File.separator + "xsd";
	String dtdDirClient = "res" + File.separator + "client" + File.separator + "dtd";
	String menuDIr = "res" + File.separator + "server"+ File.separator +"menu.txt";
	String[] xsdFileNames = {
			"XmlMessageConnect.xsd",
			"XmlMessageConnectResult.xsd",
			"XmlMessageDisconnect.xsd",
			"XmlMessageDisconnectResult.xsd",
			"XmlMessageMenu.xsd",
			"XmlMessageMenuResult.xsd",
			"XmlMessageOrder.xsd",
			"XmlMessageOrderResult.xsd"
	};
	String[] dtdFileNames = {
			"XmlMessageConnect.dtd",
			"XmlMessageConnectResult.dtd",
			"XmlMessageDisconnect.dtd",
			"XmlMessageDisconnectResult.dtd",
			"XmlMessageMenu.dtd",
			"XmlMessageMenuResult.dtd",
			"XmlMessageOrder.dtd",
			"XmlMessageOrderResult.dtd"
	};
}
