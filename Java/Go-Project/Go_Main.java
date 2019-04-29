/*
 * Created on Jan 31, 2004
 *
 * To change the template for this generated file go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */

/**
 * @author tristan
 *
 * To change the template for this generated type comment go to
 * Window - Preferences - Java - Code Generation - Code and Comments
 */

import java.applet.*;
import java.awt.*;
import java.net.*;
import java.io.*;

public class Go_Main extends Applet{
	private Image bimg, pwhite, pblack; 
	private Board b;
	private int sizepiece=16;
	private Player p1, p2, current_player;
	int turn;
	GameFrame f;
	boolean usingP2P = false;
	Socket s;
	//DataInputStream ds;
	PrintStream os;
	boolean goFirst = true;
	boolean myTurn = false;
	
	public void init ()
	{
		turn = 0;
		
		new P2PServerManager(this).start();
		System.out.println("Started Server!");
		
		GametypeDialog gametype = new GametypeDialog();
		gametype.show();
		
		if (gametype.getType() == 0)
		{
			System.out.println("Local game");
			Setup gameSetup = new Setup();
			gameSetup.show();
			p1 = new Player (gameSetup.getPlayerOne());
			p2 = new Player (gameSetup.getPlayerTwo());
			myTurn = true;
		}
		else
		{
			System.out.println("P2P game");
			P2PSetup gameSetup = new P2PSetup();
			gameSetup.show();
			p1 = new Player (gameSetup.getPlayer());
			p2 = new Player ("Remote");	
			usingP2P = true;
			
			//Socket s;
			//DataInputStream ds;
					//PrintStream ps;
			try 
			{	
				System.out.println("Starting client");
				s = new Socket(gameSetup.getHost(),16180);
				os = new PrintStream(new BufferedOutputStream(s.getOutputStream(), 1024), false);
				System.out.println("Done starting client");
				//os.println("m:"+30+":"+10);
				//os.flush();
				if (goFirst)
				{
					myTurn = true;
				}
				/*PrintStream os = new PrintStream(new BufferedOutputStream(s.getOutputStream(), 1024), false);
				os.println("m:55:55");
				os.flush();*/
			}
			catch(Exception e)
			{
				System.out.print("Could not connect!" + e);		
			}
		}
		
		
		current_player = p1;
		
		setBackground (Color.black);
		bimg = getImage (getCodeBase (), "boardgrid.jpg");
		pwhite = getImage (getCodeBase (), "white.png");
		pblack = getImage (getCodeBase (), "black.png");
		b = new Board (bimg, pwhite, pblack, p1, p2);
		
		f = new GameFrame(this, 415,475);
		resize (400,400);
	}

	public void paint (Graphics g)
	{
		b.paint (g, this);		
	}
	
	public void update (Graphics g)
	{
		paint (g);
	}	
	
	public boolean mouseDown (Event e, int x, int y)
	{
		if (myTurn)
		{
		
		Move m, mo;
		
		// normalize mouse click position on board
		int xTest = (x/19) ;
		int yTest = (y/19) ;
		
		double xx = xTest + .5;
		double yy = yTest + .5;
		 
		double xTest2 = ((double)x/19);
		if (xTest2 > xx)
		{
			x = (x/19)*19 + 19;
		}
		else
		{
			x = (x/19)*19;
		}
		double yTest2 = ((double)y/19);
		if (yTest2 > yy)
		{
			y =  (y/19)*19 + 19;
		}
		else
		{
			y = (y/19)*19;
		}
		
		System.out.println("Mouse After: " + x + " " + y);
		
		if (usingP2P)
		{
			os.println("m:"+x+":"+y);
			os.flush();
			myTurn = false;
		}
		
		if (e.shiftDown ())
		{
			/*
			if (turn == 0)
			{	
				mo = p2.removeMove (b);
				turn = 1;
			}
			else
			{	
				mo = p1.removeMove (b);
				turn = 0;
			}
			System.out.println ("REMOVE:" + mo.getX () + " " + mo.getY ());
			*/
			
			b.Undo ();
			
			if (current_player == p1)
			{
				turn = 1;
				current_player = p2;
			}
			else
			{
				turn = 0;
				current_player = p1;
			}
		}
		else if (e.controlDown())
		{
			current_player.setPass (true);
			
			if (p1.getPass () == true && p2.getPass () == true)
				Score ();	
			
			if (current_player == p1)
			{	
				turn = 1;
				current_player = p2;
			}
			else
			{
				turn = 0;
				current_player = p1;
			}
			
			b.SaveState ();
		}
		else
		{
			Piece p = new Piece (x-(sizepiece)/2, y-(sizepiece)/2, turn);
			m = new Move (x-(sizepiece)/2, y-(sizepiece)/2);
		
			if (b.Play (p))
			{		
				if (current_player == p1)
				{
					p1.addMove();
					turn = 1;
					current_player = p2;
				}
				else
				{
					p2.addMove();
					turn = 0;
					current_player = p1;
				}
			}
		}
		
		repaint ();
		}

		return true;
	}
	
	public boolean mouseDownServer (int x, int y)
	{
		myTurn = true;
		Move m, mo;
		
		// normalize mouse click position on board
		int xTest = (x/19) ;
		int yTest = (y/19) ;
		
		double xx = xTest + .5;
		double yy = yTest + .5;
		 
		double xTest2 = ((double)x/19);
		if (xTest2 > xx)
		{
			x = (x/19)*19 + 19;
		}
		else
		{
			x = (x/19)*19;
		}
		double yTest2 = ((double)y/19);
		if (yTest2 > yy)
		{
			y =  (y/19)*19 + 19;
		}
		else
		{
			y = (y/19)*19;
		}
		
		System.out.println("Mouse After: " + x + " " + y);
		
		
		{
			Piece p = new Piece (x-(sizepiece)/2, y-(sizepiece)/2, turn);
			m = new Move (x-(sizepiece)/2, y-(sizepiece)/2);
		
			if (b.Play (p))
			{		
				if (current_player == p1)
				{
					p1.addMove();
					turn = 1;
					current_player = p2;
				}
				else
				{
					p2.addMove();
					turn = 0;
					current_player = p1;
				}
			}
		}
		
		repaint ();

		return true;
	}	
	
	public void Score ()
	{
		b.Score (p1, p2);
		
		if (p1.getScore() > p2.getScore())
		{
			new WinnerDialog(p1.getName(), p1.getScore(), p2.getScore()).show();
		}
		else if (p1.getScore() < p2.getScore())
		{
			new WinnerDialog(p2.getName(), p1.getScore(), p2.getScore()).show();
		}
		else
		{
			new WinnerDialog("No One", p1.getScore(), p2.getScore()).show();
		}
		
		System.out.println ("Player 1 Score: " + p1.getScore ());
		System.out.println ("Player 2 Score: " + p2.getScore ());
	}
	
	public void newGame()
	{
	}

	public void restartGame()
	{
	}

	public void loadGame()
	{
	}

	public void saveGame()
	{
	}

	public void exitGame()
	{
	}

	public void Undo()
	{
		b.Undo ();
		System.out.println ("UNDO");
		if (current_player == p1)
		{
			turn = 1;
			current_player = p2;
		}
		else
		{
			turn = 0;
			current_player = p1;
		}
		
		repaint ();
	}

	public void Redo()
	{
		b.Redo ();
		
		if (current_player == p1)
		{
			turn = 1;
			current_player = p2;
		}
		else
		{
			turn = 0;
			current_player = p1;
		}
		
		repaint ();
	}
}
