package udp;

import java.io.ByteArrayOutputStream;
import java.nio.ByteBuffer;
import java.util.Arrays;

import application.Chat;

public class Packet
{
	private String message;
	
	private int header;
	private int size;
	private int crc;
	
	public Packet(byte[] byteArray) 
	{
		this.header = byteArray[0];
		
		if(this.header == 0x80)
		{
			Chat.log("Packet with invalid header: "+(this.header)+".");
			return;
		}
		
		this.size = byteToInt(Arrays.copyOfRange(byteArray, 1, 3));
		this.crc = byteToInt(Arrays.copyOfRange(byteArray, 3+size, 5+size));
		this.message = new String(new String(Arrays.copyOfRange(byteArray, 3, 3+size)));
	}
	
	public String toString()
	{
		return "["+header+", "+size+", "+message+", "+crc+"]";
	}
	
	public static byte[] compile(String msg)
	{
		byte header = (byte)0x80;
		byte[] message = msg.getBytes();
		byte[] size = allocByte(message.length);
		byte[] crc = allocByte(0);
		byte[] buffer = new byte[message.length];
		
		try
		{
			ByteArrayOutputStream out = new ByteArrayOutputStream();
			out.write(header);
			out.write(size);
			out.write(message);
			out.write(crc);
			out.close();
			
			buffer = out.toByteArray();
		}
		catch(Exception e){
			e.printStackTrace();
		}
		
		return buffer;
	}
	
	public static byte[] allocByte(int value)
	{
		return ByteBuffer.allocate(2).putShort((short)value).array();
	}
	
	public int byteToInt(byte[] bytes)
	{
		return (int)ByteBuffer.wrap(bytes).getShort();
	}
}
