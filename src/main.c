#include <genesis.h> //Library of Sega Genesis
#include <resources.h> //Load all Resources
#define CONST 84
#define SFX_CRASH 64
#define SFX_SEGA 64

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  #Gapa Game                                                                                                             //
//      & Author MatiasRN - Alias: MatRN                                                                                   //
//                                                                                                                         //
//  Description: This is a Sega Genesis game by youtuber gapa, this project uses the SGDK library, a C library.            //
//  I publish this code so that anyone can modify the game for learning purposes.                                          //
//  recommendation: separate the code and void into headers for more convenience when programming,                         //
//  and I recommend having practice and understanding of the limitations of the Sega Genesis before starting. Good luck :D //
//                                                                                                                         //
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///=====VOID INIT====///
void myJoyHandler(u16 joy, u16 changed, u16 state);
static void handleInput();
void GameManager();
void Intro();
void Menu();
void InitGame();
void GameOver();
void Player();
void Player2();
void positionPlayer();
void positionPlayer2();
void Dificultad();
void Interfaces();

///VARIABLES///
int StateGame = 0;
char GameOvertext[40] = "-Press Start to RESTART-";
u16 palette_full [64];
int ScrollingHorizontal = 0;

///=======SCORE========///
const int LEFT_EDGE = 0;
const int RIGHT_EDGE = 320;
int Score = 0;
int Score_2 = 0;
char Hud_string[14] = "";
char Hud_string2[14] = "";
u16 ind=1;

///=========PLAYER:1==========///
    int player_pos_x = 84;
    fix16 player_vel_yz = FIX16(0);
    fix16 player_y = FIX16(155);
    fix16 gravity = FIX16(0.3);
    fix16 Velocity = FIX16(0.2);
    int player_vel_x = 0;

///=======JUMP CHECK===========///
    bool jumping = TRUE;

///====================================///

///=========PLAYER:2==========///
    int player_pos_x2 = 200;
    fix16 player_vel_yz2 = FIX16(0);
    fix16 player_y2 = FIX16(155);
    fix16 gravity2 = FIX16(0.3);
    fix16 Velocity2 = FIX16(0.2);
    int player_vel_x2 = 0;
    bool Player2Ingame = FALSE;

///=======JUMP CHECK:2==========///
    bool jumping_2 = TRUE;

///====OBJECTS=====///
typedef struct{
    int ObjetoX;
    int ObjetoY;
}OBJECTS; OBJECTS Objects;

///=====ENEMY=====///
int EnemyX = -30;
int EnemyY = 60;

///======ENEMY:2====///
int EnemyX2 = -30;
int EnemyY2 = 20;

bool ChargeMove = FALSE;
bool ChargeMove2 = FALSE;
bool Hard = FALSE;

///====ALL SPRITES====///
Sprite* player;
Sprite* player2;
Sprite* block;
Sprite* object;
Sprite* enemy;
Sprite* enemy2;

///======DRAW MAP=====/// Draw the map using matrices and following the Map() instructions.
u8 level1[23][42] = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 2, 2, 2, 2, 2, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 10, 0, 0},
    {11, 11, 11, 11, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 11, 11, 11, 11, 11, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 11, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 11, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 2, 2, 2, 2, 2, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 2, 2, 2, 2, 2, 10, 0, 0},
    {11, 11, 11, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 11, 11, 11, 11, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {9, 7, 8, 8, 8, 8, 8, 8, 8, 7, 10, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 10, 0, 0},
    {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 11, 0, 0},
    {11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 11, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 11, 0, 0}
};

///<==FUNCTION MAIN==>/// Here the entire execution begins.
int main(){
//========INIT========//
    SPR_init(0,0,0);
    JOY_init();
    Intro();
///===Activate Init Game or Not, Only for the test==///
    //InitGame();
//=========LOOP GAME=========//
    while(1){
        //If the game state is 2 update player move.
            if(StateGame==2){
                positionPlayer();
                if(Player2Ingame==TRUE){
                    positionPlayer2();
                }
                        EnemyMove();
                    if(Hard==TRUE){
                        EnemyMove2();
                    }
                //DIFICULTAD//
                Dificultad();
                GameManager();
            }
    ///=====UPDATE=====///
        //SCROLL BACKGROUND//
            VDP_setHorizontalScroll(BG_B,ScrollingHorizontal);
            ScrollingHorizontal+= 1;
        //CONTROLS AND OTHERS//
            handleInput();
            SPR_update();
            SYS_doVBlankProcess();
    }
//==Finish Rom==//
    return (0);
}

///====CONTROLES ASINCRONAS===/// Initialize the controls.
static void handleInput(){
    u16 value = JOY_readJoypad(JOY_1);
    u16 value2 = JOY_readJoypad(JOY_2);

///=====CONTROLS PLAYER 1======///
    //===LEFT===//
    if (value & BUTTON_LEFT && StateGame==2){
                SPR_setHFlip(player,TRUE);
                player_vel_x = -3;
                SPR_setAnim(player,1);
    //===RIGHT===//
    }else if (value & BUTTON_RIGHT && StateGame==2){
                SPR_setHFlip(player,FALSE);
                player_vel_x = 3;
                SPR_setAnim(player,1);
    //===START INIT===//
    }else if (value & BUTTON_START && StateGame==1){
                InitGame();
    //===START===//
    }else if (value & BUTTON_START && StateGame==3){
                GameOver();
    //==NOT PRESSING BUTTON==//
    }else if (((!(value & BUTTON_LEFT)) && (!(value & BUTTON_RIGHT)) && (!(value & BUTTON_A)) && (!(value & BUTTON_B))) && StateGame==2){
                player_vel_x = 0;
				SPR_setAnim(player,0);
    }
    //==JUMP==//
    if ((value & BUTTON_A || value & BUTTON_B || value & BUTTON_C)&& StateGame==2){
            if(jumping == FALSE){
                jumping = TRUE;
                player_vel_yz = FIX16(-7);
            }
    }

///=====CONTROLS PLAYER 2======///
    //===LEFT===//
    if ((value2 & BUTTON_LEFT && StateGame==2)&& Player2Ingame==TRUE){
                SPR_setHFlip(player2,TRUE);
                player_vel_x2 = -3;
                SPR_setAnim(player2,1);
    //===RIGHT===//
    }else if ((value2 & BUTTON_RIGHT && StateGame==2) && Player2Ingame==TRUE){
                SPR_setHFlip(player2,FALSE);
                player_vel_x2 = 3;
                SPR_setAnim(player2,1);
    //===START INIT===//
    }else if ((value2 & BUTTON_START && StateGame==2) && Player2Ingame==FALSE){
            Player2Ingame=TRUE;
			Player2();
    //===START===//
    }else if ((value2 & BUTTON_START && StateGame==3) && Player2Ingame==TRUE){
                GameOver();
    //==NOT PRESSING BUTTON==//
    }else if (((!(value2 & BUTTON_LEFT && Player2Ingame==TRUE)) && (!(value2 & BUTTON_RIGHT && Player2Ingame==TRUE)) && (!(value2 & BUTTON_A && Player2Ingame==TRUE)))&& StateGame==2){
                player_vel_x2 = 0;
				SPR_setAnim(player2,0);
    }
    //==JUMP==//
    if ((value2 & BUTTON_A && Player2Ingame==TRUE|| value2 & BUTTON_B && Player2Ingame==TRUE|| value2 & BUTTON_C && Player2Ingame==TRUE)&& StateGame==2){
            if(jumping_2 == FALSE){
                jumping_2 = TRUE;
                player_vel_yz2 = FIX16(-7);
            }
    }
}

///<=====Intro=====>// Initializes game state 0 (Intro Sega).
void Intro(){
////=====================================================///
        memcpy(&palette_full[0],SEGALOGOPNG.palette->data,16*2);
        PAL_setPaletteColors(0,(u16*) palette_black,DMA);
        VDP_setPalette(PAL2,SEGALOGOPNG.palette->data);
        VDP_drawImage(BG_B, &SEGALOGOPNG,11,11);
////=====================================================///
        PAL_fadeIn(0, 63, palette_full, 100, FALSE);
        XGM_setPCM(SFX_SEGA, SegaSFX, sizeof(SegaSFX));
        XGM_startPlayPCM(SFX_SEGA,1,SOUND_PCM_CH2);
        waitMs(2000);
        PAL_fadeOut(0, 16, 100, FALSE);
        waitMs(1000);
        Menu();
}

///<=====MENU======>// Initializes game state 1 (Menu).
void Menu(){
        XGM_setLoopNumber(-1);
        XGM_startPlay(&TitleTrack);
        VDP_clearPlane(BG_A, TRUE);
        VDP_clearPlane(BG_B, TRUE);

        memcpy(&palette_full[0],TITLE.palette->data,16*2);
        memcpy(&palette_full[8],BACKGROUNDA.palette->data,16*2);
        memcpy(&palette_full[16],BLOCKS.palette->data,16*2);

        VDP_setPalette(PAL3,BACKGROUNDA.palette->data);
        VDP_setPalette(PAL2,Player1ALL.palette->data);
        VDP_setPalette(PAL1,BLOCKS.palette->data);

        VDP_drawImageEx(BG_B, &BACKGROUNDA,TILE_ATTR_FULL(PAL3,0,FALSE,FALSE, 140), 0, 0,FALSE,FALSE);
        VDP_drawImageEx(BG_B, &BACKGROUNDB,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE, 200), 0, 10,FALSE,FALSE);
        VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);

        VDP_drawImageEx(BG_A, &TITLE,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,620), 12, 7,FALSE,FALSE);
        VDP_drawImageEx(BG_A, &STARTTITLE,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,720), 12, 16,FALSE,FALSE);
        VDP_drawImageEx(BG_A, &CREATORTITLE,TILE_ATTR_FULL(PAL2,0,FALSE,FALSE,770), 35, 26,FALSE,FALSE);

        PAL_fadeIn(0,32, palette_full, 100, FALSE);
        waitMs(1000);
////================================================///
        StateGame=1;
////================================================///
}

///<=======GAME====>// Initializes game state 2 (Game).
void InitGame(){
    //=======================//
    XGM_stopPlay(&TitleTrack);
    VDP_setTextPalette(PAL0);
    PAL_fadeOut(0, 63, 100, FALSE);
    waitMs(1000);
    VDP_clearPlane(BG_B,TRUE);
    VDP_clearPlane(BG_A, TRUE);
    XGM_setLoopNumber(-1);
////================================///
        Player();
        SpawnDeObjectos();
        Interfaces();
        ActualizarPuntaje();
        Enemy();
        Maps();
////================================///
        waitMs(5000);
        XGM_startPlay(&GameTrack);
        StateGame=2;
////================================///
}

///====GAMEMANAGER====/// Manage which player wins in each game.
void GameManager(){
    if(Score>=350 && Player2Ingame==FALSE){
        StateGame=3;
        VDP_drawText("-Player_1 WIN-",12,10);
        VDP_drawText(GameOvertext,7,11);
    }else if(Score>=350 && Player2Ingame==TRUE){
        StateGame=3;
        VDP_drawText("-Player_1 WIN-",12,9);
        VDP_drawText("-Player_2 LOSE-",12,10);
        VDP_drawText(GameOvertext,7,11);
    }else if (Score_2>=350){
        StateGame=3;
        VDP_drawText("-Player_1 LOSE-",12,9);
        VDP_drawText("-Player_2 WIN-",12,10);
        VDP_drawText(GameOvertext,7,11);
    }
}

///<=====GAME OVER And TRY AGAIN====>/// If we reach the final score, we will get this gameover.
void GameOver(){
    VDP_clearText(30,1,12);
    VDP_clearText(1,1,12);
    //If Player2 is active//
    if(Player2Ingame==TRUE){
        player_pos_x2= 200;
        player_vel_x2= 0;
        player_y2 = FIX16(155);
        Score_2 = 0;
        ActualizarPuntaje2();
    }
    Score = 0;
    ActualizarPuntaje();
    //GAMEOVERTEXT
    VDP_clearText(12,9,20);
    VDP_clearText(12,10,20);
    VDP_clearText(7,11,25);
    player_pos_x= 84;
    player_vel_x= 0;
    player_y = FIX16(155);
    EnemyX = 340;
    EnemyX2 = -30;
    waitMs(2000);
////////////////////////////
    StateGame = 2;
}

///===DIFICULT===/// Manage the enemy that will appear after reaching a certain score.
void Dificultad(){
    if(Score<=0){
        Hard = FALSE;
    }else if((Score>=60 || Score_2>=60) && Hard==FALSE){
        Enemy2();
        Hard = TRUE;
    }
}

///===INTERFACES===/// It is the interface within the State_Game=2 game instance.
void Interfaces(){
    VDP_drawText("Player_1",1,0);
    VDP_drawText("Press START",28,0);
    VDP_drawText("GOAL:350",15,1);
}

///===PLAYER 1===/// Create and set the player 1 color palettes.
void Player(){
  //=====SPRITE=======//
  VDP_setPalette(PAL2,Player1ALL.palette->data);
  player = SPR_addSprite(&Player1ALL,player_pos_x,fix16ToInt(player_y),TILE_ATTR(PAL2,TRUE, FALSE, FALSE));
}

///=PLAYER POSITION 1=/// Manages collisions, movements and others of player 1.
void positionPlayer(){

	player_pos_x += player_vel_x;
	player_y = fix16Add(player_y,player_vel_yz);

	SPR_setPosition(player,player_pos_x,fix16ToInt(player_y));

///Gravedad/Caida del Personaje///
    if(jumping == TRUE){
        player_vel_yz = fix16Add(player_vel_yz, gravity);
    }

//COLISION CON ENEMIGO//
if(player_pos_x <= EnemyX + 12 && player_pos_x + 16 >= EnemyX){
            if(fix16ToInt(player_y) <= EnemyY + 12 && fix16ToInt(player_y) + 16 >= EnemyY){
                SPR_setAnim(player,0);
                Score--;
                ActualizarPuntaje();
                if(Score<=0){
                    Score = 0;
                    ActualizarPuntaje();
                }
            }
    }

//COLISION CON ENEMIGO 2//
if(player_pos_x <= EnemyX2 + 12 && player_pos_x + 16 >= EnemyX2){
            if(fix16ToInt(player_y) <= EnemyY2 + 12 && fix16ToInt(player_y) + 16 >= EnemyY2){
                SPR_setAnim(player,0);
                Score--;
                ActualizarPuntaje();
                if(Score<=0){
                    Score = 0;
                    ActualizarPuntaje();
                }
            }
    }

//COLISION CON OBJETOS//
if(player_pos_x <= Objects.ObjetoX + 8 && player_pos_x + 8 >= Objects.ObjetoX){
            if(fix16ToInt(player_y) <= Objects.ObjetoY + 16 && fix16ToInt(player_y) + 16 >= Objects.ObjetoY){
                Score += 10;
                SPR_setAnim(object,1);
                SPR_releaseSprite(object);
                XGM_setPCM(SFX_CRASH, Cristal, sizeof(Cristal));
                XGM_startPlayPCM(SFX_CRASH,1,SOUND_PCM_CH2);
            ///========================//
                ActualizarPuntaje();
                SpawnDeObjectos();
            }
    }

//COLISIONES GENERALES//
        //Primera Plataforma//
        if(player_pos_x <= 100 + 250 && player_pos_x + 16 >= 0 &&(fix16ToInt(player_y)<= 200 && fix16ToInt(player_y) + 16 >= 200) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(184);
            jumping=FALSE;
        //Segunda Plataforma//
        }else if(player_pos_x <= 52 && player_pos_x + 16 >= 0 &&(fix16ToInt(player_y)<= 158 && fix16ToInt(player_y) + 16 >= 160) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(144);
            jumping=FALSE;
        //Tercera Plataforma//
        }else if(player_pos_x <= 100 + 224 && player_pos_x + 16 >= 270 &&(fix16ToInt(player_y)<= 158 && fix16ToInt(player_y) + 16 >= 160) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(144);
            jumping=FALSE;
        //Cuarta Plataforma//
        }else if(player_pos_x <= 54 && player_pos_x + 16 >= 0 &&(fix16ToInt(player_y)<= 80 && fix16ToInt(player_y) + 16 >= 72) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(56);
            jumping=FALSE;
        //Quinta Plataforma//
        }else if(player_pos_x <= 100 + 224 && player_pos_x + 16 >= 270 &&(fix16ToInt(player_y)<= 80 && fix16ToInt(player_y) + 16 >= 72) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(56);
            jumping=FALSE;
        //Sexta Plataforma//
        }else if(player_pos_x <= 112 && player_pos_x + 16 >= 60 &&(fix16ToInt(player_y)<= 110 && fix16ToInt(player_y) + 16 >= 120) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(104);
            jumping=FALSE;
        //Septima Plataforma//
        }else if(player_pos_x <= 240 && player_pos_x + 16 >= 188 &&(fix16ToInt(player_y)<= 140 && fix16ToInt(player_y) + 16 >= 128) && jumping==TRUE){
            player_vel_yz = FIX16(0);
            player_y = intToFix16(112);
            jumping=FALSE;
        }else{
            jumping=TRUE;
        }

//Checkea las colisiones de pantalla con el jugador//
    if(player_pos_x < LEFT_EDGE) player_pos_x = LEFT_EDGE;
    if(player_pos_x + 16 > RIGHT_EDGE) player_pos_x = RIGHT_EDGE - 16;
}

///===PLAYER 2===/// Create and set the player 2 color palettes.
void Player2(){
//=====SPRITE=======//
    player2 = SPR_addSprite(&Player2ALL,player_pos_x2,fix16ToInt(player_y2),TILE_ATTR(PAL3,TRUE, FALSE, FALSE));
    VDP_clearText(28,0,18);
    VDP_drawText("Player_2",31,0);
    ActualizarPuntaje2();
}

///=PLAYER POSITION 2=/// Manages collisions, movements and others of player 2.
void positionPlayer2(){

	player_pos_x2 += player_vel_x2;
	player_y2 = fix16Add(player_y2,player_vel_yz2);

	SPR_setPosition(player2,player_pos_x2,fix16ToInt(player_y2));

///Gravedad/Caida del Personaje///
    if(jumping_2 == TRUE){
        player_vel_yz2 = fix16Add(player_vel_yz2, gravity2);
    }

//COLISION CON ENEMIGO//
if(player_pos_x2 <= EnemyX + 12 && player_pos_x2 + 16 >= EnemyX){
            if(fix16ToInt(player_y2) <= EnemyY + 12 && fix16ToInt(player_y2) + 16 >= EnemyY){
                SPR_setAnim(player2,0);
                Score_2--;
                ActualizarPuntaje2();
                if(Score_2<=0){
                    Score_2 = 0;
                    ActualizarPuntaje2();
                }
            }
    }

//COLISION CON ENEMIGO 2//
if(player_pos_x2 <= EnemyX2 + 12 && player_pos_x2 + 16 >= EnemyX2){
            if(fix16ToInt(player_y2) <= EnemyY2 + 12 && fix16ToInt(player_y2) + 16 >= EnemyY2){
                SPR_setAnim(player2,0);
                Score_2--;
                ActualizarPuntaje2();
                if(Score_2<=0){
                    Score_2 = 0;
                    ActualizarPuntaje2();
                }
            }
    }

//COLISION CON OBJETOS//
    if(player_pos_x2 <= Objects.ObjetoX + 8 && player_pos_x2 + 8 >= Objects.ObjetoX){
            if(fix16ToInt(player_y2) <= Objects.ObjetoY + 16 && fix16ToInt(player_y2) + 16 >= Objects.ObjetoY){
                Score_2 += 10;
                SPR_setAnim(object,1);
                SPR_releaseSprite(object);
                XGM_setPCM(SFX_CRASH, Cristal, sizeof(Cristal));
                XGM_startPlayPCM(SFX_CRASH,1,SOUND_PCM_CH2);
            ///========================//
                ActualizarPuntaje2();
                SpawnDeObjectos();
            }
    }

//COLISIONES GENERALES//
        //Primera Plataforma//
        if(player_pos_x2 <= 100 + 250 && player_pos_x2 + 16 >= 0 &&(fix16ToInt(player_y2)<= 200 && fix16ToInt(player_y2) + 16 >= 200) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(184);
            jumping_2=FALSE;
        //Segunda Plataforma//
        }else if(player_pos_x2 <= 52 && player_pos_x2 + 16 >= 0 &&(fix16ToInt(player_y2)<= 158 && fix16ToInt(player_y2) + 16 >= 160) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(144);
            jumping_2=FALSE;
        //Tercera Plataforma//
        }else if(player_pos_x2 <= 100 + 224 && player_pos_x2 + 16 >= 270 &&(fix16ToInt(player_y2)<= 158 && fix16ToInt(player_y2) + 16 >= 160) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(144);
            jumping_2=FALSE;
        //Cuarta Plataforma//
        }else if(player_pos_x2 <= 54 && player_pos_x2 + 16 >= 0 &&(fix16ToInt(player_y2)<= 80 && fix16ToInt(player_y2) + 16 >= 72) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(56);
            jumping_2=FALSE;
        //Quinta Plataforma//
        }else if(player_pos_x2 <= 100 + 224 && player_pos_x2 + 16 >= 270 &&(fix16ToInt(player_y2)<= 80 && fix16ToInt(player_y2) + 16 >= 72) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(56);
            jumping_2=FALSE;
        //Sexta Plataforma//
        }else if(player_pos_x2 <= 112 && player_pos_x2 + 16 >= 60 &&(fix16ToInt(player_y2)<= 110 && fix16ToInt(player_y2) + 16 >= 120) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(104);
            jumping_2=FALSE;
        //Septima Plataforma//
        }else if(player_pos_x2 <= 240 && player_pos_x2 + 16 >= 188 &&(fix16ToInt(player_y2)<= 140 && fix16ToInt(player_y2) + 16 >= 128) && jumping_2==TRUE){
            player_vel_yz2 = FIX16(0);
            player_y2 = intToFix16(112);
            jumping_2=FALSE;
        }else{
            jumping_2=TRUE;
        }

//Checkea las colisiones de pantalla con el jugador//
    if(player_pos_x2 < LEFT_EDGE) player_pos_x2 = LEFT_EDGE;
    if(player_pos_x2 + 16 > RIGHT_EDGE) player_pos_x2 = RIGHT_EDGE - 16;
}

///COLECTABLE OBJECTS// Creates collectable objects that are called from Spawn Objects.
void Object(int oX,int oY){
object = SPR_addSprite(&ObjectALL,oX,oY,TILE_ATTR(PAL2, FALSE, FALSE, FALSE));
SPR_setAnim(object,0);
}

///ENEMY/// Create the enemy 1 textures.
void Enemy(){
    enemy = SPR_addSprite(&EnemyALL,EnemyX,EnemyY,TILE_ATTR(PAL2,0, FALSE, FALSE));
}

///ENEMY2/// Create the enemy 2 textures.
void Enemy2(){
    enemy2 = SPR_addSprite(&EnemyALL,EnemyX2,EnemyY2,TILE_ATTR(PAL2,0, FALSE, FALSE));
}

///ENEMY MOVE/// Contains the movements and oscillation of Enemy 1.
void EnemyMove(){
///=====Propieties of Angle=====///
    int velocidadmovx;
    int acelerador = 3;     //modificador el mov sinoidal (CAMBIALO PARA PROBAR)
    int mod_amplitud = 1;   //modificador el mov sinoidal (CAMBIALO PARA PROBAR)
///===========ColisionFinal======================/////
    if(EnemyX>=360){ChargeMove=TRUE;}else if(EnemyX<=-65){ChargeMove=FALSE;}
///===================Charge of Move========================/////
    if(ChargeMove==TRUE){
        velocidadmovx=4;
        EnemyX-= velocidadmovx;
        mod_amplitud=2;
    }else{
        velocidadmovx=3;
        EnemyX+= velocidadmovx;
        mod_amplitud=1;
    }
///===============Position Of Enemy====================///
    EnemyY= CONST + sinFix16(EnemyX* acelerador)* mod_amplitud;
    SPR_setPosition(enemy,EnemyX,EnemyY);
}

//===ENEMY2 MOVE===// Contains the movements and oscillation of Enemy 2.
void EnemyMove2(){
///=====Propieties of Angle=====///
    int velocidadmovx;
    int acelerador = 3;     //modificador el mov sinoidal (CAMBIALO PARA PROBAR)
    int mod_amplitud = 1;   //modificador el mov sinoidal (CAMBIALO PARA PROBAR)
///===========ColisionFinal======================/////
    if(EnemyX2>=360){ChargeMove2=TRUE;}else if(EnemyX2<=-65){ChargeMove2=FALSE;}
///===================Charge of Move========================/////
    if(ChargeMove2==TRUE){
        velocidadmovx=5;
        EnemyX2-= velocidadmovx;
        mod_amplitud=1;
    }else{
        velocidadmovx=4;
        EnemyX2+= velocidadmovx;
        mod_amplitud=1;
    }
///===============Position Of Enemy====================///
    EnemyY2= CONST + sinFix16(EnemyX2* acelerador)* mod_amplitud;
    SPR_setPosition(enemy2,EnemyX2,EnemyY2);
}

///UPDATE POINTS/// Update player 1's score.
void ActualizarPuntaje(){
    sprintf(Hud_string,"SCORE: %d ",Score);
    VDP_drawText(Hud_string,1,1);
}

///UPDATE POINTS 2/// Update player 2's score.
void ActualizarPuntaje2(){
    sprintf(Hud_string2,"SCORE: %d ",Score_2);
    VDP_drawText(Hud_string2,30,1);
}

///=====MAP=====/// Create the mapping tile, and draw the backgrounds.
void Maps(){
///////////////////////////////////
VDP_setPalette(PAL3,BACKGROUNDA.palette->data);
VDP_drawImageEx(BG_B, &BACKGROUNDA,TILE_ATTR_FULL(PAL3,0,FALSE,FALSE, 100), 0, 0,FALSE,TRUE);
VDP_drawImageEx(BG_B, &BACKGROUNDB,TILE_ATTR_FULL(PAL1,0,FALSE,FALSE, 200), 0, 12,FALSE,TRUE);
VDP_setScrollingMode(HSCROLL_PLANE,VSCROLL_PLANE);
///////////////////////////////////////
VDP_loadTileSet(BLOCKS.tileset, 1, DMA);
VDP_setPalette(PAL1,BLOCKS.palette->data);
////////////////////////////////////////////
u8 x = 0;
u8 y = 0;
u8 t = 0;
////////////
///////////////////
 for(y = 0; y < 23; y++){
    for (x = 0; x < 42; x++){
            t = level1[y][x];
            VDP_setTileMapXY(BG_A, TILE_ATTR_FULL(PAL1, 0, FALSE, FALSE, t), x, y + 37);
        }
    }
}

///SPAWN// Spawn a random object into different positions with a switch, taking into account the Rand variable.
void SpawnDeObjectos(int Rand){
Rand = (random() % (7-1+2))+1;
switch(Rand){
    case 1:Objects.ObjetoX=150; Objects.ObjetoY=50;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 2:Objects.ObjetoX=25; Objects.ObjetoY=140;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 3:Objects.ObjetoX=286; Objects.ObjetoY=140;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 4:Objects.ObjetoX=286; Objects.ObjetoY=182;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 5:Objects.ObjetoX=25; Objects.ObjetoY=182;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 6:Objects.ObjetoX=25; Objects.ObjetoY=55;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 7:Objects.ObjetoX=286; Objects.ObjetoY=55;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 8:Objects.ObjetoX=85; Objects.ObjetoY=100;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    case 9:Objects.ObjetoX=240; Objects.ObjetoY=100;
    Object(Objects.ObjetoX,Objects.ObjetoY);
    break;
    }
}
