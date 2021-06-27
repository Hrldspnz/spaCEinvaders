package server;


import java.net.*;
import java.io.*;
import java.util.regex.Pattern;
import socket.DatoSocket;


/**
 * Clase principal que instancia un socket servidor, acepta una conexi�n
 * de un cliente y le env�a un entero y una cadena de caracteres.
 */
public class SocketServidor
{    

    int[] puertos = { 25556,25557,25558,25559};
    public static void main (String [] args)
    {   
        threadServidor cliente1 = new threadServidor();
        Thread cliente1Thread = new Thread(cliente1, "0");
        cliente1Thread.start();
        threadServidor cliente2 = new threadServidor();
        Thread cliente2Thread = new Thread(cliente2, "1");
        cliente2Thread.start();
        //Runnable cliente
        //MontarPuertos();
    }
    
    public static void MontarPuertos(){
        
      
    }
    
     /**
      * Constructor por defecto. Hace todo lo que hace el ejemplo.
      */
    public void SocketServidor(int indice)
    {
        try
        {
            // Se acepata una conexi�n con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            try ( // Se crea un socket servidor atendiendo a un determinado puerto.
            // Por ejemplo, el 25556.
                    ServerSocket socket = new ServerSocket (puertos[indice])) {
                // Se acepata una conexi�n con un cliente. Esta llamada se queda
                // bloqueada hasta que se arranque el cliente.
                System.out.println ("Esperando cliente");
                try (Socket cliente = socket.accept()) {
                    System.out.println ("Conectado con cliente de " + cliente.getInetAddress());
                    
                    // Se hace que el cierre del socket sea "gracioso". Esta llamada s�lo
                    // es necesaria si cerramos el socket inmediatamente despu�s de
                    // enviar los datos (como en este caso).
                    // setSoLinger() a true hace que el cierre del socket espere a que
                    // el cliente lea los datos, hasta un m�ximo de 10 segundos de espera.
                    // Si no ponemos esto, el socket se cierra inmediatamente y si el
                    // cliente no ha tenido tiempo de leerlos, los datos se pierden.
                    cliente.setSoLinger (true, 10);
                    
                    // Se prepara un dato para enviar.
                    
                    DatoSocket Dato = new DatoSocket(indice);
                    
                    BufferedWriter out;
                    out = new BufferedWriter (new OutputStreamWriter(cliente.getOutputStream()));
                    
                    System.out.println(Dato.leerTXT());
                    
                    out.write(Dato.leerTXT()+"\0");
                    out.newLine(); 
                    out.flush();
     
                    BufferedReader in;
                    in = new BufferedReader(new InputStreamReader(cliente.getInputStream()));    
                    java.lang.String info;
                    for(java.lang.Integer i=0; i<58; i++){
                        info = in.readLine();
                        Dato.escribirTXT(info + "\n");
                    }
                   
     
                    cliente.close();
                    
                    // Se cierra el socket encargado de aceptar clientes. Ya no
                    // queremos m�s.
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
       
    
}
