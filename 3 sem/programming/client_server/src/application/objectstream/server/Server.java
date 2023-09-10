package application.objectstream.server;

import java.io.IOException;
import java.net.*;
import java.util.ArrayList;
import java.util.Scanner;


public class Server extends Thread {

	protected final int port;
	protected boolean isRunning = false;

	private ArrayList<ServerThread> userThreads;

	public Server(int PORT) {
		this.port = PORT;
		userThreads = new ArrayList<>();
	}

	public int getPort() {
		return port;
	}

	public boolean removeThread(ServerThread st) {
		return userThreads.remove(st);
	}

	public synchronized void start(boolean waitForTerminate) {
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
					ServerThread st = new ServerThread(this, socket);
					if (st != null) {
						userThreads.add(st);
						st.start();
					}
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void clearUserThreads() {
		for (ServerThread st : userThreads) {
			try {
				st.close();
				System.out.println(st.getClientInetAddress().getHostName());
			} catch (IOException e) {
			}
		}
	}

	public void waitForTerminate() {
		System.out.println("Server started on port: " + port + "\nCtrl+c to terminate");
		Scanner sc = new Scanner(System.in);
		while (sc.hasNextLine()) {
		}
		isRunning = false;
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

