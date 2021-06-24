#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "include/raylib.h"
#include "include/propiedades.h"

Vector2 player = { SCREEN_WIDTH / 2 - 22, SCREEN_HEIGHT - 50 };
Vector2 enemies[5][8];
Vector2 bullets[50];
Vector2 enemiesBullets[50];
Vector2 bunkers[4];

int score = 0;
int bunkersHP[4] = { BUNKER_HP, BUNKER_HP, BUNKER_HP, BUNKER_HP};
int marginL = 10, marginR = SCREEN_WIDTH-64;
int direction = 1;
int enemyCount = 40;
int playerHP = 3;
int framesCounter = 0;
int playerCanShoot = 1;
int isInGame = 0;
int menuTextSelected = 0;

bool moveDownwards = false;

void updatePlayer(Sound*, float);
void updateBullets(Sound*, Sound*, float);
void updateEnemies(float);
void updateEnemiesBullets(Sound*, float);
void initGame();
void drawGame(Texture2D*, Texture2D*, Texture2D*, Texture2D*, Texture2D*, Texture2D*);
void drawMainMenu();
void handleMainMenu(Sound*);
void handleEndGame(Sound*);


/**
 * Crea todos lo objetos que el juego va utilizar
 * @author Mat 
 * */
int main() {

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Space Invaders");
    SetTargetFPS(60);
    HideCursor();

    Texture2D playerTexture = LoadTexture("assets/sprites/player.png");
    Texture2D pulpoSprite = LoadTexture("assets/sprites/pulpo.png");
    Texture2D cangrejoSprite = LoadTexture("assets/sprites/cangrejo.png");
    Texture2D calamarSprite = LoadTexture("assets/sprites/calamar.png");
    Texture2D enemyAtk = LoadTexture("assets/sprites/enemy_atk.png");
    Texture2D bunker = LoadTexture("assets/sprites/escudo.gif");

    InitAudioDevice();

    Sound playerShootFx = LoadSound("assets/sounds/player_shoot.wav");
    Sound enemyExplosionFx = LoadSound("assets/sounds/enemy_explosion.wav");
    Sound scoreFx = LoadSound("assets/sounds/score.wav");
    Sound playerExplosionFx = LoadSound("assets/sounds/player_explosion.wav");
    Sound uiFx = LoadSound("assets/sounds/ui_interact.wav");

    SetSoundVolume(playerShootFx, 0.2);
    SetSoundVolume(enemyExplosionFx, 0.1);
    SetSoundVolume(playerExplosionFx, 0.1);
    SetSoundVolume(uiFx, 0.2);

    initGame();

    while (!WindowShouldClose()) {

        if (playerHP > 0 && enemyCount > 0 && isInGame) {
            if (!playerCanShoot) framesCounter++;

            if (framesCounter == 60) {
                framesCounter = 0;
                playerCanShoot = 1;
            }

            updatePlayer(&playerShootFx, GetFrameTime());
            updateBullets(&enemyExplosionFx, &scoreFx, GetFrameTime());
            updateEnemies(GetFrameTime());
            updateEnemiesBullets(&playerExplosionFx, GetFrameTime());
        } else if (!isInGame) {
            handleMainMenu(&uiFx);
        }

        BeginDrawing();
        ClearBackground(BLACK);

        bunkers[0].x = (SCREEN_WIDTH/4)-SCREEN_WIDTH*0.20;
        bunkers[1].x = (SCREEN_WIDTH/4);
        bunkers[2].x = SCREEN_WIDTH - (SCREEN_WIDTH/4)-SCREEN_WIDTH*0.20;
        bunkers[3].x = SCREEN_WIDTH - (SCREEN_WIDTH/4);

        bunkers[0].y = (SCREEN_HEIGHT)-150;
        bunkers[1].y = (SCREEN_HEIGHT)-150;
        bunkers[2].y = (SCREEN_HEIGHT)-150;
        bunkers[3].y = (SCREEN_HEIGHT)-150;



        if (isInGame) {
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
        player.x -= MOVEMENT_SPEED * mov_speed;
    } else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
        player.x += MOVEMENT_SPEED * mov_speed;
    }

    if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_W)|| IsKeyPressed(KEY_UP)) {

        if (playerCanShoot) {
            playerCanShoot = 0;
            for (int i = 0; i < 100; i++) {
                if (bullets[i].x == -1 && bullets[i].y == -1) {
                    PlaySound(*fx);
                    bullets[i] = (Vector2) { player.x + 22 - 2, player.y - 2 };
                    break;
                }
            }
        }
    }

    if (player.x + PLAYER_WIDTH > SCREEN_WIDTH) {
        player.x = SCREEN_WIDTH - PLAYER_WIDTH;
    } else if (player.x < 0) {
        player.x = 0;
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
    for (int i = 0; i < 50; ++i) {
        if (bullets[i].x != -1) {
            for (int col = 0; col < 5; ++col) {
                for (int row = 0; row < 8; ++row) {
                    if (enemies[col][row].x != -1 && enemies[col][row].y != 1) {
                        if (CheckCollisionRecs((Rectangle) { bullets[i].x, bullets[i].y, 6, 6 }, (Rectangle) { enemies[col][row].x, enemies[col][row].y, ENEMY_WIDTH, ENEMY_HEIGHT })) {
                            PlaySound(*explosionFx);
                            enemies[col][row] = (Vector2) { -1, -1 };
                            bullets[i] = (Vector2) { -1, -1 };
                            enemyCount--;
                            score += 100;
                            if (score % 1000 == 0) PlaySound(*scoreFx);
                        }
                        for (int j = 0; j < 4; j++)
                        {
                            if(CheckCollisionRecs((Rectangle) { bullets[i].x, bullets[i].y, 6, 6 }, 
                                                (Rectangle) {bunkers[j].x, bunkers[j].y, BUNKER_WIDTH, BUNKER_HEIGHT}) 
                                                && bunkersHP[j]>0){

                                PlaySound(*explosionFx);
                                bunkersHP[j] -=1;                    
                                bullets[i] = (Vector2) { -1, -1 };        
                            }

                        }

                    }
                }
            }

            if (bullets[i].y < 0) {
                bullets[i] = (Vector2) { -1, -1 };
            }

            if (bullets[i].x != -1) {
                bullets[i].y -= 400 * mov_speed;
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
    Vector2 aux = { 0, 0 };
    Vector2* first = &aux;
    Vector2* last = &enemies[0][0];

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j){
            if (enemies[i][j].x != -1) first = &enemies[i][j];
        }
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            Vector2* enemy = &enemies[i][j];
            if (enemy->x == -1) continue;

            if (enemy->x < first->x) first = enemy;
            else if (enemy->x > last->x) last = enemy;
        }
    }

    if (first->x < marginL){
        direction = 1;
    } 
    else if (last->x > marginR){
        direction = -1;
    }else if(first->x <= marginL+10 || last->x >= marginR-10){
        moveDownwards = true;
    }

    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            Vector2* enemy = &enemies[i][j];
            if(moveDownwards){
               enemy->y+=2;
               if(enemy->y >= SCREEN_HEIGHT - 150){
                   playerHP = 0;
               }
            }
            if (enemy->x == -1) continue;
            //velocidad de movimiento enemigo
            enemy->x += direction * 100 * (40 / enemyCount) * mov_speed;
            

            if (i == 4) {
                if (GetRandomValue(1, 400) == 1) {
                    for (int k = 0; k < 50; ++k) {
                        if (enemiesBullets[k].x == -1 && enemiesBullets[k].y == -1) {
                            enemiesBullets[k] = (Vector2) { enemy->x + 22 - 2, enemy->y + 2};
                            break;
                        }
                    }
                }
            } else if (enemies[i + 1][j].x == -1) {
                if (GetRandomValue(1, 400) == 1) {
                    for (int k = 0; k < 50; ++k) {
                        if (enemiesBullets[k].x == -1 && enemiesBullets[k].y == -1) {
                            enemiesBullets[k] = (Vector2) { enemy->x + 22 - 2, enemy->y + 2};
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
    for (int i = 0; i < 50; ++i) {
        if (enemiesBullets[i].x != -1 && enemiesBullets[i].y != -1) {
            Vector2* bullet = &enemiesBullets[i];
            if (CheckCollisionRecs((Rectangle) { enemiesBullets[i].x, enemiesBullets[i].y, BULLET_WIDTH, BULLET_HEIGHT },
                                    (Rectangle) { player.x, player.y, PLAYER_WIDTH, PLAYER_HEIGHT })) {
                PlaySound(*fx);
                playerHP -= 1;
                enemiesBullets[i] = (Vector2) { -1, -1 };
            }
            for (int j = 0; j < 4; j++)
            {
                if(CheckCollisionRecs((Rectangle) { enemiesBullets[i].x, enemiesBullets[i].y, BULLET_WIDTH, BULLET_HEIGHT}, 
                                    (Rectangle) {bunkers[j].x, bunkers[j].y, BUNKER_WIDTH, BUNKER_HEIGHT}) 
                                    && bunkersHP[j]>0){

                    PlaySound(*fx);
                    bunkersHP[j] -=1;                    
                    enemiesBullets[i] = (Vector2) { -1, -1 };        
                }

            }
            
            
            if (bullet->y > SCREEN_HEIGHT) {
                *bullet = (Vector2) { -1, -1 };
            }

            if (bullet->x != -1) {
                bullet->y += 400 * mov_speed;
            }
        } 
    }
}

/**
 * Esta funcion se encarga de dibujar todos los sprites del juego.
 * Estos sprites son dibujados segun las posiciones ya calculadas de los enemigos, bunkers y el jugador.
 * @Author Mat
 * @param playerTexture sprite del jugador
 * @param pulpoSprite sprite del jugador
 * @param cangrejoSprite sprite del jugador
 * @param calamarSprite sprite del jugador
 * @param enemyAtk sprite del jugador
 * @param bunker sprite del jugador
 * */
void drawGame(Texture2D* playerTexture, Texture2D* pulpoSprite, Texture2D* cangrejoSprite, Texture2D* calamarSprite, Texture2D* enemyAtk, Texture2D* bunker) {
    if (playerHP > 0 && enemyCount > 0) {
        DrawTextureV(*playerTexture, player, WHITE);
        for (int i = 0; i < 4; i++)
        {
            if(bunkersHP[i]>0)
                DrawTextureV(*bunker,bunkers[i],WHITE);
        }
        
        
       
        for (int i = 0; i < 5; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (enemies[i][j].x != -1) {
                    if (i == 0) {
                        DrawTextureV(*calamarSprite, enemies[i][j], WHITE);
                    } else if (i <= 2) {
                        DrawTextureV(*cangrejoSprite, enemies[i][j], WHITE);
                    } else {
                        DrawTextureV(*pulpoSprite, enemies[i][j], WHITE);
                    }
                }
            }
        }

        for (int i = 0; i < 50; ++i) {
            if (bullets[i].x != -1) {
                DrawRectangle(bullets[i].x, bullets[i].y, 6, 6, WHITE);
            }
        }

        for (int i = 0; i < 50; ++i) {
            if (enemiesBullets[i].x != -1) {
                DrawTextureV(*enemyAtk, enemiesBullets[i], WHITE);
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

        DrawText("Space Invaders", SCREEN_WIDTH / 2 - MeasureText("Space Invaders", 70) / 2, 30, 70, WHITE);

            DrawText("- Play -", SCREEN_WIDTH / 2 - MeasureText("- Play -", 55) / 2, 300, 55, WHITE);
            DrawText("Press enter to play", SCREEN_WIDTH / 2 - MeasureText("Press enter to play", 50) / 2, 400, 50, WHITE);
}

/**
 * Maneja la logica del menu inicial (Si no se agrega el espectador esta desaparece)
 * @author Mat
*/

void handleMainMenu(Sound* uiFx) {
    

        if (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE)) {
            PlaySound(*uiFx);
            
                isInGame = 1;
        }
}

/**
 * Inicialisa los enemigos, las balas lanzadas por el jugador y las balas lanzadas por el enemigo.
 * Estos los inicializa en una posicion calculada
 * @author Mat
*/
void initGame() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 8; ++j) {
            enemies[i][j] = (Vector2) { j * 80 + 20, i * 50 + 50 };
        }
    }

    for (int i = 0; i < 50; ++i) {
        bullets[i] = (Vector2) { -1, -1 };
    }

    for (int i = 0; i < 50; ++i) {
        enemiesBullets[i] = (Vector2) { -1, -1 };
    }
}