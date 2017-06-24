package com.paulopieczarka.data;

public class VeiculoTerrestre extends Veiculo
{
	public VeiculoTerrestre(String subtipo, String classe, String modelo) 
	{
		super(TERRESTRE, subtipo, classe, modelo);
	}
	
	@Override
	public String toString() 
	{
		String info = super.toString();
		info += propsToString();
		return info;
	}
}
