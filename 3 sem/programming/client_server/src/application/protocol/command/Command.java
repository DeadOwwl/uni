package application.protocol.command;

public interface Command {
	byte INVALID = -1;
	byte CONNECT = 0;
	byte ORDER = 1;
	byte MENU = 2;
	byte CONTEXT = 3;
	byte DISCONNECT = 4;
}