package application.message.menu;

import application.message.Message;
import application.message.MessageException;
import application.protocol.command.Command;

import java.io.Serializable;

public class MessageMenu extends Message implements Serializable {

	private static final long serialVersionUID = 1L;

	public MessageMenu() throws MessageException {
		super(Command.MENU);
	}
}
