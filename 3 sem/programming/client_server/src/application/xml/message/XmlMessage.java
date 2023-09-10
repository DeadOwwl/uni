package application.xml.message;

import application.protocol.command.Command;
import application.protocol.command.CommandException;
import application.xml.Xml;

import javax.xml.bind.annotation.XmlAttribute;
import javax.xml.bind.annotation.XmlElement;
import javax.xml.bind.annotation.XmlTransient;
import java.io.Serializable;

@XmlTransient
public class XmlMessage extends Xml implements Command, Serializable {

	public static class Data implements Serializable {

		private static final long serialVersionUID = 1L;


		protected byte id;

		public Data() {
			id = INVALID;
		}

		@XmlAttribute(required = true)
		public byte getID() {
			return id;
		}

		public void setID(byte id) throws CommandException {
			if (!isValid(id))
				throw new CommandException(id);
			this.id = id;
		}

		public String toString() {
			return "" + id;
		}
	}

	@XmlElement
	protected Data data;

	protected XmlMessage.Data getData() {
		return data;
	}

	private static final long serialVersionUID = 1L;

	protected XmlMessage() {
		data = new Data();
	}

	public XmlMessage(byte id) throws CommandException {
		this();
		setID(id);
	}

	public static boolean isValid(byte command) {
		return command >= CONNECT && command <= DISCONNECT;
	}


	public byte getId() {
		return getData().getID();
	}

	protected void setID(byte id) throws CommandException {
		getData().setID(id);
	}

}
