package application.xml.message.order;

import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.ResultException;
import application.xml.message.XmlMessageResult;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.io.Serializable;

@XmlRootElement
public class XmlMessageOrderResult extends XmlMessageResult implements Serializable {

	private static final long serialVersionUID = 1L;

	@XmlElement
	private int number;

	public XmlMessageOrderResult() throws CommandException {
		setCommand(Command.ORDER);
		number = -1;
	}

	public XmlMessageOrderResult(byte result, int number) throws ResultException, CommandException {
		super(Command.ORDER, result);
		this.number = number;
	}

	public XmlMessageOrderResult(byte result, String message, int number) throws ResultException, CommandException {
		super(Command.ORDER, result, message);
		this.number = number;
	}

	public int getNumber() {
		return number;
	}
}
