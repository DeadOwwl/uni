package application.manage;
import application.client.Client;
import com.sun.jdi.NativeMethodException;
import application.protocol.Config;
import application.server.Server;

import java.io.FileNotFoundException;
import java.io.IOException;
import java.net.ConnectException;
import java.net.Socket;
import java.util.Scanner;

public class Manage {

	private static final String helpString = "Syntax:\n" +
			"run 'application.server' [port]\n" +
			"    'application.client' [host] [port]}\n";

	private static void error() {
		System.err.println(helpString);
		System.exit(1);
	}

	public static void runServer(String[] args){
		switch (args.length){
			case 2:
				new Server(Config.PORT).start(true);
				break;
			case 3:
				try {
					new Server(Integer.parseInt(args[2])).start(true);
				} catch (NumberFormatException e) { error(); }
				break;
			default:
				error();
		}
	}

	public static void runClient(String[] args) throws IOException{
		switch (args.length) {
			case 2:
				new Client(Config.HOST, Config.PORT).start();
			case 4:
				try {
					new Client(args[2], Integer.parseInt(args[3])).start();
				} catch (NativeMethodException e) { error(); }
			default:
				error();
		}
	}
	public static void run(String[] args) throws IOException {
		switch (args[1]){
			case "server":
				runServer(args);
			case "client":
				runClient(args);
			default:
				error();
		}
	}

	public static void main(String[] args) {
		try {
			if (args.length <2 || args.length >4)
				error();

			switch (args[0]){
				case "run":
					run(args);
			}

		} catch (ConnectException e){
			System.err.println("Server is offline");
		}
		catch (FileNotFoundException e){
			System.err.println(e.getMessage());
		}
		catch (Exception e){
			e.printStackTrace(System.err);
		}
		finally {
			new Scanner(System.in).next();
		}
	}
}