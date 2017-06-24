package com.paulopieczarka.app;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ItemEvent;
import java.awt.event.ItemListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.util.ArrayList;

import javax.swing.BorderFactory;
import javax.swing.DefaultListModel;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ListSelectionModel;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

import com.paulopieczarka.data.InventarioVeiculos;

public class InventarioView extends JPanel
{
	private static final long serialVersionUID = 1L;
	
	private JTextField tfSearch;
	private JComboBox<String> cbTipo;
	private JComboBox<String> cbSubTipo;
	private JList<String> lSearchResult;
	private JTextArea taListItemView;
	private JButton btClean;
	
	private String filterTipo = "Todos os tipos";
	private String filterSubTipo = "Todos os subtipos";
	private InventarioVeiculos inventario;
	
	public InventarioView() 
	{
		setLayout(new BorderLayout());
		
		JPanel header = new JPanel(new GridLayout(1, 4, 8, 8));
		header.setBorder(BorderFactory.createTitledBorder(" Buscar "));
		
		JPanel main = new JPanel(new BorderLayout());
		
		tfSearch = new JTextField();
		tfSearch.addKeyListener(new KeyListener() {
			@Override public void keyReleased(KeyEvent e) 
			{
				DefaultListModel<String> allList = getInvList();
				DefaultListModel<String> filteredList = new DefaultListModel<>();
				for(int i=0; i < allList.size(); i++)
				{
					lSearchResult.clearSelection();
					String model = allList.get(i).toLowerCase();
					if(model.startsWith(tfSearch.getText().toLowerCase())){
						filteredList.addElement(allList.get(i));
					}
				}
				
				lSearchResult.setModel(filteredList);
				lSearchResult.setSelectedIndex(0);
			}
			
			@Override public void keyPressed(KeyEvent e) { }
			@Override public void keyTyped(KeyEvent e) { }
		});
		
		cbTipo = new JComboBox<>();
		cbTipo.addItemListener(new ItemListener() {
			@Override public void itemStateChanged(ItemEvent e) {
				filterTipo = (String)cbTipo.getSelectedItem();
				lSearchResult.setModel(getInvList());
			}
		});
		
		cbSubTipo = new JComboBox<>();
		cbSubTipo.addItemListener(new ItemListener() {
			@Override public void itemStateChanged(ItemEvent e) {
				filterSubTipo = (String)cbSubTipo.getSelectedItem();
				lSearchResult.setModel(getInvList());
			}
		});
		
		btClean = new JButton("Limpar");
		btClean.addActionListener(new ActionListener() {
			@Override public void actionPerformed(ActionEvent e)
			{
				cbTipo.setSelectedIndex(0);
				cbSubTipo.setSelectedIndex(0);
				tfSearch.setText("");
			}
		});
		
		header.add(tfSearch);
		header.add(cbTipo);
		header.add(cbSubTipo);
		header.add(btClean);
		
		lSearchResult = new JList<>();
		lSearchResult.setPreferredSize(new Dimension(200, 0));
		lSearchResult.setBorder(BorderFactory.createTitledBorder(" Veículos "));
		lSearchResult.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		lSearchResult.addListSelectionListener(new ListSelectionListener() {
			@Override public void valueChanged(ListSelectionEvent e) 
			{
				String model = lSearchResult.getSelectedValue();
				int itemIndex = getInvList().indexOf(model);
				if(itemIndex > -1){
					taListItemView.setText(inventario.get(itemIndex).toString());
				}
			}
		});
		
		taListItemView = new JTextArea("Selecione um item!");
		taListItemView.setBorder(BorderFactory.createTitledBorder(" Informações "));
		
		main.add(new JScrollPane(lSearchResult), BorderLayout.WEST);
		main.add(new JScrollPane(taListItemView));
		
		add(header, BorderLayout.NORTH);
		add(main);
	}
	
	public void setInventario(InventarioVeiculos inventario)
	{
		this.inventario = inventario;
		lSearchResult.setModel(getInvList());
		populateCbTipo();
		populateCbSubTipo();
	}
	
	protected DefaultListModel<String> getInvList()
	{
		DefaultListModel<String> listModel = new DefaultListModel<>();
		for(int i=0; i < inventario.getList().size(); i++)
		{
			String veiName = inventario.get(i).getModelo();
			String veiTipo = inventario.get(i).getTipo();
			String veiSubTipo = inventario.get(i).getSubtipo();
			
			if(!filterTipo.equals("Todos os tipos"))
			{
				if(!filterTipo.equals(veiTipo)){
					continue;
				}
			}
			
			if(!filterSubTipo.equals("Todos os subtipos"))
			{
				if(!filterSubTipo.equals(veiSubTipo)){
					continue;
				}
			}
			
			listModel.addElement(veiName);
		}
			
		return listModel;
	}
	
	protected void populateCbTipo()
	{
		cbTipo.addItem(filterTipo);
		
		ArrayList<String> items = new ArrayList<>();
		for(int i=0; i < inventario.getList().size(); i++)
		{
			String veiName = inventario.get(i).getTipo();
			if(!items.contains(veiName)){
				cbTipo.addItem(veiName);
				items.add(veiName);
			}
		}
	}
	
	protected void populateCbSubTipo()
	{
		cbSubTipo.addItem(filterSubTipo);
		
		ArrayList<String> items = new ArrayList<>();
		for(int i=0; i < inventario.getList().size(); i++)
		{
			String veiName = inventario.get(i).getSubtipo();
			if(!items.contains(veiName)){
				cbSubTipo.addItem(veiName);
				items.add(veiName);
			}
		}
	}
}
