package application.xml;


import application.objectstream.message.MessageException;
import application.protocol.Config;
import application.protocol.command.Command;
import application.xml.message.XmlMessage;
import application.xml.message.XmlMessageResult;
import application.xml.message.connection.XmlMessageConnect;
import application.xml.message.connection.XmlMessageConnectResult;
import application.xml.message.connection.XmlMessageDisconnect;
import application.xml.message.connection.XmlMessageDisconnectResult;
import application.xml.message.menu.XmlMessageMenu;
import application.xml.message.menu.XmlMessageMenuResult;
import application.xml.message.order.XmlMessageOrder;
import application.xml.message.order.XmlMessageOrderResult;
import application.xml.schema.validator.InvalidSchemaException;
import application.xml.schema.validator.ValidationRequester;
import application.xml.schema.validator.ValidationType;
import application.xml.schema.validator.XMLValidator;
import org.xml.sax.SAXException;

import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Marshaller;
import javax.xml.bind.Unmarshaller;
import javax.xml.bind.annotation.XmlTransient;
import javax.xml.parsers.ParserConfigurationException;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;

@XmlTransient
public abstract class Xml {

	public static String toXml(Xml msg) throws JAXBException, IOException {
		try (ByteArrayOutputStream byteArrayOutputStream = new ByteArrayOutputStream(Config.XML_MAX)) {
			JAXBContext context = JAXBContext.newInstance(msg.getClass());
			Marshaller m = context.createMarshaller();
			m.marshal(msg, byteArrayOutputStream);
			byteArrayOutputStream.flush();
			return byteArrayOutputStream.toString();
		}
	}

	public static Xml fromXml(Class<? extends Xml> what, String xmlData, ValidationRequester vr,ValidationType vt) throws JAXBException, IOException, InvalidSchemaException {

		boolean valid = false;
		try {
			valid = XMLValidator.validate(what, xmlData, vr, vt);
		} catch (SAXException | ParserConfigurationException e) {
		}

		if (!valid)
			throw new InvalidSchemaException(what, xmlData);

		try (ByteArrayInputStream byteArrayInputStream = new ByteArrayInputStream(xmlData.getBytes())) {
			JAXBContext context = JAXBContext.newInstance(what);
			Unmarshaller u = context.createUnmarshaller();
			return (Xml) u.unmarshal(byteArrayInputStream);
		}
	}

	public static Class<? extends XmlMessageResult> getResultClass(Class<? extends XmlMessage> msg) throws MessageException {
		if (XmlMessageConnect.class.equals(msg)) {
			return XmlMessageConnectResult.class;
		} else if (XmlMessageMenu.class.equals(msg)) {
			return XmlMessageMenuResult.class;
		} else if (XmlMessageOrder.class.equals(msg)) {
			return XmlMessageOrderResult.class;
		} else if (XmlMessageDisconnect.class.equals(msg)) {
			return XmlMessageDisconnectResult.class;
		}
		throw new MessageException("getResultClass: undefined error");
	}

	public static Class<? extends XmlMessage> getMessageClass(byte id) {

		switch (id) {
			case Command.CONNECT:
				return XmlMessageConnect.class;
			case Command.MENU:
				return XmlMessageMenu.class;
			case Command.ORDER:
				return XmlMessageOrder.class;
			case Command.DISCONNECT:
				return XmlMessageDisconnect.class;
			default:

		}
		return null;
	}

}
