package udp;


import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.SocketException;

import application.Chat;
import javafx.application.Platform;

public class UDPServer implements Runnable
{
	private static volatile boolean running = true;
	
	private DatagramSocket socket;
	
	public UDPServer(int port) 
	{
		try 
		{
			socket = new DatagramSocket(port);
		} 
		catch (SocketException e) {
			e.printStackTrace();
		}
	}
	
	@Override public void run()
	{
		while(running)
		{
			Platform.runLater(new Runnable() {
				@Override public void run() {
					Chat.lbServerStats.setText("Aguardando pacote..");
				}
			});
			
			recive();
		}
	}
	
	public void start()
	{
		Thread thread = new Thread(this);
		thread.start();
	}
	
	public void recive()
	{
		try
		{
			byte[] buffer = new byte[65536];
			DatagramPacket replayPacket = new DatagramPacket(buffer, buffer.length);
			socket.receive(replayPacket);
			
			Packet pkt = new Packet(buffer);
			Chat.log("New packet from "+replayPacket.getAddress()+":\n - PACKET"+pkt.toString());
		}
		catch(Exception e)
		{
			e.printStackTrace();
			Chat.log("------------------ERROR------------------\n"
					+ "O server parou!\n"+e.getMessage()+"\n");
			stop();
		}
	}
	
	public static void stop()
	{
		running = false;
	}
}
