#include <thread>
#include "INCLUDE/struct.h"
#include "INCLUDE/Logger.h"
#include "INCLUDE/Aimbot.h"
#include "Offsets.h"

using namespace Offsets;
static pthread_t t2;
static int WeaponID = 0;


struct Actors {
	uint32_t Enc_1, Enc_2;
	uint32_t Enc_3, Enc_4;
};

struct Chunk {
	uint32_t val_1, val_2;
	uint32_t val_3, val_4;
};

uint32_t DecryptActorsArray(uint32_t uLevel, int Actors_Offset, int EncryptedActors_Offset) {
	if (uLevel < 0x10000000)
		return 0;
 
	if (Read<uint32_t>(uLevel + Actors_Offset) > 0)
		return uLevel + Actors_Offset;
 
	if (Read<uint32_t>(uLevel + EncryptedActors_Offset) > 0)
		return uLevel + EncryptedActors_Offset;
 
	auto AActors = Read<Actors>(uLevel + EncryptedActors_Offset + 0x0C);
 
	if (AActors.Enc_1 > 0) {
		auto Enc = Read<Chunk>(AActors.Enc_1 + 0x80);
 
		return (Read<uint8_t>(AActors.Enc_1 + Enc.val_1)
			| (Read<uint8_t>(AActors.Enc_1 + Enc.val_2) << 8)
			| (Read<uint8_t>(AActors.Enc_1 + Enc.val_3) << 0x10)
			| (Read<uint8_t>(AActors.Enc_1 + Enc.val_4) << 0x18));
	}
	else if (AActors.Enc_2 > 0) {
		auto Lost_Actors = Read<uint32_t>(AActors.Enc_2);
		if (Lost_Actors > 0) {
			return ((unsigned short)Lost_Actors - 0x400) & 0xFF00
				| (unsigned char)(Lost_Actors - 0x04)
				| (Lost_Actors + 0xFC0000) & 0xFF0000
				| (Lost_Actors - 0x4000000) & 0xFF000000;
		}
	}
	else if (AActors.Enc_3 > 0) {
		auto Lost_Actors = Read<uint32_t>(AActors.Enc_3);
		if (Lost_Actors > 0) {
			return (Lost_Actors >> 0x18) | (Lost_Actors << (32 - 0x18));
		}
	}
	else if (AActors.Enc_4 > 0) {
		auto Lost_Actors = Read<uint32_t>(AActors.Enc_4);
		if (Lost_Actors > 0) {
			return Lost_Actors ^ 0xCDCD00;
		}
	}
	return 0;
}

int isValid(long addr) {
    if ((uintptr_t) addr < 0x1000000000 || (uintptr_t) addr > 0xefffffffff ||
        (uintptr_t) addr % sizeof(uintptr_t) != 0)
        return 0;
    return 1;
}

uintptr_t getMatrix(uintptr_t base) {
    return getA(getA(base + Offsets::Gname) + 0x7c);
}

uintptr_t getEntityAddr(uintptr_t base) {
    uintptr_t level = getA(getA(getA(getA(base + Offsets::Gworld) + 0x38) + 0x58) + Offsets::PersistentLevel); //gworld
    return DecryptActorsArray(level, 0x70, 0x334);
}


PlayerBone getPlayerBone(uintptr_t pBase, struct D3DMatrix viewMatrix) {
    PlayerBone b;
    b.isBone = true;
    struct D3DMatrix oMatrix;
    uintptr_t boneAddr = getA(pBase + Mesh);
    struct D3DMatrix baseMatrix = getOMatrix(boneAddr + FixAttachInfoList);
    boneAddr = getA(boneAddr + MinLOD) + 0x30;
    // neck 0
    oMatrix = getOMatrix(boneAddr + 4 * 48);
    b.neck = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // cheast 1
    oMatrix = getOMatrix(boneAddr + 4 * 48);
    b.cheast = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // pelvis 2
    oMatrix = getOMatrix(boneAddr + 1 * 48);
    b.pelvis = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // lSh 3
    oMatrix = getOMatrix(boneAddr + 11 * 48);
    b.lSh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // rSh 4
    oMatrix = getOMatrix(boneAddr + 32 * 48);
    b.rSh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // lElb 5
    oMatrix = getOMatrix(boneAddr + 12 * 48);
    b.lElb = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // rElb 6
    oMatrix = getOMatrix(boneAddr + 33 * 48);
    b.rElb = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // lWr 7
    oMatrix = getOMatrix(boneAddr + 63 * 48);
    b.lWr = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // rWr 8
    oMatrix = getOMatrix(boneAddr + 62 * 48);
    b.rWr = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // lTh 9
    oMatrix = getOMatrix(boneAddr + 52 * 48);
    b.lTh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // rTh 10
    oMatrix = getOMatrix(boneAddr + 56 * 48);
    b.rTh = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // lKn 11
    oMatrix = getOMatrix(boneAddr + 53 * 48);
    b.lKn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // rKn 12
    oMatrix = getOMatrix(boneAddr + 57 * 48);
    b.rKn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // lAn 13 
    oMatrix = getOMatrix(boneAddr + 54 * 48);
    b.lAn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));
    // rAn 14
    oMatrix = getOMatrix(boneAddr + 58 * 48);
    b.rAn = World2ScreenMain(viewMatrix, mat2Cord(oMatrix, baseMatrix));

    return b;
}

PlayerWeapon getPlayerWeapon(uintptr_t base) {
    PlayerWeapon p;
    uintptr_t addr[3];
    pvm(getA(base + Children), addr, sizeof(addr));

    if (isValid(addr[0]) && Read<int>(addr[0] + DrawShootLineTime) == 2) {
        p.isWeapon = true;
        p.id = Read<int>(getA(addr[0] + ShootWeaponEntityComp) + UploadInterval);
        p.ammo = Read<int>(addr[0] + CurBulletNumInClip);
        p.maxammo = Read<int>(addr[0] + CurMaxBulletNumInOneClip);
    }
	else if (isValid(addr[1]) && Read<int>(addr[1] + DrawShootLineTime) == 2) {
        p.isWeapon = true;
        p.id = Read<int>(getA(addr[1] + ShootWeaponEntityComp) + UploadInterval);
        p.ammo = Read<int>(addr[1] + CurBulletNumInClip);
        p.maxammo = Read<int>(addr[1] + CurMaxBulletNumInOneClip);
    }
	else if (isValid(addr[2]) && Read<int>(addr[2] + DrawShootLineTime) == 2) {
        p.isWeapon = true;
        p.id = Read<int>(getA(addr[2] + ShootWeaponEntityComp) + UploadInterval);
        p.ammo = Read<int>(addr[2] + CurBulletNumInClip);
        p.maxammo = Read<int>(addr[2] + CurMaxBulletNumInOneClip);
    }
    return p;
}

void p_write(uintptr_t address, void* buffer, int size) {
    struct iovec local[1];
    struct iovec remote[1];

    local[0].iov_base = (void*)buffer;
    local[0].iov_len = size;
    remote[0].iov_base = (void*)address;
    remote[0].iov_len = size;

    process_vm_writev(pid, local, 1, remote, 1, 0);
}


template<typename T>
void Write(uintptr_t address, T value) {
    vm_writev(address, reinterpret_cast<void*>(&value),sizeof(T));
}



int main(int argc, char *argv[]) {
    if (!Create()) {
        perror("Creation Failed");
        return 0;
    }
    if (!Connect()) {
        perror("Connection Failed");
        return 0;
    }

    pid = getPid("com.tencent.ig");
    if (pid == 0) {
        pid = getPid("com.pubg.krmobile");
        if (pid == 0) {
            pid = getPid("com.vng.pubgmobile");
            if (pid == 0) {
                pid = getPid("com.rekoo.pubgm");
                if (pid == 0) {
                    pid = getPid("com.pubg.imobile");
                    if (pid == 0) {
                        printf("\nGame is not running");
                        Close();
                        return 0;
                    }
                }
            }
        }
    }

    isPremium = true;
    uintptr_t base = getBase();
    uintptr_t vMatrix = getMatrix(base);

    if (!vMatrix) return 0;

    struct D3DMatrix vMat;
    bool aimKnoced = false;
    bool bullettrack = false;
    int firing = 0, ads = 0;
    int aimBy = 1, aimFor = 1, aimWhen = 3;
    float aimRadius = 200;
    struct Vec2 pointingAngle;
    uintptr_t yawPitch = 0;
    struct Vec3 MyPos, EntityPos,TargetLocation;

    uintptr_t LocalController = 0;
    long int zmAddr = 0;
    uintptr_t LocalPlayer;

    uintptr_t enAddrPntr;
    int changed = 1;
    int myteamID = 101;
    uintptr_t cLoc = vMatrix + 0x6d0;
    uintptr_t fovPntr = vMatrix + 0x5e0;
    vMatrix = vMatrix + 0x510;
    char name[100];
    uintptr_t gname_buff[30];
    uintptr_t gname = getA(getA(base + 0x8a5dfe8) + 0x88);//gname
    pvm(gname, &gname_buff, sizeof(gname_buff));


    //Communication
    Request request{};
    Response response{};

   // Touch_Init();
   // std::thread(TypeA);
   // std::thread(aimThread);



    while (receive((void *) &request) > 0) {
        height = request.ScreenHeight;
        width = request.ScreenWidth;
        if (request.Mode == InitMode) {
            aimRadius = (float) request.options.aimingRange; //range
            aimFor = request.options.aimbotmode;  // head chest stomach
            aimbot = request.options.openState == 0; //aimbot on off
            aimWhen = request.options.aimingState; //firing ads etc
            aimBy = request.options.priority; //distance or crosshair
            aimKnoced = request.options.pour; //ignoreknocked
            bullettrack = request.options.tracingStatus;
          //  radarLocation = request.Radar.x;
          //  radarLocation2 = request.Radar.y;

        }
        response.Success = false;
        response.PlayerCount = 0;
        response.VehicleCount = 0;
        response.ItemsCount = 0;
        response.GrenadeCount = 0;

        pvm(cLoc, &MyPos, sizeof(MyPos));
        if (MyPos.Z == 88.441124f || MyPos.X == 0 || MyPos.Z == 5278.43f || MyPos.Z == 88.440918f) {
            changed = 1;
            send((void *) &response, sizeof(response));
            continue;
        }
        pvm(fovPntr, &response.fov, 4);
        pvm(vMatrix, &vMat, sizeof(vMat));
        if (changed == 1) {
            enAddrPntr = getEntityAddr(base);
            changed = 0;
        }
        Ulevel ulevel;
        pvm(enAddrPntr, &ulevel, sizeof(ulevel));
        if (ulevel.size < 1 || ulevel.size > 0x1000 || !isValid(ulevel.addr)) {
            changed = 1;
            send((void *) &response, sizeof(response));
            continue;
        }


        float nearest = -1.0f;
        for (int i = 0; i < ulevel.size; i++) {
            uintptr_t pBase = getA(ulevel.addr + i * SIZE); //Actor
            if (!isValid(pBase)) {
                continue;
            }

            if (Read<int>(pBase + SIZE) != 8) {
                continue;
            }

            int ids = Read<int>(pBase + 8 + 2 * SIZE);
            int page = ids / 0x4000;
            int index = ids % 0x4000;

            if (page < 1 || page > 30) {
                continue;
            }

            if (gname_buff[page] == 0) {
                gname_buff[page] = getA(gname + page * SIZE);
            }

            strcpy(name, getText(getA(gname_buff[page] + index * SIZE)));
            if (strlen(name) < 5) {
                continue;
            }

            if (strstr(name, "BP_PlayerPawn") || strstr(name, "BP_PlayerCharacter")) {
                int oType = Read<int>(pBase + 0x60);
                if (!isValidPlayer(oType)) {
                    continue;

                }

                if (Read<bool>(pBase + bDead)) {
                    continue;
                }

                PlayerData *data = &response.Players[response.PlayerCount];
                data->TeamID = Read<int>(pBase + TeamID);
                uintptr_t role = Read<int>(pBase + Role);

                if (role == 258) {
                    if (aimbot) {
                        if (aimWhen == 3 || aimWhen == 2) {
                            pvm(pBase + bIsWeaponFiring, &firing, 1);
                        }
                        if (aimWhen == 3 || aimWhen == 1) {
                            pvm(pBase + bIsGunADS, &ads, 1);
                        }

                        LocalPlayer = pBase;
                        yawPitch = getA(LocalPlayer + Controller) + ControlRotation;
                        LocalController = getA(LocalPlayer + Offsets::STPlayerController);
                        zmAddr = getA(LocalController + Offsets::PlayerCameraManager) + Offsets::CameraCache + Offsets::POV;
                    }


                    myteamID = data->TeamID;
                    continue;

                } else if (role != 257) {
                    continue;

                }

                if (data->TeamID == myteamID && myteamID <= 100) {
                    continue;
                }

                uintptr_t boneAddr = getA(pBase + Mesh); //mesh
                EntityPos = mat2Cord(getOMatrix(getA(boneAddr + MinLOD) + 6 * 48),
                                     getOMatrix(boneAddr + FixAttachInfoList));
                pvm(pBase + bIsAI, &data->isBot, sizeof(data->isBot));
                pvm(pBase + Health, healthbuff, sizeof(healthbuff));
                data->Health = healthbuff[0] / healthbuff[1] * 100;
                data->HeadLocation = World2Screen(vMat, EntityPos);
                data->Distance = getDistance(MyPos, EntityPos);

                if (healthbuff[1] > 200.0f || healthbuff[1] < 50.0f ||
                    healthbuff[0] > healthbuff[1] || healthbuff[0] < 0.0f) {
                    continue;
                }

                if (data->Distance > 600.0f) {
                    continue;
                }

                if (data->HeadLocation.Z != 1.0f && data->HeadLocation.X < width + 100 &&
                    data->HeadLocation.X > -50) {
                    data->Bone = getPlayerBone(pBase, vMat);
                    data->Weapon = getPlayerWeapon(pBase);
                    WeaponID = data->Weapon.id;
                    strcpy(data->PlayerNameByte, "66:79:84:");

                    if (!data->isBot) {
                        strcpy(data->PlayerNameByte, getNameByte(getA(pBase + PlayerName)));
                        if (strlen(data->PlayerNameByte) < 4) {
                            continue;
                        }
                    }
                }

                if (data->HeadLocation.Z != 1.0f && (aimKnoced || data->Health > 0) && aimbot &&
                    data->Distance < 150.0f) {
                    float centerDist = sqrt((data->HeadLocation.X - width / 2) *
                                            (data->HeadLocation.X - width / 2) +
                                            (data->HeadLocation.Y - height / 2) *
                                            (data->HeadLocation.Y - height / 2));
                    if (centerDist < aimRadius) {
                        if (aimBy != 1) {
                            centerDist = data->Distance;
                        }
                        if (nearest > centerDist || nearest < 0) {
                            nearest = centerDist;
                            if (aimFor == 1) {
                                //head

                                TargetLocation = EntityPos;
                                ShootWeaponBase shootWeaponBase(LocalPlayer);
                                if (shootWeaponBase.isValid()) {
                                    auto bulletFireSpeed = shootWeaponBase.GetBulletFireSpeed();
                                    auto flyTime = data->Distance / bulletFireSpeed;
                                    if (bulletFireSpeed > 0) {
                                        uintptr_t CurrentVehicle = getA(
                                                pBase + Offsets::CurrentVehicle);
                                        if (CurrentVehicle) {
                                            Vector3 LinearVelocity = Read<Vector3>(
                                                    CurrentVehicle + Offsets::ReplicatedMovement);

                                            TargetLocation.X = TargetLocation.X + LinearVelocity.X * flyTime;
                                            TargetLocation.Y = TargetLocation.Y + LinearVelocity.Y * flyTime;
                                            TargetLocation.Z = TargetLocation.Z + LinearVelocity.Z * flyTime +
                                                          0.5f * 588.6f * flyTime * flyTime;
                                        } else {
                                            uintptr_t STCharacterMovement = getA(
                                                    pBase + Offsets::STCharacterMovement);
                                            if (STCharacterMovement) {
                                                Vector3 Velocity = Read<Vector3>(
                                                        STCharacterMovement + Offsets::Velocity);

                                                TargetLocation.X = TargetLocation.X + Velocity.X * flyTime;
                                                TargetLocation.Y = TargetLocation.Y + Velocity.Y * flyTime;
                                                TargetLocation.Z = TargetLocation.Z + Velocity.Z * flyTime +
                                                              0.5f * 588.6f * flyTime * flyTime;


                                            }

                                        }

                                    }
                                }
                                pointingAngle = getPointingAngle(MyPos, TargetLocation,data->Distance);


                            } else if (aimFor == 2) {
                                //chest
                                uintptr_t boneAddr = getA(pBase + Mesh);
                                struct D3DMatrix baseMatrix = getOMatrix(
                                        boneAddr + FixAttachInfoList); //ComponentToWorld
                                boneAddr = getA(boneAddr + MinLOD);
                                struct D3DMatrix oMatrix = getOMatrix(boneAddr + 4 * 48);
                                TargetLocation = mat2Cord(oMatrix, baseMatrix);
                                auto aimDistance = getDistance(TargetLocation, MyPos);

                                ShootWeaponBase shootWeaponBase(LocalPlayer);
                                if (shootWeaponBase.isValid()) {
                                    auto bulletFireSpeed = shootWeaponBase.GetBulletFireSpeed();
                                    auto flyTime = aimDistance / bulletFireSpeed;
                                    if (bulletFireSpeed > 0) {
                                        uintptr_t CurrentVehicle = getA(
                                                pBase + Offsets::CurrentVehicle);
                                        if (CurrentVehicle) {
                                            Vector3 LinearVelocity = Read<Vector3>(
                                                    CurrentVehicle + Offsets::ReplicatedMovement);

                                            TargetLocation.X =
                                                    TargetLocation.X + LinearVelocity.X * flyTime;
                                            TargetLocation.Y =
                                                    TargetLocation.Y + LinearVelocity.Y * flyTime;
                                            TargetLocation.Z =
                                                    TargetLocation.Z + LinearVelocity.Z * flyTime +
                                                    0.5f * 588.6f * flyTime * flyTime;

                                        } else {
                                            uintptr_t STCharacterMovement = getA(
                                                    pBase + Offsets::STCharacterMovement);
                                            if (STCharacterMovement) {
                                                Vector3 Velocity = Read<Vector3>(
                                                        STCharacterMovement + Offsets::Velocity);

                                                TargetLocation.X =
                                                        TargetLocation.X + Velocity.X * flyTime;
                                                TargetLocation.Y =
                                                        TargetLocation.Y + Velocity.Y * flyTime;
                                                TargetLocation.Z =
                                                        TargetLocation.Z + Velocity.Z * flyTime +
                                                        0.5f * 588.6f * flyTime * flyTime;


                                            }

                                        }

                                    }
                                }

                               pointingAngle = getPointingAngle(MyPos,TargetLocation,aimDistance);

                            } else {
                                //stomach
                                uintptr_t boneAddr = getA(pBase + Mesh);
                                struct D3DMatrix baseMatrix = getOMatrix(
                                        boneAddr + FixAttachInfoList);
                                boneAddr = getA(boneAddr + MinLOD);
                                struct D3DMatrix oMatrix = getOMatrix(boneAddr + 2 * 48);
                                auto TargetLocation = mat2Cord(oMatrix, baseMatrix);
                                float aimDistance = getDistance(TargetLocation, MyPos);

                                ShootWeaponBase shootWeaponBase(LocalPlayer);
                                if (shootWeaponBase.isValid()) {
                                    auto bulletFireSpeed = shootWeaponBase.GetBulletFireSpeed();
                                    auto flyTime = aimDistance / bulletFireSpeed;
                                    if (bulletFireSpeed > 0) {
                                        uintptr_t CurrentVehicle = getA(
                                                pBase + Offsets::CurrentVehicle);
                                        if (CurrentVehicle) {
                                            Vector3 LinearVelocity = Read<Vector3>(
                                                    CurrentVehicle + Offsets::ReplicatedMovement);

                                            TargetLocation.X =
                                                    TargetLocation.X + LinearVelocity.X * flyTime;
                                            TargetLocation.Y =
                                                    TargetLocation.Y + LinearVelocity.Y * flyTime;
                                            TargetLocation.Z =
                                                    TargetLocation.Z + LinearVelocity.Z * flyTime +
                                                    0.5f * 588.6f * flyTime * flyTime;


                                        } else {
                                            uintptr_t STCharacterMovement = getA(
                                                    pBase + Offsets::STCharacterMovement);
                                            if (STCharacterMovement) {
                                                Vector3 Velocity = Read<Vector3>(
                                                        STCharacterMovement + Offsets::Velocity);

                                                TargetLocation.X =
                                                        TargetLocation.X + Velocity.X * flyTime;
                                                TargetLocation.Y =
                                                        TargetLocation.Y + Velocity.Y * flyTime;
                                                TargetLocation.Z =
                                                        TargetLocation.Z + Velocity.Z * flyTime +
                                                        0.5f * 588.6f * flyTime * flyTime;

                                            }

                                        }
                                    }

                                }

                                pointingAngle = getPointingAngle(MyPos, TargetLocation,aimDistance);

                             }
                          }
                       }
                    }
                    if (response.PlayerCount >= maxplayerCount) {
                        continue;
                    }
                    response.PlayerCount++;
                } else if (strstr(name, "VH") || (strstr(name, "PickUp_") && !strstr(name, "BP")) ||
                           strstr(name, "Rony") || strstr(name, "Mirado") ||
                           strstr(name, "LadaNiva") || strstr(name, "AquaRail")) {
                    if (!isPremium) {
                        continue;
                    }

                    VehicleData *data = &response.Vehicles[response.VehicleCount];
                    pvm(getA(pBase + RootComponent) + ParachuteEquipItems, &EntityPos,
                        sizeof(EntityPos));
                    data->Location = World2Screen(vMat, EntityPos);
                    if (data->Location.Z == 1.0f || data->Location.X > width + 200 ||
                        data->Location.X < -200) {
                        continue;
                    }

                    uintptr_t Vehicle = getA(pBase + VehicleCommon);
                    data->Fuel =
                            Read<float>(Vehicle + VFuel) / Read<float>(Vehicle + VFuelMax) * 100;
                    data->Health =
                            Read<float>(Vehicle + VHealth) / Read<float>(Vehicle + VHealthMax) *
                            100;

                    data->Distance = getDistance(MyPos, EntityPos);
                    strcpy(data->VehicleName, name);

                    if (response.VehicleCount >= maxvehicleCount) {
                        continue;
                    }
                    response.VehicleCount++;
                } else if (strstr(name, "Pickup_C") || strstr(name, "PickUp") ||
                           strstr(name, "BP_Ammo") || strstr(name, "BP_QK") ||
                           strstr(name, "Wrapper")) {
                    if (!isPremium) {
                        continue;
                    }

                    ItemData *data = &response.Items[response.ItemsCount];
                    pvm(getA(pBase + RootComponent) + ParachuteEquipItems, &EntityPos,
                        sizeof(EntityPos));
                    data->Location = World2Screen(vMat, EntityPos);
                    if (data->Location.Z == 1.0f || data->Location.X > width + 100 ||
                        data->Location.X < -50) {
                        continue;
                    }
                    data->Distance = getDistance(MyPos, EntityPos);
                    if (data->Distance > 200.0f) {
                        continue;
                    }
                    strcpy(data->ItemName, name);

                    if (response.ItemsCount >= maxitemsCount) {
                        continue;
                    }
                    response.ItemsCount++;
                } else if (strstr(name, "BP_AirDropPlane_") ||
                           strstr(name, "PlayerDeadInventoryBox_") ||
                           strstr(name, "BP_AirDropBox_")) {
                    if (!isPremium) {
                        continue;
                    }

                    ItemData *data = &response.Items[response.ItemsCount];
                    pvm(getA(pBase + RootComponent) + ParachuteEquipItems, &EntityPos,
                        sizeof(EntityPos));
                    data->Location = World2Screen(vMat, EntityPos);
                    if (data->Location.Z == 1.0f || data->Location.X > width + 100 ||
                        data->Location.X < -50) {
                        continue;
                    }
                    data->Distance = getDistance(MyPos, EntityPos);
                    strcpy(data->ItemName, name);

                    if (response.ItemsCount >= maxitemsCount) {
                        continue;
                    }
                    response.ItemsCount++;
                } else if (strstr(name, "BP_Grenade_Shoulei_C") ||
                           strstr(name, "BP_Grenade_Burn_C") || strstr(name, "BP_Grenade_Stun_C")) {
                    if (!isPremium)
                        continue;

                    GrenadeData *data = &response.Grenade[response.GrenadeCount];
                    pvm(getA(pBase + RootComponent) + ParachuteEquipItems, &EntityPos,
                        sizeof(EntityPos));
                    data->Location = World2Screen(vMat, EntityPos);
                    data->Distance = getDistance(MyPos, EntityPos);

                    if (data->Distance > 150.0f) {
                        continue;
                    }

                    if (strstr(name, "Shoulei")) {
                        data->type = 1;
                    } else if (strstr(name, "Burn")) {
                        data->type = 2;
                    } else if (strstr(name, "Stun")) {
                        data->type = 3;
                    }

                    if (response.GrenadeCount >= maxgrenadeCount) {
                        continue;
                    }
                    response.GrenadeCount++;
                }
            }
            if (response.PlayerCount + response.ItemsCount + response.VehicleCount +
                response.GrenadeCount > 0) {
                response.Success = true;
            }
            send((void *) &response, sizeof(response));
            if ((firing || ads) && nearest > 0) {
                if(LocalPlayer != 0){
                    if(bullettrack){
                        p_write(zmAddr + Offsets::Rotation, &pointingAngle, 8);
                    }
                     if(aimbot){
                         p_write(yawPitch, &pointingAngle, 8);
                     }

                }
            }
        }
    }