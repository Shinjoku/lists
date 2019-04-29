/*
 * Created on Apr 24, 2004
 *
 * To change the template for this generated file go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

/**
 * @author maserding
 *
 * To change the template for this generated type comment go to
 * Window&gt;Preferences&gt;Java&gt;Code Generation&gt;Code and Comments
 */

import java.applet.*;
import java.awt.*;

public class GameFrame extends Frame
{
	protected Panel p;
	protected MenuBar menubar;
	protected MenuItem newGameItem, restartGameItem, loadGameItem, saveGameItem, exitGameItem;
	protected MenuItem undoItem, redoItem;
	protected Menu m1, m2;
	protected Go_Main gm;
	protected int width, height;
	
	// create a frame to hold the applet, and also to create a menu
	public GameFrame(Applet app, int width, int height)
	{
		super("jGo");
		
		this.width = width;
		this.height = height;
		gm = (Go_Main)app;
		
		resize(width, height);
		setResizable(false);
		menubar = new MenuBar();
		
		m1 = new Menu("Game");
		newGameItem = new MenuItem("New Game");
		restartGameItem = new MenuItem("Restart Game");
		loadGameItem = new MenuItem("Load Game");
		saveGameItem = new MenuItem("Save Game");
		exitGameItem = new MenuItem("Exit Game");
	    m1.add(newGameItem);
		m1.add(restartGameItem);
		m1.add(loadGameItem);
		m1.add(saveGameItem);
		m1.add(exitGameItem);
	    menubar.add(m1);
	    
	    m2 = new Menu("Edit");
	    undoItem = new MenuItem("Undo");
	    redoItem = new MenuItem("Redo");
	    m2.add(undoItem);
	    m2.add(redoItem);
	    menubar.add(m2);
	    
		setMenuBar(menubar);
		
		
		p = new Panel();
		p.setLayout(new FlowLayout(FlowLayout.CENTER));
		p.add(app);
		setLayout(new BorderLayout());
		add("Center",p);
		
		show();	
	}
	
	// check menu events
	public boolean action(Event e, Object o)
	{
		if (e.target instanceof MenuItem)
		{
			String s= (String)o;
			
			if (e.target == newGameItem)
			{
				gm.newGame();
			}
			else if (e.target == restartGameItem)
			{
				gm.restartGame();
			}
			else if (e.target == loadGameItem)
			{
				gm.loadGame();
			}
			else if (e.target == saveGameItem)
			{
				gm.saveGame();
			}
			else if (e.target == exitGameItem)
			{
				hide();
				gm.stop();
				gm.destroy();
				gm.exitGame();
			}
			else if (e.target == undoItem)
			{
				gm.Undo();
			}
			else if (e.target == redoItem)
			{
				gm.Redo();
			}
			
			return true;
		}
		
		return false;
	}

}
