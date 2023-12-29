#ifndef COMMON_H
#define COMMON_H
#include <custom_types.h>

#define MAP_STATE_SIZE 0x64
#define MAP_STATE_AMOUNT 200

enum Buttons
{
    dpad_up = 0b1,
    dpad_down = 0b10,
    dpad_left = 0b100,
    dpad_right = 0b1000,

    lanalog_up = 0b10000,
    lanalog_down = 0b100000,
    lanalog_left = 0b1000000,
    lanalog_right = 0b10000000,

    ranalog_up = 0b100000000,
    ranalog_down = 0b1000000000,
    ranalog_left = 0b10000000000,
    ranalog_right = 0b100000000000,

    b_button = 0b1000000000000,
    a_button = 0b10000000000000,
    x_button = 0b100000000000000,
    y_button = 0b1000000000000000,

    l3_unused = 0b10000000000000000,
    r3_unused = 0b100000000000000000,
    start = 0b1000000000000000000,
    select = 0b10000000000000000000,

    l_button = 0b100000000000000000000,
    l2_unused = 0b1000000000000000000000,
    r_button = 0b10000000000000000000000,
    z_button = 0b100000000000000000000000
};
typedef enum Buttons Buttons;

struct ButtonsBitfield
{
    byte dpad_up:1;
    byte dpad_down:1;
    byte dpad_left:1;
    byte dpad_right:1;

    byte lanalog_up:1;
    byte lanalog_down:1;
    byte lanalog_left:1;
    byte lanalog_right:1;

    byte ranalog_up:1;
    byte ranalog_down:1;
    byte ranalog_left:1;
    byte ranalog_right:1;

    byte b_button:1;
    byte a_button:1;
    byte x_button:1;
    byte y_button:1;

    byte l3_unused:1;
    byte r3_unused:1;
    byte start:1;
    byte select_button:1;

    byte l_button:1;
    byte l2_unused:1;
    byte r_button:1;
    byte z:1;
};
typedef struct ButtonsBitfield ButtonsBitfield;

struct EXVector
{
    float X;
    float Y;
    float Z;
    float W;
};
typedef struct EXVector EXVector;

struct EXRect
{
    int x;
    int y;
    int w;
    int h;
};
typedef struct EXRect EXRect;

struct CollectibleTally
{
    int DarkGems;
    int LightGems;
    int DragonEggs_Type1;
    int DragonEggs_Type2;
    int DragonEggs_Type3;
    int DragonEggs_Type4;
    int DragonEggs_Type5;
    int DragonEggs_Type6;
    int DragonEggs_Type7;
    int DragonEggs_Type8;
};
typedef struct CollectibleTally CollectibleTally;

struct LevelStat
{
    long StartPoint;
    int thing;
    int totalDarkGems;
    int totalDragonEggs;
    int pad[7];
    CollectibleTally tallies;
    int thing2[3];
};
typedef struct LevelStat LevelStat;

long getGenericStructLong(int* s, int offs) {
    return *((long*) ((char*) s + offs));
}
float getGenericStructFloat(int* s, int offs) {
    return *((float*) ((char*) s + offs));
}
int getGenericStructInt(int* s, int offs) {
    return *((int*) ((char*) s + offs));
}

enum Players
{
    Player_Undefined  = 0,
    Player_Spyro      = 1,
    Player_Hunter     = 2,
    Player_Sparx      = 3,
    Player_Blinky     = 4,
    Player_SgtByrd    = 5,
    Player_BallGadget = 6,
    Player_Ember      = 7,
    Player_Flame      = 8
};
typedef enum Players Players;

#define NUM_PLAYERS 9

const char *PLAYER_STRINGS[NUM_PLAYERS] = {
/* 0  */ "Undefined\n",
/* 1  */ "Spyro\n",
/* 2  */ "Hunter\n",
/* 3  */ "Sparx\n",
/* 4  */ "Blink\n",
/* 5  */ "Sgt. Byrd\n",
/* 6  */ "Ball Gadget\n",
/* 7  */ "Ember\n",
/* 8  */ "Flame\n"
};

#define NUM_MAPS 65

const char *MAP_STRINGS[NUM_MAPS] = {
/* 0  */ "Loading\n",
/* 1  */ "Test_SG (OLDFILE)\n",
/* 2  */ "MR1_Blk\n",
/* 3  */ "MR1_Sgt\n",
/* 4  */ "MR1_Spx\n",
/* 5  */ "MR1_Spy\n",
/* 6  */ "MR2_Blk\n",
/* 7  */ "MR2_Sgt\n",
/* 8  */ "MR2_Spx\n",
/* 9  */ "MR2_Spy\n",
/* 10 */ "MR3_Blk\n",
/* 11 */ "MR3_Sgt\n",
/* 12 */ "MR3_Spx\n",
/* 13 */ "MR3_Spy\n",
/* 14 */ "MR4_Blk\n",
/* 15 */ "MR4_Sgt\n",
/* 16 */ "MR4_Spx\n",
/* 17 */ "MR4_Spy\n",
/* 18 */ "Credits\n",
/* 19 */ "Realm2B\n",
/* 20 */ "Realm2C\n",
/* 21 */ "Realm2C (Ball Gadget)\n",
/* 22 */ "Realm1C\n",
/* 23 */ "Realm1B\n",
/* 24 */ "Realm1A\n",
/* 25 */ "R1LinkAB\n",
/* 26 */ "R1LinkAC\n",
/* 27 */ "Hogwarts\n",
/* 28 */ "Test_DP\n",
/* 29 */ "Test_SC\n",
/* 30 */ "Realm4D\n",
/* 31 */ "Realm3A\n",
/* 32 */ "Realm1Z\n",
/* 33 */ "Realm3C\n",
/* 34 */ "Realm4Z\n",
/* 35 */ "Realm3B\n",
/* 36 */ "PlayRoom\n",
/* 37 */ "Model\n",
/* 38 */ "Test_TL\n",
/* 39 */ "Test_PB\n",
/* 40 */ "Realm4E\n",
/* 41 */ "Realm3Z\n",
/* 42 */ "Test_MF\n",
/* 43 */ "Shop\n",
/* 44 */ "Realm4A\n",
/* 45 */ "Realm2A\n",
/* 46 */ "R2LinkAB\n",
/* 47 */ "R2LinkAC\n",
/* 48 */ "Test_JS\n",
/* 49 */ "Test_KA\n",
/* 50 */ "Test_NB (1)\n",
/* 51 */ "Test_NB (2)\n",
/* 52 */ "Test_SJ\n",
/* 53 */ "Test_WTS (OLDFILE)\n",
/* 54 */ "Test_Bch\n",
/* 55 */ "TestBall (OLDFILE)\n",
/* 56 */ "Titles\n",
/* 57 */ "R4LinkBC\n",
/* 58 */ "R4LinkCD\n",
/* 59 */ "R4LinkDE\n",
/* 60 */ "Realm4B\n",
/* 61 */ "Realm4C (Top)\n",
/* 62 */ "Realm4C (Ball Gadget)\n",
/* 63 */ "Realm4C (Bottom)\n",
/* 64 */ "Realm2Z\n"
};

#endif /* COMMON_H */
