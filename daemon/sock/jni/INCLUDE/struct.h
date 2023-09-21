#ifndef SHOOLIN_STRUCT_H
#define SHOOLIN_STRUCT_H

#include "support.h"
#include "init.h"
#include "Vector2.hpp"
#include "Vector3.hpp"

#define maxplayerCount 100
#define maxvehicleCount 50
#define maxitemsCount 400
#define maxgrenadeCount 10

//bullet track

struct FRotator {
    float Pitch;
    float Yaw;
    float Roll;
};

struct MinimalViewInfo {
    Vector3 Location;
    Vector3 LocationLocalSpace;
    FRotator Rotation;
    float FOV;
};

struct CameraCacheEntry {
    float TimeStamp;
    char chunks[0xC];
    MinimalViewInfo POV;
};

FRotator ToRotator(Vector3  LocalHeadPosition, struct Vec3  AimPosition) {
    Vector3 rotation = Vector3((LocalHeadPosition.X - AimPosition.X), (LocalHeadPosition.Y - AimPosition.Y), (LocalHeadPosition.Z - AimPosition.Z));

    FRotator newViewAngle = {0};

    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;

    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;

    return newViewAngle;
}

struct ShootWeaponBase {
    uintptr_t WeaponManagerComponent;
    uintptr_t CurrentWeaponReplicated;
    uintptr_t ShootWeaponEntityComponent;
    int bIsWeaponFiring;
    int bIsGunADS;

    ShootWeaponBase(uintptr_t LocalPlayer) {
        WeaponManagerComponent = getA(LocalPlayer + Offsets::WeaponManagerComponent);
        CurrentWeaponReplicated = getA(WeaponManagerComponent + Offsets::CurrWeapon);
        ShootWeaponEntityComponent = getA(CurrentWeaponReplicated + Offsets::ShootWeaponEntityComp);
        bIsWeaponFiring = Read<int>(LocalPlayer + Offsets::bIsWeaponFiring);
        bIsGunADS = Read<int>(LocalPlayer + Offsets::bIsGunADS);
    }

    float GetBulletFireSpeed() {
        if(ShootWeaponEntityComponent){
            return Read<float>(ShootWeaponEntityComponent + Offsets::BulletFireSpeed);
        }
        return 0;
    }
    bool isFiring(){
        return (bIsWeaponFiring != 0);
    }

    bool isADS(){
        return (bIsGunADS != 0);
    }

    bool isValid() {
        return (CurrentWeaponReplicated != 0);
    }
};


//esp sturct
struct PlayerBone {
    bool isBone = false;
    Vec2 neck;
    Vec2 cheast;
    Vec2 pelvis;
    Vec2 lSh;
    Vec2 rSh;
    Vec2 lElb;
    Vec2 rElb;
    Vec2 lWr;
    Vec2 rWr;
    Vec2 lTh;
    Vec2 rTh;
    Vec2 lKn;
    Vec2 rKn;
    Vec2 lAn;
    Vec2 rAn;
};

struct PlayerWeapon {
    bool isWeapon = false;
    int id;
    int ammo;
    int maxammo;
};

enum Mode {
    InitMode = 1,
    ESPMode = 2,
    HackMode = 3,
    StopMode = 4,
};

struct Options {
    int aimbotmode;
    int openState;
    int aimingState;
    bool tracingStatus;
    int priority;
    bool pour;
    int aimingRange;
};

struct radar {
    float x;
    float y;
};

struct Request {
    int Mode;
    Options options;
    radar Radar;
   // Memory memory;
    int ScreenWidth;
    int ScreenHeight;
};

struct VehicleData {
    char VehicleName[50];
    float Fuel;
    float Health;
    float Distance;
    Vec3 Location;
};

struct ItemData {
    char ItemName[50];
    float Distance;
    Vec3 Location;
};

struct GrenadeData {
    int type;
    float Distance;
    Vec3 Location;
};
struct SetValue {
    int mode;
    int type;
};




struct PlayerData {
    char PlayerNameByte[100];
    int TeamID;
    float Health;
    float Distance;
    bool isBot;
    Vec3 HeadLocation;
    PlayerWeapon Weapon;
    PlayerBone Bone;
};

struct Response {
    bool Success;
    int PlayerCount;
    int VehicleCount;
    int ItemsCount;
    int GrenadeCount;
    float fov;
    PlayerData Players[maxplayerCount];
    VehicleData Vehicles[maxvehicleCount];
    ItemData Items[maxitemsCount];
    GrenadeData Grenade[maxgrenadeCount];
};

#endif
