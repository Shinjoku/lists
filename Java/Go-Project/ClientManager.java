/*
 * Created on Mar 26, 2004
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

import java.awt.*;
import java.util.*;
import java.lang.*;
import java.net.*;
import java.io.*;

public class ClientManager implements Runnable 
{
	Thread kicker = null;
	
	ClientManager()
	{
		kicker = new Thread(this);
		kicker.start();
	}
	
	public void start()
	{
		if(kicker == null)
		{
			kicker = new Thread(this);
		}
	}
	
	public void run()
	{
		//pg303
	}
	
	public void stop()
	{
		kicker = null;
	}
	
	String  getData()
	{
		Socket s;
		DataInputStream ds;
		PrintStream ps;
		String temp = null;
		
		try 
		{
			s = new Socket("diginux.net", 2357);
			ds = new DataInputStream(s.getInputStream());
			ps = new PrintStream(s.getOutputStream());
		} 
		catch (Exception e)
		{
			return null;
		}
		
		String temper;
		return temp;
	}
	

}
