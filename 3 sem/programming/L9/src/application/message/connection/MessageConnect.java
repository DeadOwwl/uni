package application.message.connection;

import application.message.Message;
import application.protocol.command.Command;
import application.protocol.command.CommandException;

public class MessageConnect extends Message {

	public MessageConnect() throws CommandException {
		super(Command.START);
	}
}
