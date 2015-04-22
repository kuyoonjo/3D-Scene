//
//  Vector.h
//  yctools
//
//  Created by Yu Chen on 4/7/15.
//
//

#ifndef yctools_Vector_h
#define yctools_Vector_h

#include <cmath>

namespace yc
{
    template <class T> class Vector
    {
    public:
        T x;
        T y;
        T z;
        
        explicit Vector(T x=0, T y=0, T z=0): x(x), y(y), z(z) {}
        
        void operator+=(const Vector<T>& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }
        void operator-=(const Vector<T>& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }
        void operator*=(const T& n)
        {
            x *= n;
            y *= n;
            z *= n;
        }
        void operator/=(const T& n)
        {
            x /= n;
            y /= n;
            z /= n;
        }
        
        
        // + - * /
        Vector<T> operator+(const Vector<T>& v) const
        {
            return Vector<T>(x + v.x, y + v.y, z + v.z);
        }
        Vector<T> operator-(const Vector<T>& v) const
        {
            return Vector<T>(x - v.x, y - v.y, z - v.z);
        }
        Vector<T> operator/(const T& n) const
        {
            return Vector<T>(x / n, y / n, z /n);
        }
        Vector<T> operator*(const T& n) const
        {
            return Vector<T>(x * n, y * n, z * n);
        }
        
        // dot, cross product
        T dotMultiply(const Vector<T>& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }
        Vector<T> crossMultiply(const Vector<T>& v) const
        {
            return Vector<T>(y * v.z - v.y * z, z * v.x - x * v.z, x * v.y - y * v.x);
        }
        
        // others
        double getPowerLength() const
        {
            return dotMultiply(*this);
        }
        double getLength() const
        {
            return std::sqrt(getPowerLength());
        }
        Vector<T> getUnitVector() const
        {
            return *this / getLength();
        }
        
        double getAngleBetween(const Vector<T>& v) const
        {
            return std::acos(dotMultiply(v) / std::sqrt(getPowerLength() * v.getPowerLength())) * 180 / M_PI;
        }
        
        Vector<T> rotateAroundAxis(Vector<T> axis, float angle)
        {
            double rotationMatrix[4][4];
            double inputMatrix[4][1] = {x, y, z, 1.0};
            double outputMatrix[4][1] = {0.0, 0.0, 0.0, 0.0};
            
            double powLenghtOfAxis = axis.getPowerLength();
            double lengthOfAxis = axis.getLength();
            angle = angle * M_PI / 180.0; //converting to radian value
            float x_2 = std::pow(axis.x, 2);
            float y_2 = std::pow(axis.y, 2);
            float z_2 = std::pow(axis.z, 2);
            
            rotationMatrix[0][0] = (x_2 + (y_2 + z_2) * cos(angle)) / powLenghtOfAxis;
            rotationMatrix[0][1] = (axis.x * axis.y * (1 - cos(angle)) - axis.z * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
            rotationMatrix[0][2] = (axis.x * axis.z * (1 - cos(angle)) + axis.y * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
            rotationMatrix[0][3] = 0.0;
            
            rotationMatrix[1][0] = (axis.x * axis.y * (1 - cos(angle)) + axis.z * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
            rotationMatrix[1][1] = (y_2 + (x_2 + z_2) * cos(angle)) / powLenghtOfAxis;
            rotationMatrix[1][2] = (axis.y * axis.z * (1 - cos(angle)) - axis.x * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
            rotationMatrix[1][3] = 0.0;
            
            rotationMatrix[2][0] = (axis.x * axis.z * (1 - cos(angle)) - axis.y * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
            rotationMatrix[2][1] = (axis.y * axis.z * (1 - cos(angle)) + axis.x * lengthOfAxis * sin(angle)) / powLenghtOfAxis;
            rotationMatrix[2][2] = (z_2 + (x_2 + y_2) * cos(angle)) / powLenghtOfAxis;
            rotationMatrix[2][3] = 0.0;
            
            rotationMatrix[3][0] = 0.0;
            rotationMatrix[3][1] = 0.0;
            rotationMatrix[3][2] = 0.0;
            rotationMatrix[3][3] = 1.0;
            
            for(int i = 0; i < 4; i++ )
                for(int j = 0; j < 1; j++){
                    outputMatrix[i][j] = 0;
                    for(int k = 0; k < 4; k++)
                        outputMatrix[i][j] += rotationMatrix[i][k] * inputMatrix[k][j];
                }
            return Vector<T>((T)outputMatrix[0][0], (T)outputMatrix[1][0], (T)outputMatrix[2][0]);
        }
        
        T* toArray()
        {
            return {x, y, z};
        }
        
        static Vector<T> ZERO, XAXIS, YAXIS, ZAXIS;
    };
    template <class T>
    Vector<T> Vector<T>::ZERO(0, 0, 0);
    template <class T>
    Vector<T> Vector<T>::XAXIS(1, 0, 0);
    template <class T>
    Vector<T> Vector<T>::YAXIS(0, 1, 0);
    template <class T>
    Vector<T> Vector<T>::ZAXIS(0, 0, 1);
}

#endif
