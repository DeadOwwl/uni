package application.xml.message.connection;

import application.protocol.Config;
import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;
import application.protocol.result.ResultException;
import application.xml.message.XmlMessageResult;
import application.xml.schema.validator.InvalidSchemaException;

import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;
import java.io.FileNotFoundException;
import java.io.Serializable;
import java.util.concurrent.CopyOnWriteArrayList;

@XmlRootElement
public class XmlMessageConnectResult extends XmlMessageResult implements Result, Serializable {

	private static final long serialVersionUID = 1L;

	@XmlElement
	private int schemaCount;

	@XmlTransient
	private static boolean err;
	{
		if (Config.xsdFileNames.length != Config.dtdFileNames.length) {
			System.err.println("DTD count not equals XSD count");
			err = true;
			schemaCount = -1;
		}
		schemaCount = Config.xsdFileNames.length;
		err = false;
	}


	public XmlMessageConnectResult() throws CommandException, ResultException {
		setCommand(Command.CONNECT);
	}

	public XmlMessageConnectResult(byte result) throws ResultException, CommandException {
		super(Command.CONNECT, result);
		if (err)
			setID(UNKNOWN_ERROR);

	}

	public XmlMessageConnectResult(byte result, String message) throws ResultException, CommandException {
		super(Command.CONNECT, result, message);
		if (err)
			setID(UNKNOWN_ERROR);
	}

	public int getSchemaCount(){
		return schemaCount;
	}

}
