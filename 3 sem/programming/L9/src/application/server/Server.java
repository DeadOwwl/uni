package application.server;

import application.protocol.Config;

import java.io.IOException;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;


public class Server extends Thread {

	private final int port;
	private boolean isRunning = false;

	private static ArrayList<ServerThread> userThreads = new ArrayList<>();

	public Server(int PORT){
		this.port = PORT;
	}

	public int getPort() {
		return port;
	}

	protected boolean removeThread(ServerThread st){
		return userThreads.remove(st);
	}

	@Override
	public synchronized void start() {
		super.start();
	}

	public synchronized void start(boolean waitForTerminate){
		start();
		if (waitForTerminate)
			waitForTerminate();
	}

	@Override
	public void run() {
		try (ServerSocket server = new ServerSocket(port)) {
			isRunning = true;
			while (isRunning) {
				try {
					Socket socket = server.accept();
					ServerThread st = new ServerThread(this,socket);
					userThreads.add(st);
					st.start();
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void clearUserThreads(){
		for (ServerThread st: userThreads){
			try {
				st.close();
				System.out.println(st.getClientInetAddress().getHostName());
			}
			catch (IOException e){}
		}
	}

	public void waitForTerminate() {
		System.out.println("Server started on port: " + port + "\nCtrl+c to terminate");
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextLine()){ }
		isRunning = false;

	}

	public static void main(String[] args) {
		Server s = new Server(Config.PORT);
		s.start(true);
	}

	@Override
	public void interrupt() {
		super.interrupt();
		isRunning = false;
		clearUserThreads();
	}

	@Override
	protected void finalize() throws Throwable {
		super.finalize();
		clearUserThreads();
	}
}

