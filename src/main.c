#include <custom_types.h>
#include <symbols.h>
#include <common.h>
#include <buttons.h>
#include <hashcodes.h>

long color_white       = 0x80808080;
long color_light_red   = 0x80505080;
long color_light_green = 0x50805080;
long color_light_blue  = 0x50508080;

int* textGUI;
EXRect mapInfoRect = {12, 100, 400, 50};

EXVector somePlace = {108, 0, -70, 0};
EXVector zeroVec = {0, 0, 0, 0};

bool hudEnabled = false;
bool scanEnabled = false;

int currMap = 0;
int currStartPoint = 0;
int currPlayer = Player_Spyro;

int GetSpyroStartPoint(int* mapPtr) {
    int mapID = getGenericStructInt(mapPtr, 0xc8);
    
    return getGenericStructInt(&startPoints, mapID*MAP_STATE_SIZE);
}

void MenuControls() {
    //BROWSE MAPS
    if (P2_IsButtonsJustPressed(dpad_right)) {
        currMap++;
        if (currMap > NUM_MAPS-1) {
            currMap = 0;
        }
    }
    if (P2_IsButtonsJustPressed(dpad_left)) {
        currMap--;
        if (currMap < 0) {
            currMap = NUM_MAPS-1;
        }
    }
    //BROWSE STARTPOINTS
    if (P2_IsButtonsJustPressed(dpad_up)) {
        currStartPoint++;
        if (currStartPoint > 199) {
            currStartPoint = 0;
        }
    }
    if (P2_IsButtonsJustPressed(dpad_down)) {
        currStartPoint--;
        if (currStartPoint < 0) {
            currStartPoint = 199;
        }
    }
    //LOAD MAP
    if (P2_IsButtonsJustPressed(a_button)) {
        int geoHash = getGenericStructInt(gMapList[currMap], 0xdc);
        int mapHash = getGenericStructInt(gMapList[currMap], 0xe0);

        bool success = GoToMap(&gGameLoop, geoHash, currStartPoint | 0x4A000000, mapHash);
        InGamePrintf("%d\n", success);
    }
    //GO TO CURRENT MAP & STARTPOINT
    if (P2_IsButtonsJustPressed(x_button)) {
        int* spyroMap = GetSpyroMap(0);
        int index = getGenericStructInt(spyroMap, 0xc8);

        currMap = index;
        int SP = GetSpyroStartPoint(spyroMap);
        if (SP == 0xFFFFFFFF) {
            currStartPoint = 0;
        } else {
            currStartPoint = SP & 0xFFFF;
        }
    }
    //CLEAR MAP BITHEAP
    if (P2_IsButtonsJustPressed(z_button)) {
        Map_ClearBitHeap(gMapList[currMap]);
        //Map_AddPlayer(gMapList[currMap], &somePlace, &zeroVec);
    }
    
    //BROWSE CHARACTERS
    if (P2_IsButtonsJustPressed(l_button)) {
        currPlayer--;
        if (currPlayer < Player_Spyro) {
            currPlayer = NUM_PLAYERS-1;
        }

        Map_SetLastStartPoint(GetSpyroMap(0), currStartPoint | 0x4A000000, currPlayer);
    }
    if (P2_IsButtonsJustPressed(r_button)) {
        currPlayer++;
        if (currPlayer > NUM_PLAYERS-1) {
            currPlayer = Player_Spyro;
        }

        Map_SetLastStartPoint(GetSpyroMap(0), currStartPoint | 0x4A000000, currPlayer);
    }
    
}

void drawGUIText(int* element, char* wText, char* pText, EXRect* rect, long col) {
    EXRect dropshadow = {
        rect->x+2,
        rect->y+2,
        rect->w,
        rect->h
    };

    long shadowColor = 0x00000080;

    GUI_Item_DrawText(textGUI, gpPanelWnd, wText, pText, &dropshadow, &shadowColor);
    GUI_Item_DrawText(textGUI, gpPanelWnd, wText, pText, rect, col);
}

void printMap(int* mapPtr) {

    int startY = mapInfoRect.y;
    int spacing = 20;

    char* startPointString[10];
    InGameSPrintf(startPointString, "StartPoint: %x\n", currStartPoint | 0x4A000000);
    drawGUIText(textGUI, 0, startPointString, &mapInfoRect, &color_white);
    if (((currStartPoint | 0x4A000000) == GetSpyroStartPoint(GetSpyroMap(0)))
     && (mapPtr == GetSpyroMap(0))) {
        drawGUIText(textGUI, 0, "                                (Current)", &mapInfoRect, &color_light_blue);
    }
    mapInfoRect.y += spacing;

    char* playerString[10];
    InGameSPrintf(playerString, "Character: %s\n", PLAYER_STRINGS[currPlayer]);
    drawGUIText(textGUI, 0, playerString, &mapInfoRect, &color_white);
    mapInfoRect.y += spacing;

    int index = getGenericStructInt(mapPtr, 0xc8);
    char* indexString[3];
    InGameSPrintf(indexString, "Map %d/%d\n", index, NUM_MAPS-1);
    drawGUIText(textGUI, 0, indexString, &mapInfoRect, &color_white);
    if (mapPtr == GetSpyroMap(0)) {
        drawGUIText(textGUI, 0, "                (Current)", &mapInfoRect, &color_light_blue);
    }
    mapInfoRect.y += spacing;

    drawGUIText(textGUI, 0, MAP_STRINGS[index], &mapInfoRect, &color_white);
    mapInfoRect.y += spacing;

    int geoHash = getGenericStructInt(mapPtr, 0xdc);
    char* geoHashString[50];
    InGameSPrintf(geoHashString, "File: %x\n", geoHash);
    drawGUIText(textGUI, 0, geoHashString, &mapInfoRect, &color_white);
    mapInfoRect.y += spacing;

    int mapHash = getGenericStructInt(mapPtr, 0xe0);
    if (mapHash != 0) {
        char* mapHashString[50];
        InGameSPrintf(mapHashString, "Map: %x\n", mapHash);
        drawGUIText(textGUI, 0, mapHashString, &mapInfoRect, &color_white);
    }
    mapInfoRect.y += spacing;
    
    long realmNameHash = Map_RealmName(mapPtr);
    char* realmName = GetText(&gGameText, realmNameHash, 0, 0);
    drawGUIText(textGUI, realmName, 0, &mapInfoRect, &color_white);
    mapInfoRect.y += spacing;

    long levelNameHash = Map_LevelName(mapPtr);
    char* levelName = GetText(&gGameText, levelNameHash, 0, 0);
    drawGUIText(textGUI, levelName, 0, &mapInfoRect, &color_white);
    mapInfoRect.y += spacing*2;

    if (scanEnabled) {
        drawGUIText(textGUI, 0, "ScanMode: On", &mapInfoRect, &color_light_green);
    } else {
        drawGUIText(textGUI, 0, "ScanMode: Off", &mapInfoRect, &color_light_red);
    }

    mapInfoRect.y = startY;

    //XWnd_SetText(gpPanelWnd, HT_File_Panel, HT_Font_Test, &color_white, 1, 2);
    //XWnd_TextPrint(gpPanelWnd, c);
}

void MainHook(void)
{
    if (textGUI == 0) {
        textGUI = CreateGUI_Item();
        *(textGUI + 0x57) = 0; //Set text alignment (top-left)

        InGamePrintf("Created GUI Item at address %x\n", textGUI);
    }
    
    if (P2_IsButtonsJustPressed(y_button)) {
        hudEnabled = !hudEnabled;
    }
    if (hudEnabled) {
        MenuControls();
        printMap(gMapList[currMap]);
    }
    if (P2_IsButtonsJustPressed(start)) {
        RestartGame(gPlayerState);
    }
    
    //printMap(GetSpyroMap(0));

    //char* c = GetText(&gGameText, HT_Text_Realm1, 0, 0);
    //drawGUIText(textGUI, c, 0, &mapInfoRect, &color_white);

    //if (gpPlayerItem != 0) {
    //    drawPlayerPos();
    //}
    
    //XWnd_SetText(gpPanelWnd, HT_File_Panel, HT_Font_Test, &color_white, 1, 2);
    //XWnd_TextPrint(gpPanelWnd, c);
}

bool ScanHook(void) {
    if (P2_IsButtonsJustPressed(b_button)) {
        scanEnabled = !scanEnabled;
    }

    if (scanEnabled) {
        return P1_IsButtonsJustPressed(z_button);
    } else {
        return false;
    }
}