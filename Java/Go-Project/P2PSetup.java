/*
 * Created on Feb 8, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

/**
 * @author Administrator
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

//import java.applet.*;
import java.awt.*;

public class P2PSetup extends Dialog
{
	
	Button b = new Button("Start Game");
	TextField textHost = new TextField("Host");
	TextField textPlayer = new TextField("Player Name");
	
	public P2PSetup()
	{
		super(new Frame("Setup P2P"), "Setup P2P", true);
	
		setLayout(new FlowLayout());
		add(textHost);
		add(textPlayer);
		add(b);
		pack();
	}
	
	public boolean action(Event e, Object o)
	{
		if (e.target instanceof Button)
		{
			hide();
			dispose();
			return true;
		}
		else return false;
	}
	
	public String getHost()
	{
		return textHost.getText();
	}
	
	public String getPlayer()
	{
		return textPlayer.getText();
	}
}
