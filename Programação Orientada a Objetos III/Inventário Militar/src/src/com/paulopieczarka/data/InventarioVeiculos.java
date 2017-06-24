package com.paulopieczarka.data;

import java.util.ArrayList;
import java.util.HashMap;

import com.paulopieczarka.client.Parser;

public class InventarioVeiculos extends Inventario
{
	private ArrayList<Veiculo> veiculoList;
	
	public InventarioVeiculos(String header, String version, String type, String charset) 
	{
		super(header, version, type, charset);
		this.veiculoList = new ArrayList<>();
	}
	
	public void add(Veiculo v)
	{
		if(v == null){
			return;
		}
		
		this.veiculoList.add(v);
	}
	
	public Veiculo get(int index)
	{
		if(index < 0 || index >= this.veiculoList.size()){
			System.err.println("Index inválido.");
			return null;
		}
		
		return this.veiculoList.get(index);
	}
	
	public void addAll(ArrayList<String> list)
	{
		System.out.println("Foram adicionandos ("+list.size()+") veiculos.");
		
		HashMap<String, String> attrs = new HashMap<>();
		Parser parser = new Parser();
		
		//TODO: Make this better.
		
		String line;
		String[] lineParts;
		Veiculo veiculo = null;
		
		for(int i=0; i < list.size(); i++)
		{
			attrs = new HashMap<>();
			
			line = list.get(i);
			line = line.replace("<veiculo ", "");
			lineParts = line.split("=\"(.+?)\"");
			ArrayList<String> values = parser.parse("\"(.+?)\"", line);
			for(int j=0; j < values.size(); j++){
				attrs.put(lineParts[j].replace(" ", ""), values.get(j));
			}
			
			if(attrs.get("tipo").equalsIgnoreCase(Veiculo.AERONAVE))
			{
				veiculo = new VeiculoAeronave(
						attrs.get("subtipo"),
						attrs.get("classe"),
						attrs.get("modelo")
					);
			}
			else if(attrs.get("tipo").equalsIgnoreCase(Veiculo.EMBARCACAO))
			{
				veiculo = new VeiculoEmbarcacao(
						attrs.get("subtipo"),
						attrs.get("classe"),
						attrs.get("modelo")
					);
			}
			else if(attrs.get("tipo").equalsIgnoreCase(Veiculo.TERRESTRE))
			{
				veiculo = new VeiculoTerrestre(
						attrs.get("subtipo"),
						attrs.get("classe"),
						attrs.get("modelo")
					);
			}
			else
			{
				System.out.println("Classe ("+attrs.get("tipo")+") não encontrada!");
			}
			
			attrs.remove("tipo");
			attrs.remove("subtipo");
			attrs.remove("classe");
			attrs.remove("modelo");
			veiculo.setPropriedades(attrs);
			add(veiculo);
		}
	}

	public ArrayList<Veiculo> getList() 
	{
		return this.veiculoList;
	}
}
