/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package server;

import ConstructorAlien.Director;
import ConstructorAlien.AlienBuilder;
import ConstructorAlien.Alien;
import socket.DatoSocket;

/**
 *
 * @author arman
 */
public class Server {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Director director = new Director();
        
        AlienBuilder builder = new AlienBuilder();
        AlienBuilder builder2 = new AlienBuilder();
        AlienBuilder builder3 = new AlienBuilder();
        
        director.Calamar(builder);
        director.Cangrejo(builder2);
        director.Pulpo(builder3);
        
        Alien alien1 = builder.getResultado();
        Alien alien4 = builder.getResultado();
        Alien alien2 = builder2.getResultado();
        Alien alien3 = builder3.getResultado();
        

    }
    
}
