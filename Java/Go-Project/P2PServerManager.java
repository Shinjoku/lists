import java.net.*;
//import java.lang.*;
import java.io.*;
//import java.util.*;
import java.applet.*;
//import java.awt.*;

public class P2PServerManager extends Thread {	
ServerSocket servSock = null;
long lastChange;
long lastWrite;
protected Go_Main gm;
P2PServerManager(Applet app) 
{
	gm = (Go_Main)app;
	
	try 
	{
		servSock = new ServerSocket(16180);
	} 
	catch (Exception e)
	{
		System.out.println("Could not listen on port: " + 16180 + ", " + e);
		System.exit(1);
    }
}

public void run() 
{
	lastChange = System.currentTimeMillis();
	while(servSock != null) 
	{
		Socket sock = null;
		try 
		{
			sock = servSock.accept();
			System.out.println("Got connection");
			System.out.println("Incomng ip: " + sock.getInetAddress());
			if (gm.s == null)
			{
				gm.goFirst = false;
			}
        } 
        catch (Exception e) 
        {
        	System.out.println("Accept failed: " + ", " + e);
            System.exit(1);
        }
        try 
        {
        	DataInputStream is = new DataInputStream(new BufferedInputStream(sock.getInputStream()));
        	PrintStream os = new PrintStream(new BufferedOutputStream(sock.getOutputStream(), 1024), false);
            String inputLine=null, outputLine = "\n";
            String command = "blah";
            String temp;
            
            while( command != null) 
            {
            	//StringTokenizer st1 = null;
            	if (is == null)
            	{
            		System.out.println("Lost 'em");
            		break;
            	}
            	inputLine = is.readLine().trim();
            	
            	if(inputLine != null) 
            	{
            		System.out.println("Got: " + inputLine);
            		if (inputLine.charAt(0) == 'c')
            		{
						String msg = inputLine.substring(inputLine.lastIndexOf(':')+1);
						System.out.println("Got message: " + msg);
            		}
            		else if (inputLine.charAt(0) == 'm')
            		{
            			int x = Integer.parseInt(inputLine.substring(inputLine.indexOf(':')+1,inputLine.lastIndexOf(':')));
            			int y = Integer.parseInt(inputLine.substring(inputLine.lastIndexOf(':')+1));
            			
            			System.out.println("Got coords: " + x + ", " + y);
            			gm.mouseDownServer(x,y);
            		}
            		else if (inputLine.charAt(0) == 'e')
            		{
						String msg = inputLine.substring(inputLine.lastIndexOf(':')+1);
						System.out.println("Exit because: " + msg);
            			command = null;
            		}
            		else
            		{
            			System.out.println("Have no fucking clue what this request is!");
            		}
            	}
            }
			//os.println("shit shit");
            os.close();
            is.close();
            sock.close();
            } 
            catch (Exception e) 
            {
            	e.printStackTrace();
            }
        }
	}
	
	public void finalize() 
	{
		try 
		{
			servSock.close();
		} 
		catch(Exception e)
		{};
		servSock = null;
	}
}