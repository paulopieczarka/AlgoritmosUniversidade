package evil;

import java.nio.ByteBuffer;
import java.util.Arrays;

public class BY {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		
		byte[] bytes = ByteBuffer.allocate(2).putShort((short)127).array();
		System.out.println(Arrays.toString(bytes));
		
		bytes = ByteBuffer.allocate(2).putShort((short)256).array();
		System.out.println(Arrays.toString(bytes));
		
		bytes = ByteBuffer.allocate(2).putShort((short)512).array();
		System.out.println(Arrays.toString(bytes));
		
		bytes = ByteBuffer.allocate(2).putShort((short)1024).array();
		System.out.println(Arrays.toString(bytes));
		
		System.out.println(ByteBuffer.wrap(bytes).getShort());
	}

}
