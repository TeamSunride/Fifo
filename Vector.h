#ifndef VECTOR_LIBRARY_H
#define VECTOR_LIBRARY_H

#include <iostream>
#include <cmath>

template<typename T>
class Vector {
public:
    Vector();
    // constructors
    explicit Vector(int s);
    Vector(std::initializer_list<T> lst);

    int size() const;

    Vector(const Vector& a);
    Vector& operator=(const Vector& a); // copy assignment

    // operators
    /**
     * @brief operator []
     * @param i
     * @return the i-th element of the vector
     */
    T& operator[](int i);

    /**
     * @brief operator / : divide all elements by a scalar
     * @param scalar
     * @return the vector divided by the scalar
     */
    Vector<T> operator/(double scalar);

    /**
     * @brief operator /= : divide equals all elements by a scalar
     * @param scalar
     * @return reference to the caller vector
     */
    Vector<T>& operator/=(double scalar);

    /**
     * @brief operator * : multiply all elements by a scalar
     * @param scalar
     * @return the vector multiplied by the scalar
     */
    Vector<T> operator*(double scalar);

    /**
     * @brief operator *= : multiply equals all elements by a scalar
     * @param scalar
     * @return reference to the caller vector
     */
    Vector<T>& operator*=(double scalar);

    /**
     * @brief operator += : add equals two vectors of the same size together
     * @param v
     * @return reference to the caller vector
     */
    Vector<T>& operator+=(Vector<T> v);
    /**
     * @brief operator -= : subtract v from caller vector
     * @param v
     * @return reference to the caller vector
     */
    Vector<T>& operator-=(Vector<T> v);

    /**
     * @brief operator + : add two vectors of the same size together
     * @param v
     * @return the result of the sum
     */
    Vector<T> operator+(Vector<T> v);

    /**
     * @brief operator - : subtract v from caller vector
     * @param v
     * @return the result of the sum
     */
    Vector<T>operator-(Vector<T> v);

    // TODO: iterators? begin functions for range-for?
    // Vector operations
    /**
     * @brief calculate the norm of a vector
     * @return the norm of the caller vector
     */
    double norm() const;

    /**
     * @brief calculate the dot product of the caller vector and v
     * @param v
     * @return the dot (scalar) product of the caller vector and v
     */
    double dot(Vector<T> v) const;

    /**
     * @brief normalise the caller vector
     * @return reference to the normalised caller vector
     */
    Vector<T>& normalize();

    /**
     * @brief normalise the caller vector
     * @return the normalised caller vector.
     */
    Vector<T> normalized() const;

    /**
     * @brief calculate the cross product of the caller vector and v
     * @param v
     * @return the cross product of the caller vector and v
     */
    Vector<T> cross(Vector<T> v) const;

    /**
     * @brief calculate the direction cosines triad of the caller vector
     * @param v
     * @return the direction cosines triad of the caller vector
     */
    Vector<T> directionCosines() const;


    ~Vector() { delete[] elem; } // destructor - implicit definition
private:
    T* elem;
    int sz;
};


#include "Vector.tpp"

#endif //VECTOR_LIBRARY_H
