//
// Created by Sayan on 17-07-2023.
//

#ifndef COOLESP_IMPORT_H
#define COOLESP_IMPORT_H


#include <jni.h>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <sys/mman.h>
#include <android/log.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <cerrno>
#include <sys/un.h>
#include <cstring>
#include <string>
#include <cmath>
#include "imgui/imgui.h"


bool isPlayerDist = true,
isEsp = true,
isPlayerHealth = true,
isSkelton = true,
isaimbot = false,
isDataReciving = false,
isr360Alert =true,
isAimKnocked =true,
isBulletTrack = false,
isItems = false,
isvehcile = false;
//aimbot
float fov = 200;
int target = 1;

int fontsize = 16;
int textpos = 14;
int teamidpos = 68;

float radarLocation = 800.f, radarLocation2 = 1650.f;
bool showtouch = true;
static float window_scale = 0.67f;


ImVec2 pushToScreenBorder(Vec2 Pos, Vec2 screen, int offset) {
    int x = (int)Pos.x;
    int y = (int)Pos.y;
    if (Pos.y < 0) {
        // top
        y = -offset;
    }
    if (Pos.x > screen.x) {
        // right
        x = (int)screen.x + offset;
    }
    if (Pos.y > screen.y) {
        // bottom
        y = (int)screen.y + offset;
    }
    if (Pos.x < 0) {
        // left
        x = -offset;
    }
    return ImVec2(x, y);
}

bool isOutsideSafeZone(Vec2 pos, Vec2 screen) {
    if (pos.y < 0) {
        return true;
    }
    if (pos.x > screen.x) {
        return true;
    }
    if (pos.y > screen.y) {
        return true;
    }
    return pos.x < 0;
}

void SaveIni() {
    FILE *fp;
    if ((fp = fopen("/data/data/com.abenk.in/Config.txt", "wt+")) != nullptr) {
        char temp[2048];
        sprintf(temp,
                "顯示方框=%d\n方框類型=%d\n顯示骨骼=%d\n顯示射綫=%d\n顯示信息=%d\n地圖雷達=%d\n顯示載具=%d\n手雷預警=%d",
                fontsize, textpos, teamidpos,isEsp,isPlayerHealth,isSkelton,isaimbot,isAimKnocked);
        fputs(temp, fp);
        sprintf(temp,
                "顯示步槍=%d\n顯示衝鋒槍=%d\n顯示狙擊槍=%d",
                isvehcile,isItems,target);
        fputs(temp, fp);
    }
    fclose(fp);
}

void GetIni() {
    FILE *fp;
    if ((fp = fopen("/data/data/com.abenk.in/Config.txt", "r")) != nullptr) {
        char temp[2048];
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            fontsize = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            textpos = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            teamidpos = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isEsp = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isPlayerHealth = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isSkelton = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isaimbot = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isAimKnocked = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isAimKnocked = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            target = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isvehcile = atoi(strstr(temp, "=") + 1);
        if (fgets(temp, sizeof(temp), fp) != nullptr)
            isItems = atoi(strstr(temp, "=") + 1);
        fclose(fp);
    }
}

#endif //COOLESP_IMPORT_H
