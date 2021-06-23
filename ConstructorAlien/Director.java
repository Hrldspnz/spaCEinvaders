/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ConstructorAlien;

import ConstructorAlien.Builder;

/**
 *
 * @author Armando Fallas
 * @version 1.0
 */
public class Director {
    
    public void Calamar(Builder builder){
        builder.setPuntosMuerte(10);
        builder.setposx(0);
        builder.setposy(0);
        builder.setvida(1);
    }
    
    public void Cangrejo(Builder builder){
        builder.setPuntosMuerte(20);
        builder.setposx(0);
        builder.setposy(0);
        builder.setvida(1);
    }
    
    public void Pulpo(Builder builder){
        builder.setPuntosMuerte(40);
        builder.setposx(0);
        builder.setposy(0);
        builder.setvida(1);
    }
    
}
