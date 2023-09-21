#ifndef SHOOLIN_OFFSETS_H
#define SHOOLIN_OFFSETS_H
//----------Credit -> @pakgamerz
namespace Offsets {


    uintptr_t Gworld = 0x8d730b0;
    uintptr_t Gname = 0x8d730b0 ;

    //class : world
    uintptr_t PersistentLevel = 0x20;
    uintptr_t NetDriver = 0x24;

    //Class: NetDriver
    uintptr_t ServerConnection = 0x60;

    //Class; STExtraPlayerCharacter
    constexpr auto STPlayerController = 0x2ea4;

    //class : PlayerController
    uintptr_t PlayerCameraManager = 0x370;

    //Class: UAEPlayerController
    constexpr auto PlayerKey = 0x65c;

    //class : PlayerCameraManager
    uintptr_t CameraCache = 0x370;

    //class : CameraCacheEntry
    uintptr_t  POV = 0x10;



    //Class: MinimalViewInfo
    uintptr_t Rotation = 0x18;
    uintptr_t  FOV = 0x24;


    //Class: Actor
    uintptr_t Role = 0x100; //byte Role;
    uintptr_t Children = 0x144; //Actor*[] Children;
    uintptr_t RootComponent = 0x150; //SceneComponent* RootComponent;
    uintptr_t DrawShootLineTime = 0xf4; //RepAttachment AttachmentReplication + FName AttachSocket + 0x4;
    uintptr_t ReplicatedMovement = 0x78;



    //Class: SceneComponent
    uintptr_t FixAttachInfoList = 0x140; //FTransform ComponentToWorld;
    uintptr_t ParachuteEquipItems = 0x150; //FTransform ComponentToWorld + 0x10;

    //Class: Pawn
    uintptr_t Controller = 0x328; //Controller* Controller;

    //Class: Controller
    uintptr_t ControlRotation = 0x324; //Rotator ControlRotation;

    //Class: Character
    uintptr_t Mesh = 0x34c; //SkeletalMeshComponent* Mesh;

    //Class: SkinnedMeshComponent
    uintptr_t MinLOD = 0x63c; //FTransform[] ComponentSpaceTransforms;
    
    //Class: CameraComponent
    uintptr_t FieldOfView = 0x260; //float FieldOfView;

    //Class: UAECharacter
    uintptr_t PlayerName = 0x680; //FString PlayerName;
    uintptr_t Nation = 0x68c; //FString Nation;
    uintptr_t PlayerUID = 0x69c; //FString PlayerUID;
    uintptr_t TeamID = 0x6b4; //int TeamID;
    uintptr_t bIsAI = 0x734; //bool bIsAI;

    //Class: STExtraCharacter
    uintptr_t Health = 0x9dc; //float Health;
    uintptr_t bDead = 0x9f4; //bool bDead;
    uintptr_t bIsGunADS = 0xbb1; //bool bIsGunADS;
    uintptr_t CurrentVehicle = 0xa14;//STExtraVehicleBase* CurrentVehicle;

    //Class: STExtraBaseCharacter
    uintptr_t bIsWeaponFiring = 0xffc; //bool bIsWeaponFiring;
    uintptr_t ThirdPersonCameraComponent = 0x13a4; //CameraComponent* ThirdPersonCameraComponent;//0x13a4
    uintptr_t WeaponManagerComponent = 0x19f0; //CharacterWeaponManagerComponent* WeaponManagerComponent; //0x19f0
    uintptr_t SwitchWeaponSpeedScale = 0x1e34; //float SwitchWeaponSpeedScale;//0x1e34
    uintptr_t STCharacterMovement = 0x1478;

    //Class: STExtraShootWeapon
    uintptr_t CurBulletNumInClip = 0xb58; //int CurBulletNumInClip;
    uintptr_t CurMaxBulletNumInOneClip = 0xb6c; //int CurMaxBulletNumInOneClip;
    uintptr_t ShootWeaponEntityComp = 0xc78; //ShootWeaponEntity* ShootWeaponEntityComp; //0xc78

    //Class: WeaponManagerComponent
    uintptr_t CurrWeapon = 0x3fc; //STExtraWeapon* CurrentWeaponReplicated;

    //Class: WeaponEntity
    uintptr_t UploadInterval = 0x100; //int WeaponID;

    //Class: ShootWeaponEntity
    uintptr_t BulletFireSpeed = 0x548; //float BulletRange;
    uintptr_t ShootInterval = 0x434; //float ShootInterval;
    uintptr_t AutoAimingConfig = 0x758; //AutoAimingConfig AutoAimingConfig;
    uintptr_t AccessoriesVRecoilFactor = 0x8c8; //float AccessoriesVRecoilFactor;
    uintptr_t AccessoriesHRecoilFactor = 0x8cc; //float AccessoriesHRecoilFactor;
    uintptr_t AccessoriesRecoveryFactor = 0x8d0; //float AccessoriesRecoveryFactor;
    uintptr_t GameDeviationFactor = 0x930; //float GameDeviationFactor;
    uintptr_t RecoilKickADS = 0x9e0; //float RecoilKickADS;
    uintptr_t ExtraHitPerformScale = 0x9e4; //float ExtraHitPerformScale;
    uintptr_t AnimationKick = 0x9fc; //float AnimationKick;

    //Class: STExtraVehicleBase
    uintptr_t VehicleCommon = 0x77c; //VehicleCommonComponent* VehicleCommon;//0x77c

    //Class: VehicleCommonComponent
    uintptr_t VHealthMax = 0x1e0; //float HPMax;
    uintptr_t VHealth = 0x1e4; //float HP;
    uintptr_t VFuelMax = 0x200; //float FuelMax;
    uintptr_t VFuel = 0x204; //float Fuel;

   // Class: MovementComponent
    uintptr_t Velocity = 0xc8;


}
//----------Credit -> @pakgamerz
#endif
