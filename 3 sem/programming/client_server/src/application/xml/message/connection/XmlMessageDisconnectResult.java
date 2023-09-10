package application.xml.message.connection;

import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;
import application.protocol.result.ResultException;
import application.xml.message.XmlMessageResult;

import javax.xml.bind.annotation.XmlRootElement;
import java.io.Serializable;

@XmlRootElement
public class XmlMessageDisconnectResult extends XmlMessageResult implements Result, Serializable {

	private static final long serialVersionUID = 1L;

	public XmlMessageDisconnectResult() throws ResultException, CommandException {
		setCommand(Command.DISCONNECT);
	}

	public XmlMessageDisconnectResult(byte result) throws ResultException, CommandException {
		super(Command.DISCONNECT, result);
	}

	public XmlMessageDisconnectResult(byte result, String message) throws ResultException, CommandException {
		super(Command.DISCONNECT, result, message);
	}
}
