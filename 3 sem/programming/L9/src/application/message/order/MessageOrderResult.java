package application.message.order;
import application.message.MessageException;
import application.message.MessageResult;
import application.protocol.command.Command;

import java.io.Serializable;

public class MessageOrderResult extends MessageResult implements Serializable {

	private static final long serialVersionUID = 1L;

	private int number;

	public MessageOrderResult(byte result, int number) throws MessageException {
		super(Command.ORDER, result);
		this.number = number;
	}

	public MessageOrderResult(byte result, String message, int number) throws MessageException{
		super(Command.ORDER,result,message);
		this.number = number;
	}

	public int getNumber() {
		return number;
	}
}
