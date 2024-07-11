#pragma once
#include "SymbolCharacterManager.h"
#include "Animation.h"
#include "Animations.h"
#include <unordered_map>


int CSymbolCharacterManager::GetAniIdChar(char char_) {
    unordered_map<char, int> char_to_ani_id = {
        {'0', ID_ANI_CHAR_0}, {'1', ID_ANI_CHAR_1}, {'2', ID_ANI_CHAR_2}, {'3', ID_ANI_CHAR_3},
        {'4', ID_ANI_CHAR_4}, {'5', ID_ANI_CHAR_5}, {'6', ID_ANI_CHAR_6}, {'7', ID_ANI_CHAR_7},
        {'8', ID_ANI_CHAR_8}, {'9', ID_ANI_CHAR_9}, {'A', ID_ANI_CHAR_A}, {'B', ID_ANI_CHAR_B},
        {'C', ID_ANI_CHAR_C}, {'D', ID_ANI_CHAR_D}, {'E', ID_ANI_CHAR_E}, {'F', ID_ANI_CHAR_F},
        {'G', ID_ANI_CHAR_G}, {'H', ID_ANI_CHAR_H}, {'I', ID_ANI_CHAR_I}, {'J', ID_ANI_CHAR_J},
        {'K', ID_ANI_CHAR_K}, {'L', ID_ANI_CHAR_L}, {'M', ID_ANI_CHAR_M}, {'N', ID_ANI_CHAR_N},
        {'O', ID_ANI_CHAR_O}, {'P', ID_ANI_CHAR_P}, {'Q', ID_ANI_CHAR_Q}, {'R', ID_ANI_CHAR_R},
        {'S', ID_ANI_CHAR_S}, {'T', ID_ANI_CHAR_T}, {'U', ID_ANI_CHAR_U}, {'V', ID_ANI_CHAR_V},
        {'W', ID_ANI_CHAR_W}, {'X', ID_ANI_CHAR_X}, {'Y', ID_ANI_CHAR_Y}, {'Z', ID_ANI_CHAR_Z},
        {'!', ID_ANI_CHAR_EXCLAMATION}, {'@', ID_ANI_CHAR_SHACKLE}
    };

    return  char_to_ani_id[char_];
}

int CSymbolCharacterManager::GetAniIdIcon(string icon) {
    unordered_map<string, int> icon_to_ani_id = {
        {"CLOCK", ID_ANI_CLOCK_ICON}, {"DOLAR", ID_ANI_DOLAR_ICON},
        {"LIFE", ID_ANI_LIFE_ICON}, {"X", ID_ANI_X_ICON},
        {"RED ARROW", ID_ANI_RED_ARROW_ICON}
    };

    return icon_to_ani_id[icon];
}

int CSymbolCharacterManager::GetAniIdNumber(int number) {
    return GetAniIdChar(number);
}

void CSymbolCharacterManager::RenderIcon(string icon, float x, float y) {
    int ani_id = GetAniIdIcon(icon);

    CAnimations::GetInstance()->Get(ani_id)->Render(x, y);

}

void CSymbolCharacterManager::RenderNumber(int number, float x, float y) {
    string str = to_string(number);

    if (str.length() < 0) {
        str = "0" + str;
    }

    for (int i = 0; i < str.length(); ++i) {
        int ani_id = GetAniIdChar(str[i]);
            CAnimations::GetInstance()->Get(ani_id)->Render(x + i * HUD_CHAR_BBOX_WIDTH, y + HUD_CHAR_BBOX_HEIGHT / 2);
    }
}

void CSymbolCharacterManager::RenderString(std::string str, float left, float top) {

    for (int i = 0; i < str.length(); ++i) {
        int ani_id = GetAniIdChar(str[i]);
            CAnimations::GetInstance()->Get(ani_id)->Render(left + i * HUD_CHAR_BBOX_WIDTH, top + HUD_CHAR_BBOX_HEIGHT / 2);
        
    }
}
