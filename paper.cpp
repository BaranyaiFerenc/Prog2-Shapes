#include "paper.h"


Paper::Paper():  shapeCount(0){
    shapes = new Shape*[0];
}

void Paper::AddShape(Shape* shape)
{
    if(shape == 0)
        throw std::invalid_argument("Empty pointer - void Paper::AddShape(Shape* shape)");

    Shape** temp = new Shape*[shapeCount+1];

    for(size_t i = 0; i<shapeCount; i++)
    {
        temp[i] = shapes[i];
    }

    temp[shapeCount++] = shape;

    delete[] shapes;

    shapes = temp;
}

void Paper::RemoveShape(const size_t idx)
{
    if(idx >= shapeCount)
        throw std::out_of_range("Out of array - void Paper::RemoveShape(const size_t idx)");

    Shape** temp = new Shape*[shapeCount-1];

    int k = 0;
    for(size_t i = 0; i<shapeCount; i++)
    {
        if(i != idx)
        {
            temp[k] = shapes[i];
            k++;
        }
    }

    delete shapes[idx];
    delete[] shapes;

    shapeCount--;
    shapes = temp;
}

size_t Paper::GetShapeCount() const
{
    return shapeCount;
}

void Paper::GetShapesInCircle(const double r, std::ostream& os) const
{
    for(size_t i = 0; i<shapeCount; i++)
    {
        if(shapes[i]->insideCircle(r))
            os<<shapes[i];
    }
}

void Paper::GetShapesWithPoint(const Vector& v,std::ostream& os) const
{
    for(size_t i = 0; i<shapeCount; i++)
    {
        if(shapes[i]->pointInside(v))
            os<<shapes[i];
    }
}

Shape* Paper::GetShape(const size_t idx)
{
    if(idx >= shapeCount)
        throw std::out_of_range("Out of array - Shape* Paper::GetShape(const size_t idx)");

    return  shapes[idx];
}


std::istream& operator>>(std::istream& input, Paper& paper)
{
    while (!input.eof())
    {
        Shape* newShape = 0;
        input >> newShape;


        paper.AddShape(newShape);
    }

    return input;
}

std::ostream& operator<<(std::ostream& os, const Paper& paper)
{
    for(size_t i = 0; i<paper.shapeCount; i++)
    {
        os<<paper.shapes[i];
    }

    return os;
}

void Paper::Clear()
{
    for(size_t i = 0; i<shapeCount; i++)
        delete shapes[i];

    delete[] shapes;
    shapes = new Shape*[0];
    shapeCount = 0;
}

Paper::~Paper()
{
    for(size_t i = 0; i<shapeCount; i++)
    {
        delete shapes[i];
    }

    delete[] shapes;
}