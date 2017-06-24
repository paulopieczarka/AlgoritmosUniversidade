package com.paulopieczarka.client;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import com.paulopieczarka.data.InventarioVeiculos;

public class Parser 
{
	private String content;
	
	public Parser(){}
	
	public Parser(String str)
	{
		this.setContent(str);
	}
	
	public InventarioVeiculos parseInventario()
	{
		String header = parseTag("header", getContent());
		String metadata = parseTag("metadata", getContent());
		String metaVersion = parseTag("version", metadata);
		String metaType = parseTag("type", metadata);
		String metaCoding = parseTag("coding", metadata);
		String data = parseTag("data", getContent());
		
		// Create inventario de veiculos.
		InventarioVeiculos inv = new InventarioVeiculos(header, metaVersion, metaType, metaCoding);
		inv.addAll(parseList(data));
		
		return inv;
	}
	
	public String parseTag(String tag, String text)
	{
		Pattern pattern = Pattern.compile("<"+tag+">(.+?)</"+tag+">");
		Matcher matchs = pattern.matcher(text);
		
		String textFound = "";
		while(matchs.find()){
			textFound = matchs.group(1);
		}
		
		return textFound;
	}
	
	public ArrayList<String> parse(String regex, String text)
	{
		Pattern pattern = Pattern.compile(regex);
		Matcher matchs = pattern.matcher(text);
		
		ArrayList<String> results = new ArrayList<>();
		while(matchs.find()){
			results.add(matchs.group(1));
		}
		
		return results;
	}
	
	public ArrayList<String> parseList(String text)
	{
		ArrayList<String> objs = new ArrayList<>();
		
		String[] lines = text.split(">");
		objs.addAll(Arrays.asList(lines));
		
		return objs;
	}
	
	public void setContent(String content)
	{
		this.content = content;
	}
	
	public String getContent()
	{
		return this.content;
	}
}
