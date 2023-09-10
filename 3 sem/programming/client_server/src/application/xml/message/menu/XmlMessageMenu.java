package application.xml.message.menu;

import application.protocol.command.CommandException;
import application.xml.message.XmlMessage;

import javax.xml.bind.annotation.XmlRootElement;
import java.io.Serializable;

@XmlRootElement
public class XmlMessageMenu extends XmlMessage implements Serializable {

	private static final long serialVersionUID = 1L;

	public XmlMessageMenu() throws CommandException {
		super(MENU);
	}
}
