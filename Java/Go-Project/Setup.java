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

public class Setup extends Dialog
{
	
	Button b = new Button("Start Game");
	TextField textPlayerOne = new TextField("Player One");
	TextField textPlayerTwo = new TextField("Player Two");
	
	public Setup()
	{
		super(new Frame("Setup Local"), "Setup Local", true);
	
		setLayout(new FlowLayout());
		add(textPlayerOne);
		add(textPlayerTwo);
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
	
	public String getPlayerOne()
	{
		return textPlayerOne.getText();
	}
	
	public String getPlayerTwo()
	{
		return textPlayerTwo.getText();
	}
}

