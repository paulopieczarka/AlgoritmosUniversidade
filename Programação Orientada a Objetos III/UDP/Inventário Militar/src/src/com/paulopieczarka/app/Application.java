package com.paulopieczarka.app;

import java.awt.Dimension;
import java.io.File;

import javax.swing.JFrame;
import javax.swing.JOptionPane;

import com.paulopieczarka.client.Parser;
import com.paulopieczarka.client.ParserFile;
import com.paulopieczarka.data.InventarioVeiculos;

public class Application extends JFrame implements Runnable
{
	private static final long serialVersionUID = 1L;
	
	private InventarioView invView;
	
	public Application() 
	{
		setTitle("Inventário Militar");
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setSize(new Dimension(640, 480));
		setLocationRelativeTo(null);
		
		invView = new InventarioView();
		setContentPane(invView);
	}
	
	public void start() 
	{
		setVisible(true);
		
		Thread loader = new Thread(this);
		loader.start();
	}

	@Override
	public void run() 
	{
		String filePath = JOptionPane.showInputDialog(
				"Caminho para o arquivo:", 
				"C:\\Users\\paulo\\Desktop\\inventarioFABrasil.txt"
			);
		
		File file = new File(filePath);
		if(file.exists())
		{
			System.out.print("Getting file contents..");
			
			Parser p = new ParserFile(file);
			InventarioVeiculos inv = p.parseInventario();
			invView.setInventario(inv);
			
			System.out.println("Done!");
		}
		else
		{
			JOptionPane.showMessageDialog(this, "Arquivo não encontrado!");
			run();
		}
	}
}
