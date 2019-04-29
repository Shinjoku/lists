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

public class WinnerDialog extends Dialog
{
	Label textWinner, textScore;
	Button b = new Button("OK");
	
	public WinnerDialog(String playerName, int score1, int score2)
	{
		super(new Frame("Winner!"), "Winner!", true);
		
		textWinner = new Label(playerName + " won!");
		textScore = new Label(score1 + " - "  + score2);
	
		setLayout(new FlowLayout());
		add(textWinner);
		add(textScore);
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
}
