package server;

/**
 * Clase que conforma al bunker
 * @author Harold Espinoza M.
 */


public class Bunker {

    java.lang.Integer hp;
    
    /** 
     * Constructor de la clase que crea el bunker
     */
    public Bunker(){
        this.hp = 3;
    }

    /**
     * Metodo para cambiar la vida del jugador 
     * @param hp Entero con la vida 
     */
    void setHp(java.lang.Integer hp){
        this.hp = hp;
    }

    /**
     * Metodo para obtener la vida del bunker
     * @return Retorna un entero con la vida del jugador
     */
    int getHp(){
        return this.hp;
    }

    /**
     * Metodo que resta un punto de vida al bunker 
     */
    void restHp(){
        this.hp--;
    }
}
