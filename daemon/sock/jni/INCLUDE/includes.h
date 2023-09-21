#ifndef SHOOLIN_INCLUDES_H
#define SHOOLIN_INCLUDES_H
//----------Credit -> @Shoolin_Official
#include <sys/uio.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/syscall.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdio.h>
#include <sys/un.h>
#include <time.h>
#include <ctype.h>
#include <iostream>

#include "Offsets.h"

//----------Credit -> @Shoolin_Official
#if defined(__arm__)
int process_vm_readv_syscall = 376;
int process_vm_writev_syscall = 377;
#elif defined(__aarch64__)
int process_vm_readv_syscall = 270;
int process_vm_writev_syscall = 271;
#elif defined(__i386__)
int process_vm_readv_syscall = 347;
int process_vm_writev_syscall = 348;
#else
int process_vm_readv_syscall = 310;
int process_vm_writev_syscall = 311;
#endif

#define LEN sizeof(struct MAPS)
//----------Credit -> @Shoolin_Official
struct Vec4 {
    float  X, Y, Z, W;
};

struct Vec3 {
    float X, Y, Z;
};

struct Vec2 {
    float X, Y;
};

class FVector
{
public:

    FVector(float X, float Y) {
        Init(X, Y);
    }

    void Init(float ix = 0.0f, float iy = 0.0f) {
        x = ix;
        y = iy;
    }

    FVector() : x(0.f), y(0.f), z(0.f)
    {

    }

    FVector(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {

    }
    ~FVector()
    {

    }

    float x;
    float y;
    float z;

    inline float Dot(FVector v)
    {
        return x * v.x + y * v.y + z * v.z;
    }

    inline float Distance2D(float x1, float y1)
    {
        return (float)(sqrt(pow(double(x - x1), 2.0) + pow(double(y - y1), 2.0)));
    }

    inline float Distance(FVector v)
    {
        return float(sqrtf(powf(v.x - x, 2.0) + powf(v.y - y, 2.0) + powf(v.z - z, 2.0)));
    }
    inline float Length()
    {
        return sqrtf(x * x + y * y + z * z);
    }
    inline FVector& operator+=(const FVector& v) {
        x += v.x; y += v.y; z += v.z; return *this;
    }

    inline FVector& operator-=(const FVector& v) {
        x -= v.x; y -= v.y; z -= v.z; return *this;
    }

    inline FVector& operator*=(const FVector& v) {
        x *= v.x; y *= v.y; z *= v.z; return *this;
    }

    inline FVector& operator/=(const FVector& v) {
        x /= v.x; y /= v.y; z /= v.z; return *this;
    }

    inline FVector& operator+=(float v) {
        x += v; y += v; z += v; return *this;
    }

    inline FVector& operator-=(float v) {
        x -= v; y -= v; z -= v; return *this;
    }

    inline FVector& operator*=(float v) {
        x *= v; y *= v; z *= v; return *this;
    }

    inline FVector& operator/=(float v) {
        x /= v; y /= v; z /= v; return *this;
    }

    inline FVector operator-() const {
        return FVector(-x, -y, -z);
    }

    inline FVector operator+(const FVector& v) const {
        return FVector(x + v.x, y + v.y, z + v.z);
    }

    inline FVector operator-(const FVector& v) const {
        return FVector(x - v.x, y - v.y, z - v.z);
    }

    inline FVector operator*(const FVector& v) const {
        return FVector(x * v.x, y * v.y, z * v.z);
    }

    inline FVector operator/(const FVector& v) const {
        return FVector(x / v.x, y / v.y, z / v.z);
    }

    inline FVector operator+(float v) const {
        return FVector(x + v, y + v, z + v);
    }

    inline FVector operator-(float v) const {
        return FVector(x - v, y - v, z - v);
    }

    inline FVector operator*(float v) const {
        return FVector(x * v, y * v, z * v);
    }

    inline FVector operator/(float v) const {
        return FVector(x / v, y / v, z / v);
    }
};

struct D3DMatrix
{
    float _11, _12, _13, _14;

    float _21, _22, _23, _24;

    float _31, _32, _33, _34;

    float _41, _42, _43, _44;
};

struct D2DVector
{
    float X;
    float Y;
};

struct Vec4 rot;
struct Vec3 scale, tran;

int height = 0, width = 0, pid = 0;
float mx = 0, my = 0, mz = 0;

struct MAPS
{
    long int fAddr;
    long int lAddr;
    struct MAPS* next;
};

struct Ulevel {
    uintptr_t addr;
    int size;
};

typedef struct MAPS* PMAPS;
//----------Credit -> @Shoolin_Official
#define SIZE sizeof(uintptr_t)

#endif