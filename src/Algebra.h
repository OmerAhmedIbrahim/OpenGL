#ifndef OPENGL_ALGEBRA_H
#define OPENGL_ALGEBRA_H
#define PI_Al 3.1415926f
#include <cmath>

namespace sdds{
    struct vec2{
        float x = 0.0f;
        float y = 0.0f;
        vec2(){}
        explicit vec2(const float &a):x(a),y(a){}
        vec2(const float &i, const float &j):x(i),y(j){}
        float dot(const vec2 &v) const{
            return v.x * x + v.y * y;
        }

    };
    struct vec3{
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        vec3(){}
        explicit vec3(const float &a):x(a),y(a),z(a){}
        vec3(const float &i, const float &j, const float &k):x(i),y(j),z(k){}
        float dot(const vec3 &v) const{
            return v.x * x + v.y * y + v.z * z;
        }
        vec3 cross(const vec3 &v) const{
            return { y * v.z - z * v.y,  -(x * v.z - z * v.x), x * v.y - y * v.x};
        }
        vec3 wedge(const vec3 &v) const{
            return { y * v.z - z * v.y,  x * v.z - z * v.x, x * v.y - y * v.x};
        }
        vec3& scale(const float &a){
            x*=a;
            y*=a;
            z*=a;
            return *this;
        }
        vec3& operator*=(const float &a){
            x*=a;
            y*=a;
            z*=a;
            return *this;
        }
        vec3& operator+=(const vec3 &v){
            x+=v.x;
            y+=v.y;
            z+=v.z;
            return *this;
        }
        vec3& operator-=(const vec3 &v){
            x-=v.x;
            y-=v.y;
            z-=v.z;
            return *this;
        }
    };
    vec3 operator*(const vec3 &v, const float &a){
        //v = {v.x * a, v.y * a ,v.z * a };
            return {v.x * a, v.y * a ,v.z * a };
    }
    vec3 operator*(const float &a, const vec3 &u){
        //u = {a * u.x, a * u.y, a *  u.z};
            return {a * u.x, a * u.y, a *  u.z};
    }
    vec3 operator+(const vec3 &v, const vec3 &u){
            return {v.x + u.x, v.y + u.y,v.z + u.z};
    }
    vec3 operator-(const vec3 &v, const vec3 &u){
            return {v.x - u.x, v.y - u.y,v.z - u.z};
    }
    struct vec4{
        float x = 0.0f;
        float y = 0.0f;
        float z = 0.0f;
        float w = 0.0f;
        explicit vec4(const float &a):x(a),y(a),z(a),w(a){}
        vec4(const float &i, const float &j, const float &k, const float &l):x(i),y(j),z(k),w(l){}
        float dot(const vec4 &v) const{
            return v.x * x + v.y * y + v.z * z + v.w * w;
        }
        void scale(const float &a){
            x*=a;
            y*=a;
            z*=a;
            w*=a;
        }
        vec4& operator+=(const vec4 &v){
            x+=v.x;
            y+=v.y;
            z+=v.z;
            w+=v.w;
            return *this;
        }
    };
    vec4 operator+(const vec4 &v, const vec4 &u){
            return {v.x + u.x, v.y + u.y,v.z + u.z,v.w + u.w};
    }
    vec4 operator-(const vec4 &v, const vec4 &u){
            return {v.x - u.x, v.y - u.y,v.z - u.z,v.w - u.w};
    }
    struct mat4 {
        float columns[16] = {1.0f,0.0f,0.0f,0.0f,
                     0.0f,1.0f,0.0f,0.0f,
                     0.0f,0.0f,1.0f,0.0f,
                     0.0f,0.0f,0.0f,1.0f};
        mat4(){}
        explicit mat4(const float &a)  {
            columns[0] = columns[5] = columns[10] = columns[15] = a;
        }
        void add4(const unsigned int &c, const vec4 &v){
            if(c < 4){
                unsigned int index = c* 4;
                columns[index] = v.x;
                columns[index+1] = v.y;
                columns[index+2] = v.z;
                columns[index+3] = v.w;
            }
        }
    };
    struct rotor3{
        float scalar = 0.0f;
        float xy = 0.0f;
        float yz = 0.0f;
        float zx = 0.0f;
        rotor3(){}
        rotor3(const float &angle, const vec3 &v){
            float theta = (angle * (3.1415926f /180.0f));
            scalar = std::cos(theta/2.0f);
            xy = std::sin(theta/2.0f) * v.z;
            yz = std::sin(theta/2.0f) * v.x;
            zx = std::sin(theta/2.0f) * v.y;
        }
        rotor3(const float &s, const float &e12, const float &e23, const float &e13):
        scalar(s),xy(e12),yz(e23),zx(e13){}
        rotor3(const rotor3 &r) = default;
        rotor3 reverse() const{
            rotor3 result;
            result.scalar = scalar,
            result.xy = -xy;
            result.yz = -yz;
            result.zx = -zx;
            return result;
        }
        vec3 transform(const vec3 &v) const{
            // Assume r is formed by the multiplication of two unit vectors.
            // Then S = Rv, result = SR^{-1} where R^{-1} is just R with the bivector coefficients negated
            const float S_x = scalar * v.x +  xy * v.y -  zx * v.z;
            const float S_y = scalar * v.y -  xy * v.x +  yz * v.z;
            const float S_z = scalar * v.z -  yz * v.y +  zx * v.x;
            const float S_xyz =   xy * v.z +  yz * v.x +  zx * v.y;
            vec3 result;
            result.x = S_x * scalar +   S_y * xy + S_xyz * yz -   S_z * zx;
            result.y = S_y * scalar -   S_x * xy +   S_z * yz + S_xyz * zx;
            result.z = S_z * scalar + S_xyz * xy -   S_y * yz +   S_x * zx;
            return result;
        }
        mat4 rotate() const{
            const vec3 new_x = transform(vec3{1.0f, 0.0f, 0.0f});
            const vec3 new_y = transform(vec3{0.0f, 1.0f, 0.0f});
            const vec3 new_z = transform(vec3{0.0f, 0.0f, 1.0f});

            mat4 result = mat4(1.0f);
            result.add4(0, vec4{new_x.x, new_x.y, new_x.z, 0.0f});
            result.add4(1, vec4{new_y.x, new_y.y, new_y.z, 0.0f});
            result.add4(2,  vec4{new_z.x, new_z.y, new_z.z, 0.0f});
            result.add4(3,  vec4{0.0f, 0.0f, 0.0f, 1.0f});
            return result;
        }
    };
    vec3 normalize(const vec3 &v){
        float norm = 1/std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        return {v.x * norm, v.y * norm, v.z * norm};
    }
    //mat4 inverseView(const mat4){}
    mat4 scale(const float &a){
        mat4 matrix = mat4(a);
        return matrix;
    };
    mat4 scale(const mat4 &m, const float &a){
         mat4 matrix = m;
         matrix.columns[0] *=  a;
         matrix.columns[5] *=  a;
         matrix.columns[10] *=  a;
        return matrix;
    };
    mat4 translate(const vec3 &v){
        mat4 matrix = mat4(1.0f);
        matrix.add4(3, {v.x,v.y,v.z,1.0f });
        return matrix;
    };
    mat4 translate(const vec2 &v){
        mat4 matrix = mat4(1.0f);
        matrix.add4(3, {v.x,v.y,0.0f,1.0f });
        return matrix;
    };
    mat4 translate(const mat4 &m, const vec3 &v){
        mat4 matrix = m;
        matrix.add4(3, {v.x,v.y,v.z,1.0 });
        return matrix;
    };
    mat4 translate(const mat4 &m, const vec2 &v){
        mat4 matrix = m;
        matrix.add4(3, {v.x,v.y,0.0f,1.0f });
        return matrix;
    };
    mat4 createLookAt(const vec3 &from, const vec3 &to){
        vec3 g_up = {0.0f, 0.0f,1.0f};
        vec3 cam_f = normalize((to - from));
        vec3 cam_r = normalize(cam_f.cross(g_up));
        vec3 cam_u = normalize(cam_r.cross(cam_f));

        mat4 matrix;
        matrix.add4(0, {cam_r.x, cam_u.x, -cam_f.x, 0.0f});
        matrix.add4(1, {cam_r.y, cam_u.y, -cam_f.y, 0.0f});
        matrix.add4(2, {cam_r.z, cam_u.z, -cam_f.z, 0.0f});
        matrix.add4(3, {-(cam_r.dot(from)), -(cam_u.dot(from)), cam_f.dot(from), 1.0f});
        return matrix;
    }
    mat4 createPerspectiveProjection (const float &aspect, const float &fovy, const float &near, const float &far){
        float newfovy = fovy * 3.1415926f / 360.0f;
        float t = tanf(newfovy);
        float n = (-1.0f*near);
        float f = (-1.0f*far);
        auto matrix = mat4(0.0f);
        matrix.columns[0] =  1.0f / (aspect * t);
        matrix.columns[5] =  1.0f / t;
        matrix.columns[10] =  -(n + f)/(n - f);
        matrix.columns[11] =  -1.0f;
        matrix.columns[14] =  (2.0f * n * f)/(n - f);
        return matrix;
    }
};

#endif //OPENGL_ALGEBRA_H
