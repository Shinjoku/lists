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

import java.net.*;
import java.io.*;

public class ServerManager
 {
	
	
 	public static  void main(String argss[])
 	{
		DataInputStream dis = null;
		PrintStream ps= null;
		
 		System.out.println("The server is started");
 		ServerSocket servSock = null;
 		try
 		{
 			servSock = new ServerSocket(2357);
 		}
 		catch (Exception e)
 		{
 			System.out.println("Tried to setup server sock, but failed!");
 			System.exit(1);
 		}
 		
 		Socket sock = null;
 		try
 		{
 			sock = servSock.accept();
 			System.out.println("Got connection");
 			dis = new DataInputStream( new BufferedInputStream(sock.getInputStream()));
 			ps = new PrintStream(new BufferedOutputStream(sock.getOutputStream(), 1024), false);
 		}
 		catch (Exception e)
 		{
 			System.out.println("Could not get connection");
 			System.exit(1);
 		}
 		
 		String inputLine="";
 		while (!inputLine.startsWith("bye"))
 		{
 			//inputLine = dis.readLine();
 			System.out.println("Got: " + inputLine);
 			if(inputLine.startsWith("request"))
 			{
 				ps.println("none");
 			}
 		}
 		
 		try 
 		{
 			//os.close();
 			//is.close();
 			sock.close();
 		}
 		catch (Exception e)
 		{
 			
 		}
 		
 		System.exit(1);
 	}
}
