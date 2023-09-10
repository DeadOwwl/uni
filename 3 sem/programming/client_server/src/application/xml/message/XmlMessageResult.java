package application.xml.message;

import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.protocol.result.Result;
import application.protocol.result.ResultException;
import application.xml.Xml;

import javax.xml.bind.JAXBException;
import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.Serializable;

@XmlTransient
public class XmlMessageResult extends Xml implements Result, Serializable {

	public static class Data implements Serializable {

		private static final long serialVersionUID = 1L;

		@XmlAttribute()
		private byte id;

		@XmlAttribute()
		private byte command;

		@XmlAttribute()
		private String errMessage;

		public Data() {
			command = Command.INVALID;
			id = Result.INVALID;
		}

		@XmlTransient
		public byte getID() {
			return id;
		}

		public void setID(byte id) throws ResultException {
			if (!XmlMessageResult.isValid(id))
				throw new ResultException(id);
			this.id = id;
		}

		@XmlTransient
		public byte getCommand() {
			return command;
		}

		public void setCommand(byte command) throws CommandException {
			if (!XmlMessage.isValid(command))
				throw new CommandException(command);
			this.command = command;
		}

		@XmlTransient
		public String getErrorMessage() {
			return errMessage;
		}

		public void setErrorMessage(String errorMessage) {
			this.errMessage = errorMessage;
		}

		public boolean checkError() {
			return id == Result.OK;
		}

		public String toString() {
			return "" + id + ", " + ", " + errMessage;
		}

	}

	private static final long serialVersionUID = 1L;

	@XmlElement
	Data data;

	public XmlMessageResult() {
		data = new Data();
	}

	public XmlMessageResult(byte command, byte result) throws ResultException, CommandException {
		this();
		setCommand(command);
		setID(result);
	}

	public XmlMessageResult(byte command, byte result, String errorMessage) throws ResultException, CommandException {
		this();
		setCommand(command);
		setID(result);
		setErrorMessage(errorMessage);
	}


	protected XmlMessageResult.Data getData() {
		return data;
	}

	@XmlTransient()
	public byte getID() {
		return getData().getID();
	}

	public void setID(byte id) throws ResultException {
		getData().setID(id);
	}

	@XmlTransient
	public byte getCommand() {
		return getData().getCommand();
	}

	public void setCommand(byte command) throws CommandException {
		getData().setCommand(command);
	}

	@XmlTransient
	public String getErrorMessage() {
		return getData().getErrorMessage();
	}

	public void setErrorMessage(String msg) {
		getData().setErrorMessage("");
	}

	public static boolean isValid(byte result) {
		return result >= OK && result <= UNKNOWN_ERROR;
	}

	public boolean checkError() {
		return getData().checkError();
	}

	@Override
	public String toString() {
		try {
			return toXml(this);
		} catch (Exception e) {
			e.printStackTrace();
		}
		return null;
	}

}
