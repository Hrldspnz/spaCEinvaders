package socket;


import java.net.*;
import java.io.*;

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

       SocketServidor socket = new SocketServidor();
       socket.SocketServidor();
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
                    DatoSocket dato = new DatoSocket("");
                    
                    // Se prepara un flujo de salida de datos, es decir, la clase encargada
                    // de escribir datos en el socket.
                    DataOutputStream bufferSalida =
                            new DataOutputStream (cliente.getOutputStream());
                    System.out.println(bufferSalida);
                    // Se envía el dato.
                    dato.writeObject (bufferSalida);
                    System.out.println ("Servidor Java: Enviado " + dato.leerTXT());
                    
                    // Se prepara el flujo de entrada de datos, es decir, la clase encargada
                    // de leer datos del socket.
                    DataInputStream bufferEntrada =
                            new DataInputStream (cliente.getInputStream());
                    
                    // Se crea un dato a leer y se le dice que se rellene con el flujo de
                    // entrada de datos.
                    DatoSocket aux = new DatoSocket("");
                    aux.readObject (bufferEntrada);
                    aux.escribirTXT(aux.toString());
                    System.out.println ("Servidor java: Recibido " + aux.toString());
                    
                    // Se cierra el socket con el cliente.
                    // La llamada anterior a setSoLinger() hará
                    // que estos cierres esperen a que el cliente retire los datos.
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
