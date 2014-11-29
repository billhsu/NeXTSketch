// http://www.codng.com/2011/02/gluunproject-for-iphoneios.html

#include "Project.h"
#include <math.h>

namespace cashew
{
    const int32_t GL_TRUE = 1;
    const int32_t GL_FALSE = 0;
    /*
     ** Make m an identity matrix
     */
    static void __gluMakeIdentityf(float m[16])
    {
        m[0 + 4 * 0] = 1; m[0 + 4 * 1] = 0; m[0 + 4 * 2] = 0; m[0 + 4 * 3] = 0;
        m[1 + 4 * 0] = 0; m[1 + 4 * 1] = 1; m[1 + 4 * 2] = 0; m[1 + 4 * 3] = 0;
        m[2 + 4 * 0] = 0; m[2 + 4 * 1] = 0; m[2 + 4 * 2] = 1; m[2 + 4 * 3] = 0;
        m[3 + 4 * 0] = 0; m[3 + 4 * 1] = 0; m[3 + 4 * 2] = 0; m[3 + 4 * 3] = 1;
    }
    
#define __glPi 3.14159265358979323846
    
    Matrix4
    gluPerspective(float fovy, float aspect, float zNear, float zFar)
    {
        Matrix4 result;
        float m[4][4];
        float sine, cotangent, deltaZ;
        float radians = fovy / 2 * __glPi / 180;
        
        deltaZ = zFar - zNear;
        sine = sin(radians);
        if ((deltaZ == 0) || (sine == 0) || (aspect == 0))
        {
            return result;
        }
        cotangent = cos(radians) / sine;
        
        __gluMakeIdentityf(&m[0][0]);
        m[0][0] = cotangent / aspect;
        m[1][1] = cotangent;
        m[2][2] = -(zFar + zNear) / deltaZ;
        m[2][3] = -1;
        m[3][2] = -2 * zNear * zFar / deltaZ;
        m[3][3] = 0;
        result.set((float*)m);
        return result;
    }
    
    static void normalize(float v[3])
    {
        float r;
        
        r = sqrt( v[0] * v[0] + v[1] * v[1] + v[2] * v[2] );
        if (r == 0.0) return;
        
        v[0] /= r;
        v[1] /= r;
        v[2] /= r;
    }
    
    static void cross(float v1[3], float v2[3], float result[3])
    {
        result[0] = v1[1] * v2[2] - v1[2] * v2[1];
        result[1] = v1[2] * v2[0] - v1[0] * v2[2];
        result[2] = v1[0] * v2[1] - v1[1] * v2[0];
    }
    
    Matrix4
    gluLookAt(float eyex, float eyey, float eyez, float centerx,
              float centery, float centerz, float upx, float upy,
              float upz)
    {
        Matrix4 result;
        float forward[3], side[3], up[3];
        float m[4][4];
        
        forward[0] = centerx - eyex;
        forward[1] = centery - eyey;
        forward[2] = centerz - eyez;
        
        up[0] = upx;
        up[1] = upy;
        up[2] = upz;
        
        normalize(forward);
        
        /* Side = forward x up */
        cross(forward, up, side);
        normalize(side);
        
        /* Recompute up as: up = side x forward */
        cross(side, forward, up);
        
        __gluMakeIdentityf(&m[0][0]);
        m[0][0] = side[0];
        m[1][0] = side[1];
        m[2][0] = side[2];
        
        m[0][1] = up[0];
        m[1][1] = up[1];
        m[2][1] = up[2];
        
        m[0][2] = -forward[0];
        m[1][2] = -forward[1];
        m[2][2] = -forward[2];
        Matrix4 translate;
        translate.translate(-eyex, -eyey, -eyez);
        result.set((float*)m);
        result = result * translate;
        return result;
    }
    
    static void __gluMultMatrixVecf(const float matrix[16], const float in[4],
                                    float out[4])
    {
        int i;
        
        for (i = 0; i < 4; i++)
        {
            out[i] =
            in[0] * matrix[0 * 4 + i] +
            in[1] * matrix[1 * 4 + i] +
            in[2] * matrix[2 * 4 + i] +
            in[3] * matrix[3 * 4 + i];
        }
    }
    
    /*
     ** Invert 4x4 matrix.
     ** Contributed by David Moore (See Mesa bug #6748)
     */
    static int __gluInvertMatrixf(const float m[16], float invOut[16])
    {
        float inv[16], det;
        int i;
        
        inv[0] =   m[5] * m[10] * m[15] - m[5] * m[11] * m[14] - m[9] * m[6] * m[15]
        + m[9] * m[7] * m[14] + m[13] * m[6] * m[11] - m[13] * m[7] * m[10];
        inv[4] =  -m[4] * m[10] * m[15] + m[4] * m[11] * m[14] + m[8] * m[6] * m[15]
        - m[8] * m[7] * m[14] - m[12] * m[6] * m[11] + m[12] * m[7] * m[10];
        inv[8] =   m[4] * m[9] * m[15] - m[4] * m[11] * m[13] - m[8] * m[5] * m[15]
        + m[8] * m[7] * m[13] + m[12] * m[5] * m[11] - m[12] * m[7] * m[9];
        inv[12] = -m[4] * m[9] * m[14] + m[4] * m[10] * m[13] + m[8] * m[5] * m[14]
        - m[8] * m[6] * m[13] - m[12] * m[5] * m[10] + m[12] * m[6] * m[9];
        inv[1] =  -m[1] * m[10] * m[15] + m[1] * m[11] * m[14] + m[9] * m[2] * m[15]
        - m[9] * m[3] * m[14] - m[13] * m[2] * m[11] + m[13] * m[3] * m[10];
        inv[5] =   m[0] * m[10] * m[15] - m[0] * m[11] * m[14] - m[8] * m[2] * m[15]
        + m[8] * m[3] * m[14] + m[12] * m[2] * m[11] - m[12] * m[3] * m[10];
        inv[9] =  -m[0] * m[9] * m[15] + m[0] * m[11] * m[13] + m[8] * m[1] * m[15]
        - m[8] * m[3] * m[13] - m[12] * m[1] * m[11] + m[12] * m[3] * m[9];
        inv[13] =  m[0] * m[9] * m[14] - m[0] * m[10] * m[13] - m[8] * m[1] * m[14]
        + m[8] * m[2] * m[13] + m[12] * m[1] * m[10] - m[12] * m[2] * m[9];
        inv[2] =   m[1] * m[6] * m[15] - m[1] * m[7] * m[14] - m[5] * m[2] * m[15]
        + m[5] * m[3] * m[14] + m[13] * m[2] * m[7] - m[13] * m[3] * m[6];
        inv[6] =  -m[0] * m[6] * m[15] + m[0] * m[7] * m[14] + m[4] * m[2] * m[15]
        - m[4] * m[3] * m[14] - m[12] * m[2] * m[7] + m[12] * m[3] * m[6];
        inv[10] =  m[0] * m[5] * m[15] - m[0] * m[7] * m[13] - m[4] * m[1] * m[15]
        + m[4] * m[3] * m[13] + m[12] * m[1] * m[7] - m[12] * m[3] * m[5];
        inv[14] = -m[0] * m[5] * m[14] + m[0] * m[6] * m[13] + m[4] * m[1] * m[14]
        - m[4] * m[2] * m[13] - m[12] * m[1] * m[6] + m[12] * m[2] * m[5];
        inv[3] =  -m[1] * m[6] * m[11] + m[1] * m[7] * m[10] + m[5] * m[2] * m[11]
        - m[5] * m[3] * m[10] - m[9] * m[2] * m[7] + m[9] * m[3] * m[6];
        inv[7] =   m[0] * m[6] * m[11] - m[0] * m[7] * m[10] - m[4] * m[2] * m[11]
        + m[4] * m[3] * m[10] + m[8] * m[2] * m[7] - m[8] * m[3] * m[6];
        inv[11] = -m[0] * m[5] * m[11] + m[0] * m[7] * m[9] + m[4] * m[1] * m[11]
        - m[4] * m[3] * m[9] - m[8] * m[1] * m[7] + m[8] * m[3] * m[5];
        inv[15] =  m[0] * m[5] * m[10] - m[0] * m[6] * m[9] - m[4] * m[1] * m[10]
        + m[4] * m[2] * m[9] + m[8] * m[1] * m[6] - m[8] * m[2] * m[5];
        
        det = m[0] * inv[0] + m[1] * inv[4] + m[2] * inv[8] + m[3] * inv[12];
        if (det == 0)
            return GL_FALSE;
        
        det = 1.0 / det;
        
        for (i = 0; i < 16; i++)
            invOut[i] = inv[i] * det;
        
        return GL_TRUE;
    }
    
    static void __gluMultMatricesf(const float a[16], const float b[16],
                                   float r[16])
    {
        int i, j;
        
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                r[i * 4 + j] =
                a[i * 4 + 0] * b[0 * 4 + j] +
                a[i * 4 + 1] * b[1 * 4 + j] +
                a[i * 4 + 2] * b[2 * 4 + j] +
                a[i * 4 + 3] * b[3 * 4 + j];
            }
        }
    }
    
    int32_t
    gluProject(float objx, float objy, float objz,
               const float modelMatrix[16],
               const float projMatrix[16],
               const int32_t viewport[4],
               float *winx, float *winy, float *winz)
    {
        float in[4];
        float out[4];
        
        in[0] = objx;
        in[1] = objy;
        in[2] = objz;
        in[3] = 1.0;
        __gluMultMatrixVecf(modelMatrix, in, out);
        __gluMultMatrixVecf(projMatrix, out, in);
        if (in[3] == 0.0) return (GL_FALSE);
        in[0] /= in[3];
        in[1] /= in[3];
        in[2] /= in[3];
        /* Map x, y and z to range 0-1 */
        in[0] = in[0] * 0.5 + 0.5;
        in[1] = in[1] * 0.5 + 0.5;
        in[2] = in[2] * 0.5 + 0.5;
        
        /* Map x,y to viewport */
        in[0] = in[0] * viewport[2] + viewport[0];
        in[1] = in[1] * viewport[3] + viewport[1];
        
        *winx = in[0];
        *winy = in[1];
        *winz = in[2];
        return (GL_TRUE);
    }
    
    int32_t
    gluUnProject(float winx, float winy, float winz,
                 const float modelMatrix[16],
                 const float projMatrix[16],
                 const int32_t viewport[4],
                 double *objx, double *objy, double *objz)
    {
        float finalMatrix[16];
        float in[4];
        float out[4];
        
        __gluMultMatricesf(modelMatrix, projMatrix, finalMatrix);
        if (!__gluInvertMatrixf(finalMatrix, finalMatrix)) return (GL_FALSE);
        
        in[0] = winx;
        in[1] = winy;
        in[2] = winz;
        in[3] = 1.0;
        
        /* Map x and y from window coordinates */
        in[0] = (in[0] - viewport[0]) / viewport[2];
        in[1] = (in[1] - viewport[1]) / viewport[3];
        
        /* Map to range -1 to 1 */
        in[0] = in[0] * 2 - 1;
        in[1] = in[1] * 2 - 1;
        in[2] = in[2] * 2 - 1;
        
        __gluMultMatrixVecf(finalMatrix, in, out);
        if (out[3] == 0.0) return (GL_FALSE);
        out[0] /= out[3];
        out[1] /= out[3];
        out[2] /= out[3];
        *objx = out[0];
        *objy = out[1];
        *objz = out[2];
        return (GL_TRUE);
    }
    
    int32_t
    gluUnProject4(float winx, float winy, float winz, float clipw,
                  const float modelMatrix[16],
                  const float projMatrix[16],
                  const int32_t viewport[4],
                  float nearVal, float farVal,
                  float *objx, float *objy, float *objz,
                  float *objw)
    {
        float finalMatrix[16];
        float in[4];
        float out[4];
        
        __gluMultMatricesf(modelMatrix, projMatrix, finalMatrix);
        if (!__gluInvertMatrixf(finalMatrix, finalMatrix)) return (GL_FALSE);
        
        in[0] = winx;
        in[1] = winy;
        in[2] = winz;
        in[3] = clipw;
        
        /* Map x and y from window coordinates */
        in[0] = (in[0] - viewport[0]) / viewport[2];
        in[1] = (in[1] - viewport[1]) / viewport[3];
        in[2] = (in[2] - nearVal) / (farVal - nearVal);
        
        /* Map to range -1 to 1 */
        in[0] = in[0] * 2 - 1;
        in[1] = in[1] * 2 - 1;
        in[2] = in[2] * 2 - 1;
        
        __gluMultMatrixVecf(finalMatrix, in, out);
        if (out[3] == 0.0) return (GL_FALSE);
        *objx = out[0];
        *objy = out[1];
        *objz = out[2];
        *objw = out[3];
        return (GL_TRUE);
    }
    
    
};