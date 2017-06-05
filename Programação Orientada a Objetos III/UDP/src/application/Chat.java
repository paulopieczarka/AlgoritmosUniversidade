package application;

import javafx.application.Platform;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.TitledPane;
import javafx.scene.control.ToolBar;
import javafx.scene.layout.BorderPane;
import udp.UDPClient;
import udp.UDPServer;

public class Chat extends BorderPane
{
	private static TextArea logArea;
	
	public static Label lbServerStats;
	
	public Chat() 
	{
		UDPServer server = new UDPServer(62965);
		
		//Tool bar
		lbServerStats = new Label("Server Offline..");
		
		Button btServer = new Button("Start Server");
		btServer.setOnAction(new EventHandler<ActionEvent>() {
			@Override public void handle(ActionEvent event) 
			{
				btServer.setDisable(true);
				server.start();
			}
		});
		
		ToolBar navbar = new ToolBar();
		navbar.getStyleClass().add("fluent-nav");
		navbar.getItems().add(btServer);
		navbar.getItems().add(lbServerStats);
		
		// Message
		TextArea msgArea = new TextArea();
		BorderPane chatPane = new BorderPane(msgArea);
		BorderPane.setMargin(msgArea, new Insets(0, 0, 16, 0));
		TitledPane chatBorder = new TitledPane("Chat", chatPane);
		chatBorder.setCollapsible(false);
		
		TextField tfIp = new TextField("127.0.0.1:62961");
		BorderPane.setMargin(tfIp, new Insets(0, 16, 0, 0));
		Button btSend = new Button("Send");
		btSend.setOnAction(new EventHandler<ActionEvent>() {
			@Override public void handle(ActionEvent event) 
			{
				String rawIP = tfIp.getText();
				String ip = rawIP.split(":")[0];
				int port = Integer.parseInt(rawIP.split(":")[1]);
				
				UDPClient client = new UDPClient(ip, port);
				client.sendMsg(msgArea.getText());
				
				log("Sending message to "+ip+" on "+port+".");
				msgArea.setText("");
			}
		});
		
		BorderPane bpFields = new BorderPane(tfIp);
		bpFields.setRight(btSend);
		chatPane.setBottom(bpFields);
		
		// Log
		logArea = new TextArea();
		logArea.setEditable(false);
		
		TitledPane logBorder = new TitledPane("Log", logArea);
		logBorder.setCollapsible(false);
		
		// Main
		BorderPane main = new BorderPane();
		main.setTop(navbar);
		main.setCenter(chatBorder);
		main.setBottom(logBorder);
		setCenter(main);
	}
	
	public static void log(String msg)
	{
		Platform.runLater(new Runnable() {
			@Override public void run() {
				logArea.appendText("[LOG] "+msg+"\n");
			}
		});
	}
}
