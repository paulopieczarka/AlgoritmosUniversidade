package evil;

import java.util.ArrayList;

import udp.UDPClient;

public class SpamAll 
{
	public static void main(String[] args)
	{
		String ip = "172.18.3.146";
		int port = 62965;
		
		ArrayList<String> shits = new ArrayList<>();
		shits.add("⊂(◉‿◉)つ ~~~~~~> Kirby bitch!");
		shits.add("You won $1,000,000,000,00!!!1 Send money to get it!!");
		shits.add("8====================D~~~~~~~~~~");
		shits.add("8==D 8=====D 8=D 8====D");
		shits.add("(｡◕‿◕｡) CUTE ASS FUCK (｡◕‿◕｡)");
		shits.add("ʕ•ᴥ•ʔ FUCKING BEAR ʕ•ᴥ•ʔ");
		shits.add("( ͡° ͜ʖ ͡°) So did you leave this port open?");
		shits.add("щ（ﾟДﾟщ） WHY YOU DO THIS щ（ﾟДﾟщ）");
		shits.add("t(-_-t) FUCK IT t(-_-t)");
		shits.add("t(-_-t) t(-_-t) t(-_-t) t(-_-t)");
		shits.add("(☞ﾟヮﾟ)☞ (☞ﾟヮﾟ)☞ (☞ﾟヮﾟ)☞ (☞ﾟヮﾟ)☞");
		
		UDPClient client = new UDPClient(ip, port);
		
		//for(int i=0; i < 1000; i++)
			for(String m : shits)
				client.sendMsg(m);
	}
}
