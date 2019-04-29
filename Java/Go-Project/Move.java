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
public class Move {
	private int x, y;
	
	Move (int x, int y)
	{
		this.x = x;
		this.y = y;
	}
	
	public int getX ()
	{
		return x;
	}
	
	public int getY ()
	{
		return y;
	}
	
	public void setX (int xin)
	{
		x = xin;
	}
	
	public void setY (int yin)
	{
		y = yin;
	}
	
}
