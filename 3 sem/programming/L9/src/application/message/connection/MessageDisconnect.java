package application.message.connection;

import application.message.Message;
import application.protocol.command.Command;
import application.protocol.command.CommandException;

import java.io.Serializable;

public class MessageDisconnect extends Message implements Serializable {

	private static final long serialVersionUID = 1L;

	public MessageDisconnect() throws CommandException {
		super(Command.END);
	}
}
