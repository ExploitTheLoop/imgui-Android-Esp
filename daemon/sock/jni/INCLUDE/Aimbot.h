//
// Created by Sayan on 28-07-2023.
//

#ifndef ANDROID_MOD_MENU_MASTER_AIMBOT_H
#define ANDROID_MOD_MENU_MASTER_AIMBOT_H
#include "INCLUDE/Logger.h"
struct WeaponInfo{
    float Pitch;
    float Yaw;
};
extern bool isAIM;
extern float aim_x,aim_y;
extern float push_x,push_y,Recoil;
extern bool isRunAim;
WeaponInfo GetWeaponInfo(char* MyHand);
void *aimThread(void *param);
void GetTouchPitch(char* MyHand,float Fov ,float distance);
extern float AimSpeed; //自瞄速度 min0 max300


#include "AimBot.h"
#include <string>
#include <unistd.h>
#include "TouchHelper.h"
#include <android/log.h>

bool isRunAim = false;


bool isAIM = false;
//int SlideX = 800;//自瞄初始点X min 0 max
//int SlideY = 1650;//自瞄初始点Y
static int aimLock = 0;
bool isDown = false;
static int screenX;
static int screenY;
static float ScrXH;
static float ScrYH;
bool bLock;
static float TargetX = 0;
static float TargetY = 0;

int AimSleep = 10; //min0 max100 自瞄延迟
float push_x = 0.f;
float push_y = 0.f;
float Recoil = 0.f;
float aim_x, aim_y;
float radarLocation = 800.f, radarLocation2 = 1650.f;
static bool aimbot = true;

float AimSpeed = 15.0f;//自瞄速度 min0 max300
float SpeedAim = 15.0f;//自瞄速度 min0 max300

void *aimThread(void *param) {

    int SlideX = radarLocation;
    int SlideY = radarLocation2;
    float tx = 0, ty = 0;
    screenX = (width > height ? height : width) * 2;
    screenY = (width < height ? height : width) * 2;
    ScrXH = screenX / 2;
    ScrYH = screenY / 2;
    while (true) {
        if (aimbot) {

            //这里是转换坐标，将屏幕坐标转为触摸坐标，因为触摸坐标是从屏幕竖立左上角开始的
            float zm_x = screenX - aim_y;
            float zm_y = aim_x;
            if (zm_x <= 0 || zm_x >= screenX || zm_y <= 0 || zm_y >= screenY) {
                isAIM = false;
            }
            if (SlideX <= 0 || SlideX >= screenX || SlideY <= 0 || SlideY >= screenY) {
                isAIM = false;
            }
            if (isAIM) {
                if (aimLock == 1) {
                    bLock = true;
                }
                if (isDown == false) {
                    Touch_Down((int) tx, (int) ty);
                    isDown = true;
                }
                if (zm_x <= 0 || zm_x >= screenX || zm_y <= 0 || zm_y >= screenY) {
                    continue;
                }
                if (zm_x > ScrXH) {
                    TargetX /= AimSpeed;
                    if (TargetX + ScrXH > ScrXH * 2)
                        TargetX = 0;
                }
                if (zm_x < ScrXH) {
                    TargetX /= AimSpeed;
                    if (TargetX + ScrXH < 0)
                        TargetX = 0;
                }
                if (zm_y > ScrYH) {
                    TargetY /= AimSpeed;
                    if (TargetY + ScrYH > ScrYH * 2)
                        TargetY = 0;
                }
                if (zm_y < ScrYH) {
                    TargetY = zm_y - ScrYH;
                    TargetY /= AimSpeed;
                    if (TargetY + ScrYH < 0)
                        TargetY = 0;
                }

                tx += TargetX;
                ty += TargetY;
                if (tx > screenX || tx < 0 || ty > screenY || ty < 0) {
                    // 只要滑屏达到了边界，直接还原至中心
                    tx = SlideX, ty = SlideY;
                    // 恢复变量
//                dev.Touch_Alloc();
                    Touch_Up();
                    // 抬起
                    Touch_Down((int) tx, (int) ty);
                    // 按下
                }
            } else {
                bLock = false;
                if (isDown == true) {
                    tx = SlideX, ty = SlideY;
                    // 恢复变量
//                dev.Touch_Alloc();
                    Touch_Up();
                    // 抬起
                    isDown = false;
                }
            }
            usleep(AimSleep * 9000);
        } else {
            usleep(2 * 1000);
        }
    }
    return NULL;
}

WeaponInfo GetWeaponInfo(char *MyHand) {
    WeaponInfo weaponInfo;
    weaponInfo.Pitch = 0;
    weaponInfo.Yaw = 0;
    if (strstr(MyHand, "AKM") != nullptr || strstr(MyHand, "M762") != nullptr) {
        weaponInfo.Pitch = 0;
        weaponInfo.Yaw = 0.15f;
    }
    if (strstr(MyHand, "M762") != nullptr) {
        weaponInfo.Pitch = -0.15;
        weaponInfo.Yaw = -0.05f;
    }
    if (strstr(MyHand, "Groza") != NULL) {
        weaponInfo.Pitch = 0;
        weaponInfo.Yaw = 0.1f;
    }
    if (strstr(MyHand, "M416") != nullptr || strstr(MyHand, "SCAR") != nullptr ||
        strstr(MyHand, "AUG") != nullptr) {
        weaponInfo.Pitch = -0.05f;
        weaponInfo.Yaw = -0.05f;
    }
    if (strstr(MyHand, "M249") != nullptr) {
        weaponInfo.Pitch = -0.1f;
        weaponInfo.Yaw = -0.1f;
    }
    if (strstr(MyHand, "DP28") != NULL) {
        weaponInfo.Pitch = -0.5;
        weaponInfo.Yaw = -0.1;
    }
    if (strstr(MyHand, "MG3") != NULL) {
        weaponInfo.Pitch = -0.5;
        weaponInfo.Yaw = -0.08;
    }
    return weaponInfo;
}

void GetTouchPitch(int WeaponID, float Fov) {
    //LOGE("FOV:%f",Fov);
    //LOGE("distance: %d",(int)distance);
    if ((int)Fov == 80) // no open scope
    {
        push_y = 0.7f;
        AimSpeed = 25.f;
    } else if ((int)Fov == 70 || (int)Fov == 75) //iron sight ( no use scope )
    {
        push_y=1.5f;
        /*if ((int)distance >= 0 && (int)distance <= 25){
            push_y = 1.0f;
        }
        else if ((int)distance >= 25 && (int)distance <= 50){
            push_y = 1.15f;
        }
        else if ((int)distance >= 50 && (int)distance <= 75){
            push_y = 1.2f;
        }
        else if ((int)distance >= 75 && (int)distance <= 100){
            push_y = 1.3f;
        }
        else if ((int)distance >= 100 && (int)distance <= 125){
            push_y = 1.35f;
        }
        else if ((int)distance >= 125 && (int)distance <= 150){
            push_y = 1.4f;
        }
        else if ((int)distance >= 150 && (int)distance <= 175){
            push_y = 1.6f;
        }
        else if ((int)distance >= 175 && (int)distance <= 200){
            push_y = 1.65f;
        }
        else if ((int)distance >= 200 && (int)distance <= 225){
            push_y = 1.7f;
        }
        else if ((int)distance >= 225 && (int)distance <= 250){
            push_y = 1.75f;
        }*/
        /*if (strstr(MyHand, "M762") != nullptr) {
            push_y = 3.f;
        }
        else if (strstr(MyHand, "DP28") != nullptr) {
            push_y = 1.f;
        }
        else if (strstr(MyHand, "M249") != nullptr) {
            push_y = 2.5f;
        }*/
        //if (AimSpeed > 20) {
        //    push_y -= 0.6f;
        //}

    } else if ((int)Fov == 55 || (int)Fov == 60) // Reddot
    {
        push_y = 2.0f;
        AimSpeed = 21.f;
        /*if ((int)distance >= 0 && (int)distance <= 25){
            push_y = 1.0f;
        }
        else if ((int)distance >= 25 && (int)distance <= 50){
            push_y = 1.2f;
        }
        else if ((int)distance >= 50 && (int)distance <= 75){
            push_y = 1.3f;
        }
        else if ((int)distance >= 75 && (int)distance <= 100){
            push_y = 1.4f;
        }
        else if ((int)distance >= 100 && (int)distance <= 125){
            push_y = 1.5f;
        }
        else if ((int)distance >= 125 && (int)distance <= 150){
            push_y = 1.65f;
        }
        else if ((int)distance >= 150 && (int)distance <= 175){
            push_y = 1.75f;
        }
        else if ((int)distance >= 175 && (int)distance <= 200){
            push_y = 1.85f;
        }
        else if ((int)distance >= 200 && (int)distance <= 225){
            push_y = 1.95f;
        }
        else if ((int)distance >= 225 && (int)distance <= 250){
            push_y = 2.0f;
        }
        else if ((int)distance >= 250 && (int)distance <= 300){
            push_y = 2.05f;
        }*/
    } else if ((int) Fov == 44)//2x
    {
        push_y = 2.5f;
        AimSpeed = 22.f;
        /*if ((int)distance >= 0 && (int)distance <= 25){
            push_y = 1.25f;
        }
        else if ((int)distance >= 25 && (int)distance <= 50){
            push_y = 1.35f;
        }
        else if ((int)distance >= 50 && (int)distance <= 75){
            push_y = 1.45f;
        }
        else if ((int)distance >= 75 && (int)distance <= 100){
            push_y = 1.55f;
        }
        else if ((int)distance >= 100 && (int)distance <= 125){
            push_y = 1.65f;
        }
        else if ((int)distance >= 125 && (int)distance <= 150){
            push_y = 1.75f;
        }
        else if ((int)distance >= 150 && (int)distance <= 175){
            push_y = 1.85f;
        }
        else if ((int)distance >= 175 && (int)distance <= 200){
            push_y = 1.95f;
        }
        else if ((int)distance >= 200 && (int)distance <= 225){
            push_y = 2.05f;
        }
        else if ((int)distance >= 225 && (int)distance <= 250){
            push_y = 2.1f;
        }
        else if ((int)distance >= 250 && (int)distance <= 300){
            push_y = 2.15f;
        }*/
    } else if ((int) Fov == 26)//3x
    {
        push_y = 3.0f;
        AimSpeed = 23.f;
    } else if ((int) Fov == 20)//4x
    {
        push_y = 3.65f;
        AimSpeed = 25.f;
    } else if ((int) Fov == 13)//6x
    {
        push_x = 0.f;
        push_y = 5.5f;
        AimSpeed = 30.f;
        if (WeaponID == 101001) { //AKM
            push_x = 0.8f;
            push_y = 7.5f;
        }
        if (WeaponID == 101008) { //M762
            push_x = -0.8f;
            push_y = 6.5f;
        }
    }
}

#endif //ANDROID_MOD_MENU_MASTER_AIMBOT_H
