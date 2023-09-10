package application.protocol.command;

public interface Command {
	byte INVALID = -1;
	byte START = 0;
	byte ORDER = 1;
	byte MENU = 2;
	byte END = 3;
}