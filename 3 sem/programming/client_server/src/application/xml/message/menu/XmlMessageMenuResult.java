package application.xml.message.menu;

import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;
import application.protocol.result.ResultException;
import application.xml.message.XmlMessageResult;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import java.io.Serializable;
import java.util.Arrays;

@XmlRootElement
public class XmlMessageMenuResult extends XmlMessageResult implements Result, Serializable {

	public static final long serialVersionUID = 1L;

	@XmlElement
	String[] options;

	public XmlMessageMenuResult() throws ResultException, CommandException {
		setCommand(Command.MENU);
	}

	public XmlMessageMenuResult(byte result, String[] options) throws ResultException, CommandException {
		super(Command.MENU, result);
		this.options = Arrays.copyOf(options, options.length);
	}


	public String[] getOptions() {
		return Arrays.copyOf(options, options.length);
	}
}
