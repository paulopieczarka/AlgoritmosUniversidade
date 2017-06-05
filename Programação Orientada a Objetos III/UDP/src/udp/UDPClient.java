package udp;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPClient 
{
	private DatagramSocket serverSocket;
	private InetAddress host;
	private int port;
	
	public UDPClient(String ip, int port)
	{
		try
		{
			this.port = port;
			host = InetAddress.getByName(ip);
			serverSocket = new DatagramSocket();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
	
	public void sendMsg(String text)
	{
		try
		{
			byte[] sendPacket = Packet.compile(text);
			DatagramPacket packet = new DatagramPacket(sendPacket, sendPacket.length, host, port);
			serverSocket.send(packet);
			//serverSocket.close();
		}
		catch(Exception e){
			e.printStackTrace();
		}
	}
}
