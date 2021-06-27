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
    public static void main (String [] args)
    {
        // Se instancia la clase principal para que haga todo lo que tiene que
        // hacer el ejemplo
        SocketServidor socket = new SocketServidor();
        Nivel nivel = new Nivel();
        DatoSocket DSocket = new DatoSocket();
        String[] Datos;
        
        java.lang.Integer indice;
        nivel.CreateNewLvl();


        java.lang.Boolean ejecucion = true;
        while(ejecucion == true){
        indice=5;
        DSocket.BorrarDatosE();
        Datos = DSocket.leerTXTRecibido().split(" ");
        //socket.SocketServidor();
        /**
            * Ac? el servidor recorre todos los aliens asignandoles cada posici?n que tienen en el cliente
            */
        
        for(java.lang.Integer i=0; i<5; i++){
                for(java.lang.Integer j=0; j<8; j++){
                    if(i==0){
                        nivel.UpdateAliens(i, j, Integer.parseInt(Datos[indice]), Integer.parseInt(Datos[indice+2]));
                        if(Integer.parseInt(Datos[indice]) == -1 && Integer.parseInt(Datos[indice+2]) == -1){
                            if(nivel.getAlienVida(i, j) == 1){
                                nivel.UpdatePlayer(Integer.parseInt(Datos[3]), Integer.parseInt(Datos[1]), nivel.getPPuntaje()+nivel.getAlientoPuntosMuerte(i, j));
                                nivel.KillAlien(i, j);
                            }
                        }
                    }
                    if(i==1 || i==2){
                        nivel.UpdateAliens(i, j, Integer.parseInt(Datos[indice]), Integer.parseInt(Datos[indice+2]));
                        if(Integer.parseInt(Datos[indice]) == -1 && Integer.parseInt(Datos[indice+2]) == -1){
                            if(nivel.getAlienVida(i, j) == 1){
                                nivel.UpdatePlayer(Integer.parseInt(Datos[3]), Integer.parseInt(Datos[1]), nivel.getPPuntaje()+nivel.getAlientoPuntosMuerte(i, j));
                                nivel.KillAlien(i, j);
                            }
                        }
                    }
                    if(3 <= i){
                        nivel.UpdateAliens(i, j, Integer.parseInt(Datos[indice]), Integer.parseInt(Datos[indice+2]));
                        if(Integer.parseInt(Datos[indice]) == -1 && Integer.parseInt(Datos[indice+2]) == -1){
                            if(nivel.getAlienVida(i, j) == 1){
                                nivel.UpdatePlayer(Integer.parseInt(Datos[3]), Integer.parseInt(Datos[1]), nivel.getPPuntaje()+nivel.getAlientoPuntosMuerte(i, j));
                                nivel.KillAlien(i, j);
                            }
                        }
                    }
                    indice += 4;
                }
            }
        
            nivel.UpdatePlayer(Integer.parseInt(Datos[3]), Integer.parseInt(Datos[1]), nivel.getPPuntaje());
            
            java.lang.Boolean parada = true;
            java.lang.Integer IndiceAux = 0;
            while(parada == true){
                IndiceAux++;
                if(Datos[IndiceAux].equals("HP:")){
                    parada = false;
                }
                
            }
            IndiceAux++;
            
            for(java.lang.Integer i=0; i<4; i++){
                nivel.setBunkers(i, Integer.parseInt(Datos[IndiceAux]));
                IndiceAux+=2;
            }
            
            for(java.lang.Integer i=0; i<4; i++){
                System.out.println("Vida de los bunkers " + String.valueOf(nivel.getBunkerHp(i)));
            }
            
            
            
        
        /**
            * Este for es para visualizar si se asigna la posici?n a los aliens 
            * se puede borrar si quiere
            */
        
        for(java.lang.Integer i=0; i<5; i++){
                for(java.lang.Integer j=0; j<8; j++){
                    if(i==0){
                        System.out.println("Alien en la posici?n: "+ i.toString()+ " " + j.toString()+" posx: " + String.valueOf(nivel.getAlienPosX(i, j))+" posy: " + String.valueOf(nivel.getAlienPosY(i, j)));
                        
                    }
                    if(i==1 || i==2){
                        System.out.println("Alien en la posici?n: "+ i.toString()+ " " + j.toString()+" posx: " + String.valueOf(nivel.getAlienPosX(i, j))+" posy: " + String.valueOf(nivel.getAlienPosY(i, j)));

                    }
                    if(3 <= i){
                        System.out.println("Alien en la posici?n: "+ i.toString()+ " " + j.toString()+" posx: " + String.valueOf(nivel.getAlienPosX(i, j))+" posy: " + String.valueOf(nivel.getAlienPosY(i, j)));

                    }
                }
            }
        
        System.out.println("Posicion x del jugador: " + String.valueOf(nivel.getPlayerposX()) + " vida del jugador: "+ String.valueOf(nivel.getPlayerHp())+ " puntaje del jugador: "+ String.valueOf(nivel.getPPuntaje()));
        
        
        //De aqu? en adelante se escribe los datos contenidos por el servidor al txt de datoE  
        
        DSocket.escribirTXTEnviar("JPosx: " + String.valueOf(nivel.getPlayerposX()) + " " + "JHP: " + String.valueOf(nivel.getPlayerHp()) + " Score: "+ String.valueOf(nivel.getPPuntaje()));
        
        for(java.lang.Integer i=0; i<5; i++){
                for(java.lang.Integer j=0; j<8; j++){
                    if(i==0){
                        DSocket.escribirTXTEnviar("PosX: " + String.valueOf(nivel.getAlienPosX(i, j)) + " PosY: " + String.valueOf(nivel.getAlienPosY(i, j)));
                    }
                    if(i==1 || i==2){
                        DSocket.escribirTXTEnviar("PosX: " + String.valueOf(nivel.getAlienPosX(i, j)) + " PosY: " + String.valueOf(nivel.getAlienPosY(i, j)));

                    }
                    if(3 <= i){
                        DSocket.escribirTXTEnviar("PosX: " + String.valueOf(nivel.getAlienPosX(i, j)) + " PosY: " + String.valueOf(nivel.getAlienPosY(i, j)));

                    }
                }
            }
        
        for(java.lang.Integer i=0; i<4; i++){
                DSocket.escribirTXTEnviar("HP: " + String.valueOf(nivel.getBunkerHp(i)));
            }
        
        DSocket.escribirTXTEnviar(DSocket.leerDatosBalas());
        

        if(nivel.getPlayerposX()==-1){
            ejecucion = false;
        }

        DSocket.BorrarDatosR();
        socket.SocketServidor();

    }  
        
    }
    
     /**
      * Constructor por defecto. Hace todo lo que hace el ejemplo.
      */
    public void SocketServidor()
    {
        try
        {
            // Se acepata una conexi�n con un cliente. Esta llamada se queda
            // bloqueada hasta que se arranque el cliente.
            try ( // Se crea un socket servidor atendiendo a un determinado puerto.
            // Por ejemplo, el 25556.
                    ServerSocket socket = new ServerSocket (25556)) {
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
                    
                    DatoSocket Dato = new DatoSocket();
                    
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
