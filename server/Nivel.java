
/**
 * Clase que crea el nivel
 * @author Harold Espinoza M.
 */
public class Nivel{

    java.lang.Integer oleadas;
    Bunker bunkers[] = new Bunker[4];
    Alien aliens[][] = new Alien[5][8];
    Jugador player = new Jugador();
 
    /**
     * Constructor de la clase nivel
     */
    public Nivel(){
        for(java.lang.Integer j=0; j<4; j++){
            this.bunkers[j] = new Bunker();
        }
    }

    /**
     * Funcion encargada de crear el nivel, insertando los aliens a la matriz
     */
    void CreateNewLvl(){
        for(java.lang.Integer i=0; i<5; i++){
            for(java.lang.Integer j=0; j<8; j++){
                if(i<1){
                    aliens[i][j]=new Alien(1,10,j*2,i+20);//Cambiar pos X,Y o cambiarlas despues con el update
                }
                if(1<=i && i>3){
                    aliens[i][j]=new Alien(1,10,j*2,i+20);//Cambiar pos X,Y o cambiarlas despues con el update
                }
                if(3 <= i){
                    aliens[i][j]=new Alien(1,10,j*2,i+20);//Cambiar pos X,Y o cambiarlas despues con el update
                }
                
            }
        }
    }

    /**
     * Funcion que reduce la vida de un bunker de la lista
     * @param ind Entero con la posicion en la lista del bunker
     */
    void ReduceBunkers(java.lang.Integer ind){
        this.bunkers[ind].restHp();
    }

    /**
     * Funcion que actualiza los datos del jugador: vida, posicion en X y puntaje
     * @param hp Entero con la vida del jugador
     * @param X Entero con la posicion en X del jugador
     * @param score Entero con la puntuacion del jugador 
     */
    void UpdatePlayer(java.lang.Integer hp, java.lang.Integer X, java.lang.Integer score){
        this.player.Update(hp, X, score);

    }

    /**
     * Funcion encargada de establecer la vida del alien a 0 dada la posicion del alien en la matriz
     * @param ind1 Entero con el indice en la fila de la matriz
     * @param ind2 Entero con el indice en la columna de la matriz 
     */
    void DeathAlien(java.lang.Integer ind1, java.lang.Integer ind2){
        aliens[ind1][ind2].setvida(0);

    }

    /**
     * Funcion que actualiza la posicion en el eje "X" y "Y" de un alien en una matriz
     * @param ind1 Entero con el indice en la fila de la matriz
     * @param ind2 Entero con el indice en la columna de la matriz 
     * @param X Entero con la posicion en X del alien
     * @param Y Entero con la posicion en Y del alien
     */
    void UpdateAliens(java.lang.Integer ind1, java.lang.Integer ind2,java.lang.Integer X, java.lang.Integer Y){
        aliens[ind1][ind2].setposx(X);
        aliens[ind1][ind2].setposy(Y);

    }

    /**
     * Funcion que retorna la posicion en X del jugador
     * @return Retorna un entero con la pos en x del jugador
     */
    int getPlayerposX(){
        return this.player.getPosX();
    }

    /**
     * Funcion que retorna el puntaje del jugador
     * @return Retorna un entero con el puntaje
     */
    int getPPuntaje(){
        return this.player.getPuntaje();
    }
 
    /**
     * Funcion que obtiene la vida restante del jugador
     * @return Retorna un entero con la vida del jugador
     */
    int getPlayerHp(){
        return this.player.getHp();
    }

    /**
     * Funcion que retorna la vida restante de un bunker dado un indice 
     * @param ind1 Entero con el indice del bunker del cual se desea conocer la vida
     * @return Retorna un entero con la vida del bunker
     */
    int getBunkerHp(java.lang.Integer ind1){
        return this.bunkers[ind1].getHp();
    }

    /**
     * Funcion que retorna la vida del alien dados sus indices en la matriz 
     * @param ind1 Entero con el indice en la fila del alien
     * @param ind2 Entero con el indice en la columna del alien
     * @return Retorna entero con la vida del alien
     */
    int getAlienHp(java.lang.Integer ind1, java.lang.Integer ind2){
        return this.aliens[ind1][ind2].getvida();
    }

    /**
     * Funcion que obtine la posicion del alien en el eje X dado sus indices en la matriz
     * @param ind1 Entero con el indice en la fila del alien
     * @param ind2 Entero con el indice en la columna del alien
     * @return Retorna un entero con la posicion en x del alien
     */
    int getAlienPosX(java.lang.Integer ind1, java.lang.Integer ind2){
        return this.aliens[ind1][ind2].getposx();
    }

    /**
     * Funcion que obtine la posicion del alien en el eje Y dado sus indices en la matriz
     * @param ind1 Entero con el indice en la fila del alien
     * @param ind2 Entero con el indice en la columna del alien
     * @return Retorna un entero con la posicion en y del alien
     */
    int getAlienPosY(java.lang.Integer ind1, java.lang.Integer ind2){
        return this.aliens[ind1][ind2].getposy();
    }

}