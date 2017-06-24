package com.paulopieczarka.data;

public class VeiculoEmbarcacao extends Veiculo
{
	public VeiculoEmbarcacao(String subtipo, String classe, String modelo) 
	{
		super(EMBARCACAO, subtipo, classe, modelo);
	}
	
	@Override
	public String toString() 
	{
		String info = super.toString();
		info += propsToString();
		return info;
	}
}
