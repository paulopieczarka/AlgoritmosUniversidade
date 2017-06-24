package com.paulopieczarka.data;

import java.util.HashMap;

public class Veiculo 
{
	public static final String AERONAVE = "aeronave";
	public static final String EMBARCACAO = "embarcação";
	public static final String TERRESTRE = "terrestre";
	
	private String tipo;
	private String subtipo;
	private String classe;
	private String modelo;
	
	private int quantidade;
	
	private HashMap<String, String> propriedades;
	
	public Veiculo(String tipo, String subtipo, String classe, String modelo)
	{
		this.tipo = tipo;
		this.subtipo = subtipo;
		this.classe = classe;
		this.modelo = modelo;
		this.propriedades = new HashMap<>();
	}
	
	public String getTipo()
	{
		return this.tipo;
	}
	
	public String getSubtipo()
	{
		return this.subtipo;
	}
	
	public String getClasse()
	{
		return this.classe;
	}
	
	public String getModelo()
	{
		return this.modelo;
	}
	
	public int getQuantidade()
	{
		return this.quantidade;
	}
	
	public void setPropriedades(HashMap<String, String> props)
	{
		this.quantidade = Integer.parseInt(props.get("quantidade"));
		props.remove("quantidade");
		this.propriedades = props;
	}
	
	public HashMap<String, String> getProps()
	{
		return this.propriedades;
	}
	
	@Override
	public String toString() 
	{
		String info = "Model: "+modelo+"\n\n";
		info += "Tipo: "+tipo+"\n";
		info += "Subtipo: "+subtipo+"\n";
		info += "Classe: "+classe+"\n";
		info += "Quantidade: "+quantidade+"\n";
		
		return info;
	}
	
	protected String propsToString()
	{
		String info = "\nPropriedades:\n";
		for(String key : propriedades.keySet()){
			info += " - "+key+": "+propriedades.get(key)+"\n";
		}
		
		return info;
	}
}
