package com.paulopieczarka.data;

import java.util.HashMap;

public class VeiculoAeronave extends Veiculo
{
	private int hardpoints;
	
	public VeiculoAeronave(String subtipo, String classe, String modelo) 
	{
		super(AERONAVE, subtipo, classe, modelo);
		this.hardpoints = 0;
	}
	
	public void setHardpoints(int hardpoints)
	{
		this.hardpoints = hardpoints;
	}
	
	public int getHardpoints()
	{
		return this.hardpoints;
	}
	
	@Override
	public void setPropriedades(HashMap<String, String> props) 
	{
		super.setPropriedades(props);
		
		if(props.containsKey("hardpoints"))
		{
			setHardpoints(Integer.parseInt(props.get("hardpoints")));
			props.remove("hardpoints");
		}
	}
	
	public String toString() 
	{
		String info = super.toString();
		info += "Hardpoints: "+hardpoints+"\n";
		info += propsToString();
		return info;
	}
}
