package server;

/**
 * Clase que conforma al jugador
 * @author Harold Espinoza M.
 */
public class Jugador {

    java.lang.Integer posX;
    java.lang.Integer hp;
    java.lang.Integer puntaje;

    /**
     * Constructor de la clase que crea al jugador
     * @author Harold Espinoza M.
     */
    public Jugador(){
        this.posX = 4;
        this.hp = 3;
        this.puntaje = 0;

    }

    /**
     * Funcion para cambiar la vida del jugador
     * @param hp Entero con la vida del jugador
     * 
     */
    void setHp(java.lang.Integer hp){
        this.hp=hp;
    }

    /**
     * Funcion para cambiar la posicion en el eje X del jugador
     * @param posX Entero con la posicion en X del jugador
     * 
     */
    void setPosX(java.lang.Integer posX){
        this.posX=posX;
    }

    /**
     * Funcion para cambiar el puntaje del jugador
     * @param score Entero con la vida del jugador
     * 
     */
    void setPuntaje(java.lang.Integer score){
        this.puntaje=score;
    }

    /**
     * Funcion para obtener la vida del jugador
     * @return Retorna un entero con la vida del jugador
     * 
     */
    int getHp(){
        return this.hp;
    }

    /**
     * Funcion para obtener la posicion en el eje X del jugador
     * @return Retorna un entero con la posicion en X del jugador
     * 
     */
    int getPosX(){
        return this.posX;
    }

    /**
     * Funcion para cambiar el puntaje del jugador
     * @return Retorna un entero con el puntaje del jugador 
     * 
     */
    int getPuntaje(){
        return this.puntaje;
    }

    /**
     * Funcion que alcualiza los parametros del jugador vida, posicion en X y puntaje
     * @param hp Entero con la vida del jugador
     * @param posX Entero con la posicion en X del jugador
     * @param score Entero con el puntaje del jugador
     * 
     */
    void Update(java.lang.Integer hp,java.lang.Integer posX,java.lang.Integer score){
        this.hp=hp;
        this.posX=posX;
        this.puntaje=score;
    }

    /**
     * Fucion que adiciona puntaje al jugador
     * @param score Entero con la cantidad de puntaje que se desea agregar
     * 
     */
    void addPuntaje(java.lang.Integer score){
        this.puntaje = this.puntaje + score;
    }
}
