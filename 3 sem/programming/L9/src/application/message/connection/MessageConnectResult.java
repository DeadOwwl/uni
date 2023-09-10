package application.message.connection;

import application.message.MessageException;
import application.message.MessageResult;
import application.protocol.command.Command;

import java.io.Serializable;

public class MessageConnectResult extends MessageResult implements Serializable {

	private static final long serialVersionUID = 1L;

	public MessageConnectResult(byte result) throws MessageException {
		super(Command.START, result);
	}

	public MessageConnectResult(byte result, String message) throws MessageException{
		super(Command.START,result,message);
	}
}
