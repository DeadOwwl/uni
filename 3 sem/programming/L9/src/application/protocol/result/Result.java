package application.protocol.result;

public interface Result {
	byte INVALID = -1;
	byte OK = 0;
	byte IO_ERROR = 1;
	byte MSG_ERROR = 2;
	byte CLASS_ERROR = 3;
	byte UNKNOWN_ERROR = 4;
}
