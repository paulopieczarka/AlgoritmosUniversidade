package com.paulopieczarka.data;

public abstract class Inventario 
{
	private String header;
	private String version;
	private String type;
	private String charset;
	
	public Inventario(String header, String version, String type, String charset)
	{
		this.header = header;
		this.version = version;
		this.type = type;
		this.charset = charset;
	}
	
	public String getHeader()
	{
		return this.header;
	}
	
	public String getVersion()
	{
		return this.version;
	}
	
	public String getType()
	{
		return this.type;
	}
	
	public String getCharset()
	{
		return this.charset;
	}
}
