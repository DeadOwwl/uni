package application.message.order;

import application.message.Message;
import application.protocol.command.CommandException;

import java.io.Serializable;

public class MessageOrder extends Message implements Serializable {

	public static final long serialVersionUID = 1L;

	String address;
	String order;

	public MessageOrder(String address, String order) throws CommandException {
		super(Message.ORDER);
		this.address = address;
		this.order = order;
	}

	public String getAddress() {
		return address;
	}

	public String getOrder() {
		return order;
	}

}
