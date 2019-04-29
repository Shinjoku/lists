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

public class GametypeDialog extends Dialog
{
	CheckboxGroup choice = new CheckboxGroup();
	Checkbox local = new Checkbox("Local ", choice, true);
	Checkbox p2p = new Checkbox("P2P", choice, false);
	Button b = new Button("OK");
	
	public GametypeDialog()
	{
		super(new Frame("Game Type"), "Game Type", true);
		
		setLayout(new FlowLayout());
		add(local);
		add(p2p);
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
	
	int getType()
	{
		if (local.getState())
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
}