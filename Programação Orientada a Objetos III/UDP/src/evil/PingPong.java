package evil;

import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class PingPong 
{
	public static void main(String[] args)
	{
		try 
		{
			final int port = 62968;
			InetAddress addr = InetAddress.getByName("127.0.0.1");
			
			DatagramSocket dserver = new DatagramSocket(port);
			
			String msg = "Hello! I'm a packet 2!";
			DatagramSocket dclient = new DatagramSocket();
			DatagramPacket pkt = new DatagramPacket(msg.getBytes(), msg.getBytes().length, addr, port);
			dclient.send(pkt);
			
			System.out.println("---> packet");
			
			byte[] bytes = new byte[6500000];
			DatagramPacket rpkt = new DatagramPacket(bytes, bytes.length);
			dserver.receive(rpkt);
			
			System.out.println("<--- packet");
			System.out.println(new String(rpkt.getData()));
		} 
		catch (Exception e){
			e.printStackTrace();
		}
	}
}
