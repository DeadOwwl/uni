package application.message;

import application.protocol.command.CommandException;
import application.protocol.result.Result;
import application.protocol.result.ResultException;

import java.io.Serializable;

public class MessageResult implements Result, Serializable {

	private static final long serialVersionUID = 1L;

	private String message = null;
	private final byte id;
	private final byte cmdID;

	public MessageResult(byte command, byte result) throws MessageException{
		if (!MessageResult.isValid(result)){
			throw new ResultException(result);
		}
		if (!Message.isValid(command)){
			throw new CommandException(command);
		}
		this.id = result;
		this.cmdID = command;
	}

	public MessageResult(byte command, byte result, String message) throws MessageException{
		this(command,result);
		this.message = message;
	}

	public static boolean isValid(byte result){
		return result >= OK && result <= UNKNOWN_ERROR;
	}

	public byte getResult() {
		return id;
	}

	public boolean checkError(){
		return id != OK;
	}

	public byte getCommand(){
		return cmdID;
	}

	public String getMessage() {
		return message;
	}
}
