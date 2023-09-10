package application.xml.server;

import application.objectstream.server.Server;
import application.objectstream.server.ServerThread;
import application.xml.schema.generator.XsdGenerator;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class XmlServer extends Server {

	ArrayList<XmlServerThread> userThreads;

	public XmlServer(int PORT) {
		super(PORT);
		userThreads = new ArrayList<>();
	}

	public boolean removeThread(XmlServerThread st) {
		return userThreads.remove(st);
	}

	@Override
	public void run() {
		try (ServerSocket server = new ServerSocket(port)) {
			isRunning = true;
			while (isRunning) {
				try {
					Socket socket = server.accept();
					XmlServerThread st = new XmlServerThread(this, socket);
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
