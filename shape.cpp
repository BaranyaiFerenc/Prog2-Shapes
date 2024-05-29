#include <iostream>
#include <cmath>

#include "shape.hpp"

# define PI 3.14159265358979323846

///Alakzat szülő osztály függvényei:
void Shape::Move(const Vector& v)
{
    center+=v;
}

void Shape::Rotate(const double alpha)
{
    vertex = vertex.Rotate(alpha);
}

void Shape::Scale(const double scale)
{
    vertex = vertex*scale;
}


bool Shape::insideCircle(double rad) const
{
    int n = 0;
    Vector* verts = this->GetVertices(n);

    for(int i = 0; i<n; i++)
    {
        if((verts[i]+GetCenter()).Length() > rad)
        {
            delete[] verts;
            return false;
        }
    }

    delete[] verts;
    return true;
}

std::istream& operator>>(std::istream& input, Shape*& shape)
{
    mString name;
    double cx,cy,vx,vy;

    input >> name >> cx >> cy >> vx >> vy;

    name = name.toLower();

    Vector center = Vector(cx,cy);
    Vector vert = Vector(vx,vy);

    if(name == "square")
        shape = new Square(center, vert);
    else if(name == "triangle")
        shape = new Triangle(center, vert);
    else if(name == "circle")
        shape = new Circle(center, vert);
    else
        throw std::invalid_argument("Invalid shape type - std::istream& operator>>(std::istream& input, Shape*& shape)");

    return input;
}

std::ostream& operator<<(std::ostream& os, const Shape* shape)
{
    if(shape == 0)
        throw std::invalid_argument("Empty pointer - std::ostream& operator<<(std::ostream& os, const Shape* shape)");

    shape->Write(os);
    os<<" "<<shape->GetCenter().getX()<<" "<<shape->GetCenter().getY()<<" "<<shape->GetVertex().getX()<<" "<<shape->GetVertex().getY()<<std::endl;

    return os;
}


///Háromszög függvényei:
Vector* Triangle::GetVertices(int& n) const
{
    Vector* vrts = new Vector[3];

    vrts[0] = this->GetVertex();
    vrts[1] = vrts[0].Rotate(120);
    vrts[2] = vrts[1].Rotate(120);

    n = 3;
    return  vrts;
}


bool Triangle::pointInside(const Vector& p) const
{

    int n;
    Vector* verts = GetVertices(n);

    Vector side = (verts[0]-verts[1])*0.5+verts[1];

    double rotation = atan2(side.getX(),side.getY())*(180/M_PI);

    side = side.Rotate(rotation);
    Vector point = verts[2].Rotate(rotation);

    delete[] verts;

    double minY,maxY;

    if(point.getY() > side.getY())
    {
        minY = side.getY();
        maxY = point.getY();
    }
    else
    {
        maxY = side.getY();
        minY = point.getY();
    }

    for(int i = 0; i<3; i++)
    {
        Vector searched = (p-GetCenter()).Rotate(rotation+i*60);

        if(searched.getY() < minY || searched.getY() > maxY)
            return false;
    }

    return true;

}

double Triangle::GetSide() const
{
    int n = 0;
    Vector* verts = GetVertices(n);
    double side = (verts[0]-verts[1]).Length();

    delete[] verts;

    return side;
}

void Triangle::Write(std::ostream& os) const
{
    os<<"triangle";
}

double Triangle::GetArea() const
{
    double s = GetPerimeter()/2;
    double area = s*pow((s-GetSide()),3);
    area = sqrt(area);

    return area;
}

double Triangle::GetPerimeter() const
{
    return GetSide()*3;
}

std::ostream& operator<<(std::ostream& os, const Triangle& triangle)
{
    os<<"Triangle\n";

    os<<"Perimeter: "<<triangle.GetPerimeter()<<std::endl;
    os<<"Area: "<<triangle.GetArea()<<std::endl;
    return os;
}




///Négyzet függvényei:
Vector* Square::GetVertices(int& n) const
{
    Vector* points = new Vector[4];
    n = 4;

    points[0] = GetVertex();
    points[1] = Vector(-GetVertex().getY(),GetVertex().getX());
    points[2] = Vector(-GetVertex().getX(),-GetVertex().getY());
    points[3] = Vector(GetVertex().getY(),-GetVertex().getX());

    return points;
}

double Square::GetSide() const
{
    int n = 0;
    Vector* verts = GetVertices(n);

    double side = (verts[0]-verts[1]).Length();

    delete[] verts;

    return side;
}

bool Square::pointInside(const Vector& p) const
{
    double rotation = atan2(GetVertex().getX(),GetVertex().getY())*(180/M_PI)-45;

    int n;
    Vector* verts = GetVertices(n);


    for(int i = 0; i<n; i++)    ///Csúcsok elforgatása relatívan az alakzat középpontjához hogy egyenesbe álljon a négyzet
    {
        verts[i] = verts[i].Rotate(rotation);
    }

    double minX = verts[0].getX();
    double maxX = verts[0].getX();

    double minY = verts[0].getY();
    double maxY = verts[0].getY();

    for(int i = 0; i<n; i++)    ///Határértékek megkeresése
    {
        if(verts[i].getX() > maxX)
            maxX = verts[i].getX();
        else if(verts[i].getX() < minX)
            minX = verts[i].getX();
        else if(verts[i].getY() > maxY)
            maxY = verts[i].getY();
        else if(verts[i].getY() < minY)
            minY = verts[i].getY();
    }

    Vector rP = (p-GetCenter()).Rotate(rotation);  ///Pont koordinátái relatív a négyzet középpontjához

    delete[] verts;

    return rP.getX() <= maxX && rP.getX()>=minX && rP.getY() <= maxY && rP.getY() >= minY;
}

double Square::GetArea() const
{
    return pow(GetSide(),2);
}

double Square::GetPerimeter() const
{
    return GetSide()*4;
}


void Square::Write(std::ostream& os) const
{
    os<<"square";
}

std::ostream& operator<<(std::ostream& os, const Square& square)
{
    os<<"Square\n";
    os<<"Perimeter: "<<square.GetPerimeter()<<std::endl;
    os<<"Area: "<<square.GetArea()<<std::endl;

    return os;
}




///Kör függvényei:
Circle::Circle(Vector c, Vector v, int n): Shape(c,v), vertCount(n){}

Vector* Circle::GetVertices(int& n) const
{
    Vector* points = new Vector[vertCount];
    n = vertCount;

    double alpha = (360/(double)vertCount);

    for(size_t i = 0; i<vertCount; i++)
    {
        points[i] = GetVertex().Rotate(alpha*i);
    }

    return points;
}

bool Circle::insideCircle(double r) const
{
    return (GetCenter()+(GetCenter().getDirection()*GetRadius())).Length() <= r;
}

bool Circle::pointInside(const Vector& p) const
{
    return (p-GetCenter()).Length()<=(GetVertex()-GetCenter()).Length() ;
}

double Circle::GetRadius() const
{
    return GetVertex().Length();
}

double Circle::GetArea() const
{
    return pow(GetRadius(),2)*PI;
}
double Circle::GetPerimeter() const
{
    return GetRadius()*2*PI;
}


void Circle::Write(std::ostream& os) const
{
    os<<"cirlce";
}

std::ostream& operator<<(std::ostream& os, const Circle& circle)
{
    os<<"Circle\n";
    os<<"Perimeter: "<<circle.GetPerimeter()<<std::endl;
    os<<"Area: "<<circle.GetArea()<<std::endl;

    return os;
}