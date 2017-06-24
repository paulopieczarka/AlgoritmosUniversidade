package com.paulopieczarka.client;

import java.io.File;

public class ParserFile extends Parser
{
	private File file;
	
	/**
	 * Create parser object with file contents.
	 * @param file - file to be parsed.
	 * @exception "File not found!" if file is null or does not exist.
	 * @exception "[..] is not a file." if the file is not a file. 
	 **/
	public ParserFile(File file)
	{
		super("");
		
		if(file == null || !file.exists()){
			System.err.println("File not found!");
			return;
		}
		
		if(!file.isFile()){
			System.err.println(file.getName()+" is not a file.");
			return;
		}
		
		//Get file contents.
		String content = FileHandler.getFileContent(file);
		this.setContent(content);
		this.file = file;
	}
	
	public File getFile()
	{
		return this.file;
	}
}
