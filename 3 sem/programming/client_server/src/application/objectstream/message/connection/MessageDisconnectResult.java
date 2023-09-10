package application.objectstream.message.connection;

import application.objectstream.message.MessageException;
import application.objectstream.message.MessageResult;
import application.protocol.command.Command;

import java.io.Serializable;

public class MessageDisconnectResult extends MessageResult implements Serializable {

	private static final long serialVersionUID = 1L;

	public MessageDisconnectResult(byte result) throws MessageException {
		super(Command.DISCONNECT, result);
	}

	public MessageDisconnectResult(byte result, String message) throws MessageException {
		super(Command.DISCONNECT, result, message);
	}
}
