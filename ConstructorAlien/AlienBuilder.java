package ConstructorAlien;

import ConstructorAlien.Alien;


/**
 * @author Armando Fallas
 * @version 0.1
 */

public class AlienBuilder implements Builder{
    
    private java.lang.Integer vida;
    private java.lang.Integer PuntosMuerte;
    private java.lang.Integer posx;
    private java.lang.Integer posy;
    

    
    /**
     * Asigna al alien el puntaje que tendrá el jugador por matarlo
     * 
     * @param PuntosMuerte Puntaje que se obtiene al matar el alien
     */

    @Override
    public void setPuntosMuerte(java.lang.Integer PuntosMuerte) {
        this.PuntosMuerte = PuntosMuerte;
    }
    
    /**
     * Asigna una posición en X al alien
     * 
     * @param posx Posición en x del Alien
     */

    @Override
    public void setposx(java.lang.Integer posx) {
        this.posx = posx; 
    }
    
    /**
     * Asigna una posición en Y al alien
     * 
     * @param posy Posición en y del Alien
     */

    @Override
    public void setposy(java.lang.Integer posy) {
        this.posy = posy; 
    }
    
    /**
     * Asigna la vida del alien pueder ser 0 Muerto o 1 Vivo
     * 
     * @param vida Debe ser 0 o un 1
     */

    @Override
    public void setvida(java.lang.Integer vida) {
        this.vida = vida; 
    }
    
    /**
     * Crea y retorna el alien
     * 
     * @return 
     */
    
    public Alien getResultado(){
        return new Alien(vida, PuntosMuerte, posx, posy);
    }
    
    
}
