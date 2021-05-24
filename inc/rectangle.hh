#pragma once

#include "matrix.hh"
#include "vector.hh"
#define SIZE 4

class Rectangle
{
    double angle;
    Vector path;
    Vector center;
    double h;
    double w;
    Vector size[SIZE];

public:

    const Vector &operator [] (int index) const{return size[index];}
    Vector &operator [] (int index){return size[index];}
    Rectangle(Vector center=Vector(), double h=50 ,double w=50);
    void translacja(double angle, Vector path);
};

Rectangle::Rectangle(Vector center, double h, double w)
{
    this->angle=0;
    this->center = center;
    this->h = h;
    this->w = w;
    for (int i = 0; i < SIZE; i++)
    {
        size[i][0] = center[0] - w / 2;
        size[i][1] = center[1] - h / 2;
    }

    size[1][0] += w;

    size[2][0] += w;
    size[2][1] += h;

    size[3][1] += h;
}

void Rectangle::translacja(double angle, Vector path)
{
    this->angle += angle;
    this->path =   this->path+path;
    for (int i = 0; i < SIZE; i++)
    {
        size[i][0] = center[0] + this->path[0] - w / 2;
        size[i][1] = center[1] + this->path[1] - h / 2;
    }

    size[1][0] += w;

    size[2][0] += w;
    size[2][1] += h;

    size[3][1] += h;

    for (int i = 0; i < SIZE; i++)
    {
        size[i] = matrix_rot(this->angle) * size[i];
    }
}

std::ostream &operator<<(std::ostream &Strm,const Rectangle &Pr)
{
    for (int i = 0; i < SIZE; i++)
    {
       Strm<<Pr[i]<<std::endl;
    }
    return Strm;
}