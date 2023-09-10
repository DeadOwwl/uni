package application.message.connection;

import application.message.MessageException;
import application.message.MessageResult;
import application.protocol.command.Command;

import java.io.Serializable;

public class MessageDisconnectResult extends MessageResult implements Serializable {

	private static final long serialVersionUID = 1L;

	public MessageDisconnectResult(byte result) throws MessageException {
		super(Command.END, result);
	}

	public MessageDisconnectResult(byte result, String message) throws MessageException{
		super(Command.END,result,message);
	}
}
