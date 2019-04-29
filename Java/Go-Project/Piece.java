/*
 * Created on Feb 7, 2004
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

public class Piece {
	private int color; // 0 black 1 white
	private int x, y; // position on board
	private int liberties;
	private int checked;
	private boolean bool;
	
	Piece (int x, int y, int c)
	{
		this.x = x; this.y = y;
		color = c;
		liberties = 0;
	}
	
	public void setLiberties (int l)
	{
		liberties = l;
	}
	
	public int getLiberties ()
	{
		return liberties;
	}
	
	public void setChecked (int c)
	{
		checked = c;
	}
	
	public int getChecked ()
	{
		return checked;
	}
	
	public void setBool (boolean c)
	{
		bool = c;
	}
	
	public boolean getBool ()
	{
		return bool;
	}
	
	public void setColor (int color)
	{
		this.color = color;
	}
	
	public void setX (int x)
	{
		this.x = x;
	}
	
	public void setY (int y)
	{
		this.y = y;
	}
	
	
	public int getColor ()
	{
		return color;
	}
	
	public int getX ()
	{
		return x;
	}
	
	public int getY ()
	{
		return y;
	}
	
	public void paint (Graphics g, Applet a, int x, int y, Image p)
	{
		g.drawImage (p, x, y, a);
	}
}
