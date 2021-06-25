package server;


import java.net.*;
import java.io.*;
import java.util.Vector;
import java.util.regex.Pattern;
import socket.DatoSocket;

/**
 * Clase principal que instancia un socket servidor, acepta una conexión
 * de un cliente y le envía un entero y una cadena de caracteres.
 */
public class SocketServidor
{    
    public static void main (String [] args)
    {
        // Se instancia la clase principal para que haga todo lo que tiene que
        // hacer el ejemplo
       //SocketServidor socket = new SocketServidor();
       //socket.SocketServidor();        
       Nivel nivel = new Nivel();
       DatoSocket DSocket = new DatoSocket();
       String[] Datos;
       Datos = DSocket.leerTXT().split(" ");
       
       
   
       

       
       
       
    }
    
     /**
      * Constructor por defecto. Hace todo lo que hace el ejemplo.
      */
    public void SocketServidor()
    {
        try
        {
            // Se acepata una conexión con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            try ( // Se crea un socket servidor atendiendo a un determinado puerto.
            // Por ejemplo, el 25557.
                    ServerSocket socket = new ServerSocket (25556)) {
                // Se acepata una conexión con un cliente. Esta llamada se queda
                // bloqueada hasta que se arranque el cliente.
                System.out.println ("Esperando cliente");
                try (Socket cliente = socket.accept()) {
                    System.out.println ("Conectado con cliente de " + cliente.getInetAddress());
                    
                    // Se hace que el cierre del socket sea "gracioso". Esta llamada sólo
                    // es necesaria si cerramos el socket inmediatamente después de
                    // enviar los datos (como en este caso).
                    // setSoLinger() a true hace que el cierre del socket espere a que
                    // el cliente lea los datos, hasta un máximo de 10 segundos de espera.
                    // Si no ponemos esto, el socket se cierra inmediatamente y si el
                    // cliente no ha tenido tiempo de leerlos, los datos se pierden.
                    cliente.setSoLinger (true, 10);
                    
                    // Se prepara un dato para enviar.
                    
                    DatoSocket Dato = new DatoSocket();
                    
                    BufferedWriter out;
                    out = new BufferedWriter (new OutputStreamWriter(cliente.getOutputStream()));
                     
                    out.write(Dato.leerTXT()+"\0");
                    out.newLine(); 
                    out.flush();
     
                    BufferedReader in;
                    in = new BufferedReader(new InputStreamReader(cliente.getInputStream()));    
                    java.lang.String info = in.readLine().toString();
                    Dato.escribirTXT(info);
     
                    cliente.close();
                    
                    // Se cierra el socket encargado de aceptar clientes. Ya no
                    // queremos más.
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
