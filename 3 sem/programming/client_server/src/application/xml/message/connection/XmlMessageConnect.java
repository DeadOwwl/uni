package application.xml.message.connection;

import application.protocol.command.CommandException;
import application.xml.message.XmlMessage;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.io.Serializable;

@XmlRootElement
public class XmlMessageConnect extends XmlMessage implements Serializable {

	private static final long serialVersionUID = 1L;

	public XmlMessageConnect() throws CommandException {
		super(CONNECT);
	}
}
