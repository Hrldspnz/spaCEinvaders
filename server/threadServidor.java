package server;
import socket.DatoSocket;

public class threadServidor implements Runnable{
    int identPuerto;
    public void run(){
        identPuerto = Integer.parseInt(Thread.currentThread().getName());
        // Se instancia la clase principal para que haga todo lo que tiene que
        // hacer el ejemplo
        SocketServidor socket = new SocketServidor();
        Nivel nivel = new Nivel();
        DatoSocket DSocket = new DatoSocket(identPuerto);
        String[] Datos;
        
        java.lang.Integer indice;
        nivel.CreateNewLvl();
        DSocket.RellenarTXT();


        java.lang.Boolean ejecucion = true;
        while(ejecucion == true){
            indice=5;
            DSocket.BorrarDatosE();
            Datos = DSocket.leerTXTRecibido().split(" ");
            //socket.SocketServidor();
            /**
                * Ac? el servidor recorre todos los aliens asignandoles cada posici?n que tienen en el cliente
                */
            try{
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
            }catch(Exception ex) {
                System.out.println("Formato incorrecto de TXT");    
            } 
            
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
            socket.SocketServidor(Integer.parseInt(Thread.currentThread().getName()));

    }  
    }
    public static void main(String [] args){
        new Thread(new threadServidor(), "0").start();
        new Thread(new threadServidor(), "1").start();
    }
}
