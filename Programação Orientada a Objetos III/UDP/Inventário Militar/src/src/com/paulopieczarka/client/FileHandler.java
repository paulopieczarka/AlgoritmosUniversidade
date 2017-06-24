package com.paulopieczarka.client;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStreamReader;

public class FileHandler 
{
	public static String getFileContent(File file)
	{
		BufferedReader bufferReader = null;
		FileInputStream fileReader = null;
		InputStreamReader inputStreamReader = null;
		String content = "";
		
		try
		{
			fileReader = new FileInputStream(file);
			inputStreamReader = new InputStreamReader(fileReader, "UTF-8");
			bufferReader = new BufferedReader(inputStreamReader);
			
			String line = "";
			while((line = bufferReader.readLine()) != null){
				content += line;
			}
			
			// Shit cleaner.
			content = content.replace("\t", "");
			content = content.replace("  ", "");
			
			fileReader.close();
			bufferReader.close();
		}
		catch(IOException e) {
			e.printStackTrace();
		}
		
		return content;
	}
}
