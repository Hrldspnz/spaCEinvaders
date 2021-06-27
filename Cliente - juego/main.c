#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "include/raylib.h"
#include "include/propiedades.h"
#include "Aliens.h"
#include "Player.h"
#include "Bullets.h"
#include "Bunker.h"

struct Aliens aliens[5][8]; 
struct Player player;
struct Bullets bullets[3];
struct Bullets enemiesBullets[10];
struct Bunker bunkers[4];

int score = 0;
int marginL = 10, marginR = SCREEN_WIDTH-64;
int direction = 1;
int enemyCount = 40;
int framesCounter = 0;
int playerCanShoot = 1;
int isInGame = 0;
int isObserving = 0;
int menuTextSelected = 0;


Texture2D playerTexture;
Texture2D pulpoSprite;
Texture2D cangrejoSprite;
Texture2D calamarSprite;
Texture2D enemyAtk;
Texture2D bunker;

Sound playerShootFx;
Sound enemyExplosionFx;
Sound scoreFx;
Sound playerExplosionFx;
Sound uiFx;

bool moveDownwards = false;

void updatePlayer(Sound*, float);
void updateBullets(Sound*, Sound*, float);
void updateEnemies(float);
void updateEnemiesBullets(Sound*, float);
void initGame();
void playGame();
void observeGame();
void loadTextures();
void loadSounds();
void drawGame(Texture2D*, Texture2D*, Texture2D*, Texture2D*, Texture2D*, Texture2D*);
void drawMainMenu();
void handleMainMenu(Sound*);
void handleEndGame(Sound*);
void escribirTXT(char cadena[]);
void leerTXTObserver();

/**
 * Crea todos lo objetos que el juego va utilizar
 * @author Mat 
 * */
int main() {

    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
    SetTargetFPS(60);
    HideCursor();

    InitAudioDevice();
    
    loadTextures();
    loadSounds();

    SetSoundVolume(playerShootFx, 0.2);
    SetSoundVolume(enemyExplosionFx, 0.1);
    SetSoundVolume(playerExplosionFx, 0.1);
    SetSoundVolume(uiFx, 0.2);

    initGame();
    

    while (!WindowShouldClose()) {

        if (player.HP > 0 && enemyCount > 0 && isInGame) {
            playGame();
        }else if(isObserving){
            observeGame();
        }
        else{
            initGame();
            handleMainMenu(&uiFx);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        if (isInGame || isObserving) {
            drawGame(&playerTexture, &pulpoSprite, &cangrejoSprite, &calamarSprite, &enemyAtk, &bunker);
        } else{ 
            drawMainMenu(&uiFx);
        } /*else {
            //handleEndGame(&uiFx);
        }*/
        
        EndDrawing();

    }

    UnloadTexture(bunker);
    UnloadTexture(playerTexture);
    UnloadTexture(pulpoSprite);
    UnloadTexture(cangrejoSprite);
    UnloadTexture(calamarSprite);
    UnloadTexture(enemyAtk);

    UnloadSound(playerShootFx);
    UnloadSound(enemyExplosionFx);
    UnloadSound(scoreFx);

    CloseAudioDevice();

    CloseWindow();

    return 0;
}

//buscar si se puede hacer desde la lectura del archivo
void observeGame(){
    leerTXTObserver();
    if(player.HP <= 0){
        isObserving = 0;
    }
}

void playGame(){

    int resp;
    //resp = conectSocket();

    char cadena[1500] = "";
    if (!playerCanShoot) framesCounter++;

            if (framesCounter == 60) {
                framesCounter = 0;
                playerCanShoot = 1;
            }
            
            updatePlayer(&playerShootFx, GetFrameTime());
            updateBullets(&enemyExplosionFx, &scoreFx, GetFrameTime());
            updateEnemies(GetFrameTime());
            updateEnemiesBullets(&playerExplosionFx, GetFrameTime());

            char buffer[4];

            itoa(player.posX, buffer, 10);
            strcat(cadena, "JPosx: ");
            strcat(cadena, buffer);
            strcat(cadena, " JHP: ");
            itoa(player.HP, buffer, 10);
            strcat(cadena, buffer);
            strcat(cadena, "\n");

            for (int i = 0; i < 5; ++i) {
                for (int j = 0; j < 8; ++j){
                    itoa(aliens[i][j].posX, buffer, 10);
                    strcat(cadena, "Posx: ");
                    strcat(cadena, buffer);

                    itoa(aliens[i][j].posY, buffer, 10);
                    strcat(cadena, " Posy: ");
                    strcat(cadena, buffer);
                    strcat(cadena, "\n");

                }
            }


            for (int j = 0; j < 4; ++j){
                itoa(bunkers[j].HP, buffer, 10);
                strcat(cadena, "HP: ");
                strcat(cadena, buffer);
                strcat(cadena, "\n");
            }

            for (int j = 0; j < 10; ++j){
                itoa(enemiesBullets[j].posX, buffer, 10);
                strcat(cadena, "ABalaPosx: ");
                strcat(cadena, buffer);

                itoa(enemiesBullets[j].posY, buffer, 10);
                strcat(cadena, " ABalaPosy: ");
                strcat(cadena, buffer);
                strcat(cadena, "\n");
            }

            for (int j = 0; j < 3; ++j){
                itoa(bullets[j].posX, buffer, 10);
                strcat(cadena, "BalaPosx: ");
                strcat(cadena, buffer);

                itoa(bullets[j].posY, buffer, 10);
                strcat(cadena, " BalaPosy: ");
                strcat(cadena, buffer);
                strcat(cadena, "\n");
            }
            

            escribirTXT(cadena);
            sleep(0.05);
            

}

/** 
 * Actualiza la posicion del jugador.
 * Ademas verfica que el jugador pueda disparar
 * @autor Mat, Harold
 *  @param fx sonido ejecutado al judaor disparar
 *  @param mov_speed variable que depende de los FPS que ayuda
 * a calcular la velocidad del movimiento de la nave del jugador
 * 
*/
void updatePlayer(Sound* fx, float mov_speed) {

    if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        player.posX -= MOVEMENT_SPEED * mov_speed;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player.posX += MOVEMENT_SPEED * mov_speed;
    }

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)|| IsKeyPressed(KEY_UP)) {

        if (playerCanShoot) {
            playerCanShoot = 0;
            for (int i = 0; i < 100; i++) {
                if (bullets[i].posX == -1 && bullets[i].posY == -1) {
                    PlaySound(*fx);
                    bullets[i].posX = player.posX + 22 - 2;
                    bullets[i].posY = player.posY - 2 ;
                    break;
                }
            }
        }
    }

    if (player.posX + PLAYER_WIDTH > SCREEN_WIDTH) {
        player.posX = SCREEN_WIDTH - PLAYER_WIDTH;
    } else if (player.posX < 0) {
        player.posX = 0;
    }
}


/**
 * Actualiza la posicion de las balas disparadas por el jugador.
 * Esta a su vez revisa si la bala colisiona con los enemigos o con los bunkers.
 * En el caso de colisionar actualiza la informacion del archivo
 * @author Mat, Harold
 * @param explosionFx sonido que emiten lo enemigos al morir
 * @param score sonido reproducido al ganar puntaje
 * */
void updateBullets(Sound* explosionFx, Sound* scoreFx, float mov_speed) {
    for (int i = 0; i < 3; ++i) {
        if (bullets[i].posX != -1) {
            for (int col = 0; col < 5; ++col) {
                for (int row = 0; row < 8; ++row) {
                    if (aliens[col][row].posX != -1 && aliens[col][row].posY != 1) {
                        if (CheckCollisionRecs((Rectangle) { bullets[i].posX, bullets[i].posY, 6, 6 }, (Rectangle) { aliens[col][row].posX, aliens[col][row].posY, ENEMY_WIDTH, ENEMY_HEIGHT })) {
                            PlaySound(*explosionFx);
                            aliens[col][row].posX = -1; 
                            aliens[col][row].posY = -1;
                            bullets[i].posX = -1;
                            bullets[i].posY = -1;
                            enemyCount--;
                            score += 100;
                            if (score % 1000 == 0) PlaySound(*scoreFx);
                        }
                        for (int j = 0; j < 4; j++)
                        {
                            if(CheckCollisionRecs((Rectangle) { bullets[i].posX, bullets[i].posY, 6, 6 }, 
                                                (Rectangle) {bunkers[j].posX, bunkers[j].posY, BUNKER_WIDTH, BUNKER_HEIGHT}) 
                                                && bunkers[j].HP>0){

                                PlaySound(*explosionFx);
                                bunkers[j].HP -=1;
                                bullets[i].posX = -1;
                                bullets[i].posY = -1;      
                            }

                        }

                    }
                }
            }

            if (bullets[i].posY < 0) {
                bullets[i].posX = -1;
                bullets[i].posY = -1;
            }

            if (bullets[i].posX != -1) {
                bullets[i].posY -= 400 * mov_speed;
            }

        }
    }
}


/**
 * Actualiza la posicion de los aliens.
 * Esta funcion decide en que direccion horizontal deben moverse los aliens, verificando que no esten despues del limite de la pantalla.
 * Por otro lado cuando un alien se encuentra a 10 posiciones del borde, todos los aliens bajan una posicion
 * @author Mat
 * @param mov_speed velocidad de movimiento de los enemigos (cantidad de posiciones en x que se mueven)
 * */
void updateEnemies(float mov_speed) {
    struct Aliens aux;
    aux.posX = 0;
    aux.posY = 0;
    struct Aliens* first = &aux;
    struct Aliens* last = &aliens[0][0];

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j){
            if (aliens[i][j].posX != -1) first = &aliens[i][j];
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            struct Aliens* enemy = &aliens[i][j];
            if (enemy->posX == -1) continue;

            if (enemy->posX < first->posX) first = enemy;
            else if (enemy->posX > last->posX) last = enemy;
        }
    }

    if (first->posX < marginL){
        direction = 1;
    } 
    else if (last->posX > marginR){
        direction = -1;
    }else if(first->posX <= marginL+10 || last->posX >= marginR-10){
        moveDownwards = true;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
             struct Aliens* enemy = &aliens[i][j];
            if(moveDownwards){
               enemy->posY+=2;
               //printf("%s vs %s", enemy->posY,   SCREEN_HEIGHT - 150);
               if(enemy->posY >= SCREEN_HEIGHT - 150){
                   player.HP = 0;
               }
            }
            if (enemy->posX == -1) continue;
            //velocidad de movimiento enemigo
            enemy->posX += direction * 100 * (20 / (enemyCount/2)) * mov_speed;
            

            if (i == 4) {
                if (GetRandomValue(1, 400) == 1) {
                    for (int k = 0; k < 10; ++k) {
                        if (enemiesBullets[k].posX == -1 && enemiesBullets[k].posY == -1) {
                            enemiesBullets[k].posX = enemy->posX + 22 - 2;
                            enemiesBullets[k].posY = enemy->posY + 2;
                            break;
                        }
                    }
                }
            } else if (aliens[i + 1][j].posX == -1) {
                if (GetRandomValue(1, 400) == 1) {
                    for (int k = 0; k < 10; ++k) {
                        if (enemiesBullets[k].posX == -1 && enemiesBullets[k].posY == -1) {
                            enemiesBullets[k].posX = enemy->posX + 22 - 2;
                            enemiesBullets[k].posY = enemy->posY + 2;
                            break;
                        }
                    }
                }
            }
        }
    }
    moveDownwards = false;
}

 /**
  * Actualiza las posiciones de las balas del enemigo. Al mismo tiempo verifica si han colisionado con el jugador o con algun bunker
  * Si colisiona alguno le disminuye la vida en 1, o si poseen solo 1 de vida, lo destruye
  * @author Mat, Armando
  * @param fx sonido reproducido al impactar al jugador o a algun bunker
  * @param mov_speed velocidad a la que se mueven las balas del enemigo
  */
void updateEnemiesBullets(Sound* fx, float mov_speed) {
    for (int i = 0; i < 10; ++i) {
        if (enemiesBullets[i].posX != -1 && enemiesBullets[i].posY != -1) {
            struct Bullets* bullet = &enemiesBullets[i];
            if (CheckCollisionRecs((Rectangle) { enemiesBullets[i].posX, enemiesBullets[i].posY, BULLET_WIDTH, BULLET_HEIGHT },
                                    (Rectangle) { player.posX, player.posY, PLAYER_WIDTH, PLAYER_HEIGHT })) {
                PlaySound(*fx);
                player.HP -= 1;
                if(player.HP <= 0){

                    player.posX = -1;
                }
                enemiesBullets[i].posX = -1;
                enemiesBullets[i].posY = -1;
            }
            for (int j = 0; j < 4; j++)
            {
                if(CheckCollisionRecs((Rectangle) { enemiesBullets[i].posX, enemiesBullets[i].posY, BULLET_WIDTH, BULLET_HEIGHT}, 
                                    (Rectangle) {bunkers[j].posX, bunkers[j].posY, BUNKER_WIDTH, BUNKER_HEIGHT}) 
                                    && bunkers[j].HP>0){

                    PlaySound(*fx);
                    bunkers[j].HP -=1;          
                    enemiesBullets[i].posX = -1;
                    enemiesBullets[i].posY = -1;      
                }

            }
            
            
            if (bullet->posY > SCREEN_HEIGHT) {
                bullet->posX = -1;
                bullet->posY = -1;
            }

            if (bullet->posX != -1) {
                bullet->posY += 400 * mov_speed;
            }
        } 
    }
}

/**
 * Funcion encargada de asignar las texturas utilizadas por el juego
 * @author Mat
 * */
void loadTextures(){
    playerTexture = LoadTexture("assets/sprites/player.png");
    pulpoSprite = LoadTexture("assets/sprites/pulpo.png");
    cangrejoSprite = LoadTexture("assets/sprites/cangrejo.png");
    calamarSprite = LoadTexture("assets/sprites/calamar.png");
    enemyAtk = LoadTexture("assets/sprites/enemy_atk.png");
    bunker = LoadTexture("assets/sprites/escudo.gif");
}

/**
 * Funcion encargada de asignar los sonidos que el juego reproducira
 * @author Mat
 * 
 * */
void loadSounds(){
    playerShootFx = LoadSound("assets/sounds/player_shoot.wav");
    enemyExplosionFx = LoadSound("assets/sounds/enemy_explosion.wav");
    scoreFx = LoadSound("assets/sounds/score.wav");
    playerExplosionFx = LoadSound("assets/sounds/player_explosion.wav");
    uiFx = LoadSound("assets/sounds/ui_interact.wav");
}


/**
 * Esta funcion se encarga de dibujar todos los sprites del juego.
 * Estos sprites son dibujados segun las posiciones ya calculadas de los enemigos, bunkers y el jugador.
 * @author Mat
 * @param playerTexture sprite del jugador
 * @param pulpoSprite sprite del jugador
 * @param cangrejoSprite sprite del jugador
 * @param calamarSprite sprite del jugador
 * @param enemyAtk sprite del jugador
 * @param bunker sprite del jugador
 * */
void drawGame(Texture2D* playerTexture, Texture2D* pulpoSprite, Texture2D* cangrejoSprite, Texture2D* calamarSprite, Texture2D* enemyAtk, Texture2D* bunker) {
    if (player.HP > 0 && enemyCount > 0) {
        Vector2 vPlayer = {player.posX, player.posY};
        DrawTextureV(*playerTexture, vPlayer, WHITE);
        for (int i = 0; i < 4; i++)
        {
            if(bunkers[i].HP>0){
                Vector2 vBunker = {bunkers[i].posX, bunkers[i].posY};
                DrawTextureV(*bunker,vBunker,WHITE);
            }
        }
        
        
       
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (aliens[i][j].posX != -1) {
                    Vector2 alien;
                    alien.x = aliens[i][j].posX;
                    alien.y = aliens[i][j].posY;
                    if (i == 0) {
                        DrawTextureV(*calamarSprite, alien, WHITE);
                    } else if (i <= 2) {
                        DrawTextureV(*cangrejoSprite, alien, WHITE);
                    } else {
                        DrawTextureV(*pulpoSprite, alien, WHITE);
                    }
                }
            }
        }

        for (int i = 0; i < 3; ++i) {
            if (bullets[i].posX != -1) {
                DrawRectangle(bullets[i].posX, bullets[i].posY, 6, 6, WHITE);
            }
        }

        for (int i = 0; i < 10; ++i) {
            if (enemiesBullets[i].posX != -1) {
                Vector2 enemieBullet = {enemiesBullets[i].posX, enemiesBullets[i].posY};
                DrawTextureV(*enemyAtk, enemieBullet, WHITE);
            }
        }

        DrawText(TextFormat("SCORE: %05i", score), 10, SCREEN_HEIGHT - 25, 20, RAYWHITE);
    } else {
        isInGame = 0;
    }
}


/**
 * Dibuja el menu inicial
 * @author Mat
 * 
*/
void drawMainMenu() {
    
        DrawText("SpaCEinvaders", SCREEN_WIDTH / 2 - MeasureText("SpaCEinvaders", 70) / 2, 30, 70, YELLOW);
        if(menuTextSelected == 0 ){
            DrawText("- Jugar -",  20, 300, 55, GREEN);
            DrawText("Observar un juego",  10, 450, 55, WHITE);
            DrawText("Presione enter para jugar",  10, 620, 50, WHITE);
        }else{
            DrawText("Jugar", 10, 300, 55, WHITE);
            DrawText("- Observar un juego -", 20 , 450, 55, GREEN);
            DrawText("Presione enter para jugar", 10 , 620, 50, WHITE);
        }
}

/**
 * Maneja la logica del menu inicial (Si no se agrega el espectador esta desaparece)
 * @author Mat
*/

void handleMainMenu(Sound* uiFx) {
    

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            PlaySound(*uiFx);
            if(menuTextSelected == 0 )
                isInGame = 1;
            else if(menuTextSelected == 1)
                isObserving = 1;
    
        }else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)){            
            menuTextSelected = 1;
            PlaySound(*uiFx);
        }else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)){            
            menuTextSelected = 0;
            PlaySound(*uiFx);
        }
}

/**
 * inicializa el jugador, los bunkers, los enemigos, las balas lanzadas por el jugador y las balas lanzadas por el enemigo.
 * Estos los inicializa en una posicion calculada
 * @author Mat
*/
void initGame() {

    //system("clienteC.exe");

    player.HP = 3;
    player.posX = SCREEN_WIDTH / 2 - 22;
    player.posY = SCREEN_HEIGHT - 50 ;
    score = 0;
    enemyCount = 40;

    bunkers[0].posX = (SCREEN_WIDTH/4)-SCREEN_WIDTH*0.20;
    bunkers[1].posX = (SCREEN_WIDTH/4);
    bunkers[2].posX = SCREEN_WIDTH - (SCREEN_WIDTH/4)-SCREEN_WIDTH*0.20;
    bunkers[3].posX = SCREEN_WIDTH - (SCREEN_WIDTH/4);

    for (int i = 0; i < 4; i++)
    {
        bunkers[i].posY = (SCREEN_HEIGHT)-150;
        bunkers[i].HP = BUNKER_HP;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            aliens[i][j].posX = j * 80 + 20;
            aliens[i][j].posY = i * 50 + 50;
        }
    }

    for (int i = 0; i < 3; ++i) {
        bullets[i].posX = -1;
        bullets[i].posY = -1;
    }

    for (int i = 0; i < 10; ++i) {
        enemiesBullets[i].posX = -1;
        enemiesBullets[i].posY = -1;
    }
}

void leerTXTObserver(){
	FILE *archivo;
    char linea[32];
	static char data[1300];
	int i= 0;
    char *token;
	
	archivo = fopen("DatoR.txt","r");
	if (archivo == NULL)
    {
        printf("\nError de apertura del archivo. \n\n");
    }
    else
    {
        fgets(linea, 32,(FILE*) archivo);
        token = strtok(linea, " ");
        token = strtok(NULL, " ");
        if(token != NULL){
            player.posX = atoi(token);
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            player.HP = atoi(token);
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 8; j++)
                {
                    fgets(linea, 32,(FILE*) archivo);
                    token = strtok(linea, " ");
                    token = strtok(NULL, " ");
                    aliens[i][j].posX = atoi(token);
                    token = strtok(NULL, " ");
                    token = strtok(NULL, " ");
                    aliens[i][j].posY = atoi(token);
                }
                
            }
            for(int i = 0; i<4; i++){
                fgets(linea, 32,(FILE*) archivo);
                token = strtok(linea, " ");
                token = strtok(NULL, " ");
                bunkers[i].HP = atoi(token);
            }
            for(int i = 0; i<10;i++){
                fgets(linea, 32,(FILE*) archivo);
                token = strtok(linea, " ");
                token = strtok(NULL, " ");
                enemiesBullets[i].posX = atoi(token);
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                enemiesBullets[i].posY = atoi(token);
            }
            //Linea para saltar la linea que indica el inicio de las balas del jugador
            //fgets(linea, 32,(FILE*) archivo);
            for(int i = 0; i<3;i++){
                fgets(linea, 32,(FILE*) archivo);
                token = strtok(linea, " ");
                token = strtok(NULL, " ");
                bullets[i].posX = atoi(token);
                token = strtok(NULL, " ");
                token = strtok(NULL, " ");
                bullets[i].posY = atoi(token);                
            }
            
        }
    }
    fclose(archivo);
    sleep(0.05);	
}

void escribirTXT(char cadena[]){
	FILE *fp;
    
    fp = fopen ( "DatoE.txt", "w" ); //parámetro para escritura al final y para file tipo texto
 	
 	fwrite(cadena, sizeof(char), strlen(cadena), fp );
 	
 	fclose ( fp );
}

