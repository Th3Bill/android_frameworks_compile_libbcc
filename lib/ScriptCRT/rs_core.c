#include "rs_types.rsh"
#include "rs_cl.rsh"

/* Declaration of 4 basic functions in libRS */
extern void __attribute__((overloadable))
    rsDebug(const char *, float, float);
extern void __attribute__((overloadable))
    rsDebug(const char *, float, float, float);
extern void __attribute__((overloadable))
    rsDebug(const char *, float, float, float, float);
extern float4 __attribute__((overloadable)) convert_float4(uchar4 c);

/* Implementation of Core Runtime */

extern void __attribute__((overloadable)) rsDebug(const char *s, float2 v) {
    rsDebug(s, v.x, v.y);
}

extern void __attribute__((overloadable)) rsDebug(const char *s, float3 v) {
    rsDebug(s, v.x, v.y, v.z);
}

extern void __attribute__((overloadable)) rsDebug(const char *s, float4 v) {
    rsDebug(s, v.x, v.y, v.z, v.w);
}

extern uchar4 __attribute__((overloadable)) rsPackColorTo8888(float r, float g, float b)
{
    uchar4 c;
    c.x = (uchar)(r * 255.f);
    c.y = (uchar)(g * 255.f);
    c.z = (uchar)(b * 255.f);
    c.w = 255;
    return c;
}

extern uchar4 __attribute__((overloadable)) rsPackColorTo8888(float r, float g, float b, float a)
{
    uchar4 c;
    c.x = (uchar)(r * 255.f);
    c.y = (uchar)(g * 255.f);
    c.z = (uchar)(b * 255.f);
    c.w = (uchar)(a * 255.f);
    return c;
}

extern uchar4 __attribute__((overloadable)) rsPackColorTo8888(float3 color)
{
    color *= 255.f;
    uchar4 c = {color.x, color.y, color.z, 255};
    return c;
}

extern uchar4 __attribute__((overloadable)) rsPackColorTo8888(float4 color)
{
    color *= 255.f;
    uchar4 c = {color.x, color.y, color.z, color.w};
    return c;
}

extern float4 rsUnpackColor8888(uchar4 c)
{
    float4 ret = (float4)0.0039156862745f;
    ret *= convert_float4(c);
    return ret;
}

/////////////////////////////////////////////////////
// Matrix ops
/////////////////////////////////////////////////////

extern void __attribute__((overloadable))
rsMatrixSet(rs_matrix4x4 *m, uint32_t row, uint32_t col, float v) {
    m->m[row * 4 + col] = v;
}

extern float __attribute__((overloadable))
rsMatrixGet(const rs_matrix4x4 *m, uint32_t row, uint32_t col) {
    return m->m[row * 4 + col];
}

extern void __attribute__((overloadable))
rsMatrixSet(rs_matrix3x3 *m, uint32_t row, uint32_t col, float v) {
    m->m[row * 3 + col] = v;
}

extern float __attribute__((overloadable))
rsMatrixGet(const rs_matrix3x3 *m, uint32_t row, uint32_t col) {
    return m->m[row * 3 + col];
}

extern void __attribute__((overloadable))
rsMatrixSet(rs_matrix2x2 *m, uint32_t row, uint32_t col, float v) {
    m->m[row * 2 + col] = v;
}

extern float __attribute__((overloadable))
rsMatrixGet(const rs_matrix2x2 *m, uint32_t row, uint32_t col) {
    return m->m[row * 2 + col];
}


extern float4 __attribute__((overloadable))
rsMatrixMultiply(rs_matrix4x4 *m, float4 in) {
    float4 ret;
    ret.x = (m->m[0] * in.x) + (m->m[4] * in.y) + (m->m[8] * in.z) + (m->m[12] * in.w);
    ret.y = (m->m[1] * in.x) + (m->m[5] * in.y) + (m->m[9] * in.z) + (m->m[13] * in.w);
    ret.z = (m->m[2] * in.x) + (m->m[6] * in.y) + (m->m[10] * in.z) + (m->m[14] * in.w);
    ret.w = (m->m[3] * in.x) + (m->m[7] * in.y) + (m->m[11] * in.z) + (m->m[15] * in.w);
    return ret;
}

extern float4 __attribute__((overloadable))
rsMatrixMultiply(rs_matrix4x4 *m, float3 in) {
    float4 ret;
    ret.x = (m->m[0] * in.x) + (m->m[4] * in.y) + (m->m[8] * in.z) + m->m[12];
    ret.y = (m->m[1] * in.x) + (m->m[5] * in.y) + (m->m[9] * in.z) + m->m[13];
    ret.z = (m->m[2] * in.x) + (m->m[6] * in.y) + (m->m[10] * in.z) + m->m[14];
    ret.w = (m->m[3] * in.x) + (m->m[7] * in.y) + (m->m[11] * in.z) + m->m[15];
    return ret;
}

extern float4 __attribute__((overloadable))
rsMatrixMultiply(rs_matrix4x4 *m, float2 in) {
    float4 ret;
    ret.x = (m->m[0] * in.x) + (m->m[4] * in.y) + m->m[12];
    ret.y = (m->m[1] * in.x) + (m->m[5] * in.y) + m->m[13];
    ret.z = (m->m[2] * in.x) + (m->m[6] * in.y) + m->m[14];
    ret.w = (m->m[3] * in.x) + (m->m[7] * in.y) + m->m[15];
    return ret;
}

extern float3 __attribute__((overloadable))
rsMatrixMultiply(rs_matrix3x3 *m, float3 in) {
    float3 ret;
    ret.x = (m->m[0] * in.x) + (m->m[3] * in.y) + (m->m[6] * in.z);
    ret.y = (m->m[1] * in.x) + (m->m[4] * in.y) + (m->m[7] * in.z);
    ret.z = (m->m[2] * in.x) + (m->m[5] * in.y) + (m->m[8] * in.z);
    return ret;
}

extern float3 __attribute__((overloadable))
rsMatrixMultiply(rs_matrix3x3 *m, float2 in) {
    float3 ret;
    ret.x = (m->m[0] * in.x) + (m->m[3] * in.y);
    ret.y = (m->m[1] * in.x) + (m->m[4] * in.y);
    ret.z = (m->m[2] * in.x) + (m->m[5] * in.y);
    return ret;
}

extern float2 __attribute__((overloadable))
rsMatrixMultiply(rs_matrix2x2 *m, float2 in) {
    float2 ret;
    ret.x = (m->m[0] * in.x) + (m->m[2] * in.y);
    ret.y = (m->m[1] * in.x) + (m->m[3] * in.y);
    return ret;
}

/////////////////////////////////////////////////////
// int ops
/////////////////////////////////////////////////////

extern uint __attribute__((overloadable, always_inline)) rsClamp(uint amount, uint low, uint high) {
    return amount < low ? low : (amount > high ? high : amount);
}
extern int __attribute__((overloadable, always_inline)) rsClamp(int amount, int low, int high) {
    return amount < low ? low : (amount > high ? high : amount);
}
extern ushort __attribute__((overloadable, always_inline)) rsClamp(ushort amount, ushort low, ushort high) {
    return amount < low ? low : (amount > high ? high : amount);
}
extern short __attribute__((overloadable, always_inline)) rsClamp(short amount, short low, short high) {
    return amount < low ? low : (amount > high ? high : amount);
}
extern uchar __attribute__((overloadable, always_inline)) rsClamp(uchar amount, uchar low, uchar high) {
    return amount < low ? low : (amount > high ? high : amount);
}
extern char __attribute__((overloadable, always_inline)) rsClamp(char amount, char low, char high) {
    return amount < low ? low : (amount > high ? high : amount);
}