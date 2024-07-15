#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include "Game.h"
#include "../../files/people.h"


void gameNew(Game* game_obj){

    game_obj->frames = 0;
    game_obj->gEngine = newEngine();
    game_obj->init = gameIntit;
    game_obj->checkTreasureChest = gameCheckTreasureChest;
    game_obj->start = gameStart;
    game_obj->readInput = gameReadInput;
    game_obj->update = gameUpdate;
    game_obj->render = gameRender;
}

void gameIntit(Game* game_obj){
    
    int player1_character_type = 0;
    int player2_character_type = 0;
    //--Choose Character--//





    //load charactor image
    //0->sasge
    if(player1_character_type == 0){
        extern const uint16_t Sasge[6][2500];
        Engine_Render_addImage(game_obj->gEngine, "person1", Sasge[0], 50, 50);
    }
    //1->
    //...




    //----//


    //--Load Resources--//

    Engine_Render_addImage(game_obj->gEngine, "block", block, 80, 15);
    Engine_Render_addImage(game_obj->gEngine, "ground", block, 320, 15);
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/adf_music.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/gunshot.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/metalpipe.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/potai.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/yamete.mp3");
    Engine_Audio_addAudio(game_obj->gEngine, "/spiffs/guncock.mp3");
    Engine_Audio_setVolume(game_obj->gEngine, 0);
    
    game_obj->background = Engine_Render_newObject(game_obj->gEngine, "background", 0, 0, 1);
    game_obj->ground = Engine_Render_newObject(game_obj->gEngine, "ground", 0, 225, 1);
    game_obj->block_1 = Engine_Render_newObject(game_obj->gEngine, "block", 20, 170, 1);
    game_obj->block_2 = Engine_Render_newObject(game_obj->gEngine, "block", 220, 170, 1);
    game_obj->block_3 = Engine_Render_newObject(game_obj->gEngine, "block", 60, 115, 1);
    game_obj->block_4 = Engine_Render_newObject(game_obj->gEngine, "block", 180, 115, 1);
    game_obj->block_5 = Engine_Render_newObject(game_obj->gEngine, "block", 120, 70, 1);
    
    //----//

}
void gameCheckTreasureChest(Game* game_obj);

void gameStart(Game* game_obj){

    newPerson(game_obj->player1, game_obj->gEngine, 1, 190);
    Engine_Render_addObject(game_obj->gEngine, game_obj->player1->mRenderObject);

}
void gameReadInput(Game* game_obj);
void gameUpdate(Game* game_obj){

    // 這兩個function我不確定要包在哪
    Engine_Detect(game_obj->gEngine);
    Engine_Audio_handleAudioEvents(game_obj->gEngine);
    //

    game_obj->player1->move((game_obj->player1));
    Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
    if(game_obj->frames%4==1){
        Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->player1->mRenderObject, "person2");
        Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
    }
    if(game_obj->frames%4==3){
        Engine_Render_changeObjectImage(game_obj->gEngine, game_obj->player1->mRenderObject, "person1");
        Engine_Render_render(game_obj->gEngine, game_obj->player1->mRenderObject);
    }


    game_obj->frames ++;
}
void gameRender(Game* game_obj){
    Engine_Render_update(game_obj->gEngine);
}
