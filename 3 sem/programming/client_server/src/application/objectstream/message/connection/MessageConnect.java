package application.objectstream.message.connection;

import application.objectstream.message.Message;
import application.protocol.command.Command;
import application.protocol.command.CommandException;

import java.io.Serializable;

public class MessageConnect extends Message implements Serializable {

	private static final long serialVersionUID = 1L;

	public MessageConnect() throws CommandException {
		super(Command.CONNECT);
	}
}
