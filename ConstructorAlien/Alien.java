/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package ConstructorAlien;

/**
 *
 * @author arman
 */
public class Alien {
    
    private java.lang.Integer vida;
    private final java.lang.Integer PuntosMuerte;
    private java.lang.Integer posx;
    private java.lang.Integer posy;
    
    /**
     * Constructor para los aliens
     * @param vida Integer 0 o 1 
     * @param PuntosMuerte Integer puntaje por muerte de alien
     * @param posx Integer posicion del alien en x
     * @param posy Integer posicion del alien en y
     */
    
    public Alien(java.lang.Integer vida, java.lang.Integer PuntosMuerte, java.lang.Integer posx, java.lang.Integer posy){
        this.PuntosMuerte = PuntosMuerte;
        this.vida = vida;
        this.posx = posx;
        this.posy = posy;
    }
    
      public int getPuntosMuerte(){
       return this.PuntosMuerte;
    }
    
    /**
     * Obtiene si el alien está vivo o muerto
     * 
     * @return integer puede ser 0 o 1
     * 
     */
    
    public int getvida(){
        return this.vida;
    }
    
    /**
     * Obtiene la posición en x del alien
     * 
     * @return Integer posición en x
     */
    
    public int getposx(){
        return this.posx;
    }
    
    /**
     * Obtiene la posicion en y del Alien
     * 
     * @return Integer posicion en y
     */
    
    public int getposy(){
        return this.posy;
    }
    
    /**
     * Función que cambia la vida del alien
     * 
     * @param vida Integer 0 o 1
     */
    
    public void setvida(java.lang.Integer vida){
        this.vida = vida;
    }
    
    /**
     * Función que cambia las posición x del alien
     * 
     * @param posx Integer
     */
    
    public void setposx(java.lang.Integer posx){
        this.posx = posx;
    }
    
    /**
     * Función que cambia la posición y del alien
     * 
     * @param posy Integer
     */
    
    public void setposy(java.lang.Integer posy){
        this.posy = posy;
    }
    
}
