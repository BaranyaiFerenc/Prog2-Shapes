#include <iostream>
#include <fstream>
#include "vector.h"
#include "mystring.h"

#include "shape.hpp"
#include "paper.h"

#include "menu.h"

#include "gtest_lite.h"


///Objektum fájlba írása
/// @param const T& obj - kiírandó objektum
/// @param const mString& path - fájl elérési útja
template<typename T>
void ToFile(const T& obj, const mString& path)
{
    std::fstream file(path.getText(), std::fstream::out);
    file<<obj;
    file.close();
}

///Ellenőrzi a fájlba kiírt kimenet helyességét
/// @param const mString& path - kimeneti fájl elérési útja
/// @param const mString& expected - elvárt szöveg
bool CheckOutput(const mString& path, const mString& expected)
{
    std::fstream file(path.getText(), std::fstream::in);
    mString text;
    char* tmp = new char[256];


    while(file.getline(tmp, 256))
    {
        text += tmp;
        text+='\n';
    }


    text = text.RemoveAt(text.Length()-1, text.Length()-1);
    delete[] tmp;

    file.close();

    return text == expected;
}

///Double értékek kerekítése az összehasonlításokhoz
/// @param double num - kerekítendő érték
/// @param double decimals - tizesdesjegyek száma
double Round(double num, int decimals = 2)
{
    return std::ceil(num * pow(10,decimals)) / pow(10,decimals);
}



void base_test()
{
    mString outputFile = "test_out.txt";

    std::cout<<"mString osztaly teszt\n---------------------------------------------------";

    TEST(mString, Constructors) {
        mString str("Hello");
        EXPECT_STREQ("Hello",str.getText());
        mString str2(str);
        EXPECT_STREQ("Hello",str2.getText());


        ToFile(str2, outputFile);

        EXPECT_TRUE(CheckOutput(outputFile, "Hello"));
    } ENDM

    TEST(mString, operator+) {
        mString str1 = "Hello ";
        mString str2 = "World!";

        EXPECT_STREQ("Hello World!",(str1+str2).getText()); ///mString+mString

        str1 = "Hello ";

        EXPECT_STREQ("Hello World!",(str1+"World!").getText()); ///mString+Char*

        str1 = "Hello World";

        EXPECT_STREQ("Hello World!",(str1+'!').getText()); ///mString+Char

    } ENDM

    TEST(mString, operator+=) {
        mString str1 = "Hello ";
        str1 += "World!";

        EXPECT_STREQ("Hello World!",str1.getText()); ///mString+=Char*

        mString str2 = " How are you";
        str1+=str2;

        EXPECT_STREQ("Hello World! How are you",str1.getText()); ///mString+=mString


        str1+='?';

        EXPECT_STREQ("Hello World! How are you?",str1.getText()); ///mString+=Char

        str2 = " Im fine!";
        str1 += str2.getText();

        EXPECT_STREQ("Hello World! How are you? Im fine!",str1.getText()); ///mString+=Char*
    } ENDM

    TEST(mString, operator==) {
        mString str1 = "Hello World!";
        mString str2 = "Bye World!";

        EXPECT_FALSE(str1 == str2); ///mString==mString
        EXPECT_TRUE(str1=="Hello World!"); ///mString==Char*

    } ENDM

    TEST(mString, operator[]) {
        mString str1 = "Hello World!";

        EXPECT_EQ('o', str1[4]);

        str1[5] = '_';

        EXPECT_STREQ("Hello_World!", str1.getText());

        EXPECT_ANY_THROW(str1[100]); ///Exception test

    } ENDM

    TEST(mString, lowercase) {
        mString str1 = "Hello World!";

        EXPECT_STREQ("hello world!", str1.toLower().getText());
    } ENDM

    TEST(mString, uppercase) {
        mString str1 = "Hello World!";

        EXPECT_STREQ("HELLO WORLD!", str1.toUpper().getText());
    } ENDM

    TEST(mString, Split) {
        mString str1 = "Hello World! How are you?";
        mString* array;

        int n = str1.Split(' ', array);

        EXPECT_EQ(5, n);
        EXPECT_STREQ("Hello", array[0].getText());
        EXPECT_STREQ("World!", array[1].getText());
        EXPECT_STREQ("How", array[2].getText());
        EXPECT_STREQ("are", array[3].getText());
        EXPECT_STREQ("you?", array[4].getText());

        delete[] array;
    } ENDM

    TEST(mString, RemoveAt) {
        mString str1 = "Hello World!";
        mString str2 = str1.RemoveAt(3,6);

        EXPECT_STREQ("Helorld!", str2.getText());
        EXPECT_ANY_THROW(str2.RemoveAt(50,100));

    } ENDM

    TEST(mString, clear) {
        mString str1 = "Hello World!";
        str1.clear();

        EXPECT_STREQ("", str1.getText());

    } ENDM


    std::cout<<"\n\nVektor osztaly teszt\n---------------------------------------------------";

    TEST(Vector, Constructors){
        Vector v1;

        EXPECT_DOUBLE_EQ(0.0,v1.getX());
        EXPECT_DOUBLE_EQ(0.0,v1.getY());

        v1 = Vector(2,3);

        EXPECT_DOUBLE_EQ(2.0,v1.getX());
        EXPECT_DOUBLE_EQ(3.0,v1.getY());

        Vector v2(2,3);
        v2 = v1;

        EXPECT_DOUBLE_EQ(2.0,v2.getX());
        EXPECT_DOUBLE_EQ(3.0,v2.getY());
    } ENDM

    TEST(Vector, operator+){
        Vector v1(-1, 3);
        Vector v2(2,2);

        EXPECT_DOUBLE_EQ(1.0,(v1+v2).getX());
        EXPECT_DOUBLE_EQ(5.0,(v1+v2).getY());
    } ENDM

    TEST(Vector, operator-){
        Vector v1(-1, 3);
        Vector v2(2,2);

        EXPECT_DOUBLE_EQ(-3.0,(v1-v2).getX());
        EXPECT_DOUBLE_EQ(1.0,(v1-v2).getY());
    } ENDM

    TEST(Vector, operator*){
        Vector v1(-1, 3);
        Vector v2(2,2);

        EXPECT_DOUBLE_EQ(-2.0,(v1*v2).getX());
        EXPECT_DOUBLE_EQ(6.0,(v1*v2).getY());

        EXPECT_DOUBLE_EQ(-3.2,(v1*3.2).getX());
        EXPECT_DOUBLE_EQ(9.0,(v1*3.0).getY());
    } ENDM

    TEST(Vector, Length){
        Vector v1(4, 3);

        EXPECT_DOUBLE_EQ(5.0,v1.Length());
    } ENDM

    TEST(Vector, Direction){
        Vector v1(4, 3);

        EXPECT_DOUBLE_EQ(0.8,v1.getDirection().getX());
        EXPECT_DOUBLE_EQ(0.6,v1.getDirection().getY());
    } ENDM

    TEST(Vector, Round){
        Vector v1(4.3432, 3.34);

        Vector rV = v1.Round();

        EXPECT_EQ(4,rV.getX());
        EXPECT_EQ(3,rV.getY());
    } ENDM

    TEST(Vector, Rotate){
        Vector v1(4, 3);
        Vector rV = v1.Rotate(26);

        EXPECT_DOUBLE_EQ(2.29, Round(rV.getX()));
        EXPECT_DOUBLE_EQ(4.45,Round(rV.getY()));
    } ENDM

    std::cout<<"\n\nHaromszog osztaly teszt\n---------------------------------------------------";

    TEST(Triangle, Constructors/GetVertices) {
        Triangle triangle(Vector(0,0),Vector(2,3));

        int n;
        Vector* verts = triangle.GetVertices(n);

        EXPECT_EQ(3,n);

        EXPECT_DOUBLE_EQ(2.0, verts[0].getX());
        EXPECT_DOUBLE_EQ(3.0, verts[0].getY());

        Vector next = verts[0].Rotate(120);

        EXPECT_DOUBLE_EQ(next.getX(), verts[1].getX());
        EXPECT_DOUBLE_EQ(next.getY(), verts[1].getY());

        next = verts[0].Rotate(240);

        EXPECT_DOUBLE_EQ(next.getX(), verts[2].getX());
        EXPECT_DOUBLE_EQ(next.getY(), verts[2].getY());

        delete[] verts;

    } ENDM


    TEST(Triangle, GetSide) {
        Triangle triangle(Vector(0,0),Vector(2,3));

        EXPECT_DOUBLE_EQ(6.25, Round(triangle.GetSide()));

    } ENDM

    TEST(Triangle, Area/Perimeter) {
        Triangle triangle(Vector(0,0),Vector(2,3));

        EXPECT_DOUBLE_EQ(16.89, Round(triangle.GetArea()));
        EXPECT_DOUBLE_EQ(18.74, Round(triangle.GetPerimeter()));

    } ENDM

    TEST(Square, Move/Scale/Rotate) {
        Triangle triangle(Vector(0,0),Vector(2,3));

        triangle.Move(Vector(3,-4));

        EXPECT_DOUBLE_EQ(16.89, Round(triangle.GetArea()));
        EXPECT_DOUBLE_EQ(18.74, Round(triangle.GetPerimeter()));

        EXPECT_DOUBLE_EQ(3.0, triangle.GetCenter().getX());
        EXPECT_DOUBLE_EQ(-4.0, triangle.GetCenter().getY());

        triangle.Scale(2);

        EXPECT_DOUBLE_EQ(67.55, Round(triangle.GetArea()));
        EXPECT_DOUBLE_EQ(37.47, Round(triangle.GetPerimeter()));

        triangle.Rotate(34);

        EXPECT_DOUBLE_EQ(67.55, Round(triangle.GetArea()));
        EXPECT_DOUBLE_EQ(37.47, Round(triangle.GetPerimeter()));


    } ENDM

    TEST(Triangle, PointInside){
        Triangle triangle = Triangle(Vector(0,0),Vector(0,10));

        EXPECT_FALSE(triangle.pointInside(Vector(7,4)));
        EXPECT_TRUE(triangle.pointInside(Vector(0,-1.5)));
    } ENDM

    TEST(Triangle, insideCircle) {
        Triangle triangle = Triangle(Vector(0,0),Vector(0,10));

        EXPECT_FALSE(triangle.insideCircle(0));
        EXPECT_TRUE(triangle.insideCircle(15));
        EXPECT_TRUE(triangle.insideCircle(100));
        EXPECT_TRUE(triangle.insideCircle(10));

    } ENDM

    std::cout<<"\n\nNegyzet osztaly teszt\n---------------------------------------------------";


    TEST(Square, Constructors/GetVertices) {
        Square s(Vector(0,0),Vector(5,5));

        int n;
        Vector* verts = s.GetVertices(n);

        EXPECT_EQ(4,n);

        EXPECT_DOUBLE_EQ(5.0, verts[0].getX());
        EXPECT_DOUBLE_EQ(5.0, verts[0].getY());

        EXPECT_DOUBLE_EQ(-5.0, verts[1].getX());
        EXPECT_DOUBLE_EQ(5.0, verts[1].getY());

        EXPECT_DOUBLE_EQ(-5.0, verts[2].getX());
        EXPECT_DOUBLE_EQ(-5.0, verts[2].getY());

        EXPECT_DOUBLE_EQ(5.0, verts[3].getX());
        EXPECT_DOUBLE_EQ(-5.0, verts[3].getY());

        delete[] verts;

    } ENDM


    TEST(Square, GetSide) {
        Square s(Vector(0,0),Vector(5,5));

        EXPECT_DOUBLE_EQ(10.0, Round(s.GetSide()));

    } ENDM


    TEST(Square, Area/Perimeter) {
        Square s(Vector(0,0),Vector(5,5));

        EXPECT_DOUBLE_EQ(100.0, Round(s.GetArea()));
        EXPECT_DOUBLE_EQ(40.0, Round(s.GetPerimeter()));

    } ENDM

    TEST(Square, Move/Scale/Rotate) {
        Square s(Vector(0,0),Vector(5,5));

        s.Move(Vector(3,-4));

        EXPECT_DOUBLE_EQ(3.0, s.GetCenter().getX());
        EXPECT_DOUBLE_EQ(-4.0, s.GetCenter().getY());

        EXPECT_DOUBLE_EQ(100.0, Round(s.GetArea()));
        EXPECT_DOUBLE_EQ(40.0, Round(s.GetPerimeter()));

        s.Scale(2);

        EXPECT_DOUBLE_EQ(400.0, Round(s.GetArea()));
        EXPECT_DOUBLE_EQ(80.0, Round(s.GetPerimeter()));

        s.Rotate(34);

        EXPECT_DOUBLE_EQ(400.0, Round(s.GetArea()));
        EXPECT_DOUBLE_EQ(80.0, Round(s.GetPerimeter()));


    } ENDM

    TEST(Square, pointInside) {

        Square s(Vector(10,-2),Vector(5,5));

        EXPECT_FALSE(s.pointInside(Vector(0,0)));
        EXPECT_TRUE(s.pointInside(Vector(5,0)));
        EXPECT_TRUE(s.pointInside(Vector(5,-4)));


    } ENDM

    TEST(Square, insideCircle) {

        Square s(Vector(10,-2),Vector(5,5));

        EXPECT_FALSE(s.insideCircle(0));
        EXPECT_FALSE(s.insideCircle(15));
        EXPECT_TRUE(s.insideCircle(18));
        EXPECT_FALSE(s.insideCircle(10));


    } ENDM

    std::cout<<"\n\nKor osztaly teszt\n---------------------------------------------------";


    TEST(Circle, Constructors/GetVertices) {
        Circle circle(Vector(0,0),Vector(5,5));

        int n;
        Vector* verts = circle.GetVertices(n);

        EXPECT_EQ(36,n);

        delete[] verts;

        circle = Circle(Vector(12,-10),Vector(5,0),360);

        verts = circle.GetVertices(n);

        EXPECT_EQ(360,n);

        EXPECT_DOUBLE_EQ(5.0, verts[0].getX());
        EXPECT_DOUBLE_EQ(0.0, verts[0].getY());

        EXPECT_DOUBLE_EQ(0.0, verts[90].getX());
        EXPECT_DOUBLE_EQ(5.0, verts[90].getY());

        EXPECT_DOUBLE_EQ(-5.0, verts[180].getX());
        EXPECT_DOUBLE_EQ(0.0, verts[180].getY());

        EXPECT_DOUBLE_EQ(0.0, verts[270].getX());
        EXPECT_DOUBLE_EQ(-5.0, verts[270].getY());

        delete[] verts;
    } ENDM


    TEST(Circle, GetRadius) {

        Circle circle(Vector(-23,23),Vector(4,4));

        EXPECT_DOUBLE_EQ(5.66, Round(circle.GetRadius()));

    } ENDM


    TEST(Circle, Area/Perimeter) {
        Circle circle(Vector(-23,23),Vector(4,4));

        EXPECT_DOUBLE_EQ(100.54, Round(circle.GetArea()));
        EXPECT_DOUBLE_EQ(35.55, Round(circle.GetPerimeter()));

    } ENDM

    TEST(Circle, Move/Scale) {
        Circle circle(Vector(-23,23),Vector(4,4));

        circle.Move(Vector(3,-4));
        circle.Scale(12);

        EXPECT_DOUBLE_EQ(-20.0, circle.GetCenter().getX());
        EXPECT_DOUBLE_EQ(19.0, circle.GetCenter().getY());

        EXPECT_DOUBLE_EQ(14476.46, Round(circle.GetArea()));
        EXPECT_DOUBLE_EQ(426.52, Round(circle.GetPerimeter()));

    } ENDM

    TEST(Circle, pointInside) {

        Circle circle(Vector(-10,4),Vector(4,4));

        EXPECT_TRUE(circle.pointInside(Vector(0,0)));
        EXPECT_FALSE(circle.pointInside(Vector(10,0)));
        EXPECT_TRUE(circle.pointInside(Vector(0,-4)));

    } ENDM

    TEST(Circle, insideCircle) {

        Circle circle(Vector(-10,4),Vector(4,4));

        EXPECT_FALSE(circle.insideCircle(0));
        EXPECT_FALSE(circle.insideCircle(15));
        EXPECT_TRUE(circle.insideCircle(100));
        EXPECT_FALSE(circle.insideCircle(10));


    } ENDM


    std::cout<<"\n\nPaper osztaly teszt\n---------------------------------------------------";

    TEST(Paper, Constructors/AddShape) {

        Paper paper;

        Shape* triangle = new Triangle(Vector(1,2),Vector(3,2));
        Shape* square = new Square(Vector(5,2),Vector(6,7));
        Shape* circle = new Circle(Vector(10,3),Vector(33,12));


        paper.AddShape(triangle);
        paper.AddShape(square);
        paper.AddShape(circle);

        EXPECT_EQ(3,(int)paper.GetShapeCount());

        Shape* shape = 0;

        EXPECT_ANY_THROW(paper.AddShape(shape));

    } ENDM

    TEST(Paper, RemoveShape/AddShape) {

        Paper paper;

        Shape* triangle = new Triangle(Vector(1,2),Vector(3,2));
        Shape* square = new Square(Vector(5,2),Vector(6,7));

        paper.AddShape(triangle);

        ToFile(paper, outputFile);

        EXPECT_TRUE(CheckOutput(outputFile, "triangle 1 2 3 2"));

        paper.AddShape(square);

        paper.RemoveShape(0);

        EXPECT_EQ(1,(int)paper.GetShapeCount());

        ToFile(paper, outputFile);

        EXPECT_TRUE(CheckOutput(outputFile, "square 5 2 6 7"));

        EXPECT_ANY_THROW(paper.RemoveShape(2));

    } ENDM

    TEST(Paper, ReadFromFile){

        Paper paper;

        std::fstream file("shape_container.txt", std::fstream::in);

        file>>paper;
        file.close();

        ToFile(paper, outputFile);

        file.open(outputFile.getText(), std::fstream::in);
        mString text;
        char* tmp = new char[256];

        while(file.getline(tmp, 256))
        {
            text += tmp;
            text+='\n';
        }

        text = text.RemoveAt(text.Length()-1, text.Length()-1);
        delete[] tmp;

        file.close();


        EXPECT_TRUE(CheckOutput(outputFile, text));

    }ENDM

    TEST(Paper, GetShapesInCircle) {

        Paper paper;

        Shape* triangle = new Triangle(Vector(20,2),Vector(3,2));
        Shape* square = new Square(Vector(5,2),Vector(6,7));

        paper.AddShape(triangle);
        paper.AddShape(square);

        std::fstream file(outputFile.getText(), std::fstream::out);

        paper.GetShapesInCircle(3, file);

        file.close();

        EXPECT_TRUE(CheckOutput(outputFile, ""));

        file.open(outputFile.getText(), std::fstream::out);

        paper.GetShapesInCircle(20, file);

        file.close();

        EXPECT_TRUE(CheckOutput(outputFile, "square 5 2 6 7"));

    } ENDM

    TEST(Paper, GetShapesWithPoint) {

        Paper paper;

        Shape* triangle = new Triangle(Vector(5,2),Vector(3,2));
        Shape* square = new Square(Vector(5,2),Vector(6,7));

        paper.AddShape(triangle);
        paper.AddShape(square);

        std::fstream file(outputFile.getText(), std::fstream::out);

        paper.GetShapesWithPoint(Vector(4,1), file);

        file.close();

        EXPECT_TRUE(CheckOutput(outputFile, "triangle 5 2 3 2\nsquare 5 2 6 7"));

        file.open(outputFile.getText(), std::fstream::out);

        paper.GetShapesWithPoint(Vector(-1,7), file);

        file.close();

        EXPECT_TRUE(CheckOutput(outputFile, "square 5 2 6 7"));

        file.open(outputFile.getText(), std::fstream::out);

        paper.GetShapesWithPoint(Vector(-10,-10), file);

        file.close();

        EXPECT_TRUE(CheckOutput(outputFile, ""));

    } ENDM

    TEST(Paper, GetShape) {

        Paper paper;

        Shape* triangle = new Triangle(Vector(5,2),Vector(3,2));
        Shape* square = new Square(Vector(5,2),Vector(6,7));

        paper.AddShape(triangle);
        paper.AddShape(square);

        EXPECT_ANY_THROW(paper.GetShape(3));

        EXPECT_DOUBLE_EQ(triangle->GetCenter().getX(), paper.GetShape(0)->GetCenter().getX());
        EXPECT_DOUBLE_EQ(triangle->GetCenter().getY(), paper.GetShape(0)->GetCenter().getY());

        EXPECT_DOUBLE_EQ(triangle->GetVertex().getX(), paper.GetShape(0)->GetVertex().getX());
        EXPECT_DOUBLE_EQ(triangle->GetVertex().getY(), paper.GetShape(0)->GetVertex().getY());

    } ENDM

    TEST(Paper, Clear) {

        Paper paper;

        Shape* triangle = new Triangle(Vector(5,2),Vector(3,2));
        Shape* square = new Square(Vector(5,2),Vector(6,7));

        paper.AddShape(triangle);
        paper.AddShape(square);

        paper.Clear();

        EXPECT_EQ(0, (int)paper.GetShapeCount());

    } ENDM

}

#define CPORTA

///Ha nem a JPORTA környezetében fut akkor
///a felhasználói program fut le, ellenben
///az ellenőrző program
#ifndef CPORTA
int main()
{
    Menu::menu();
    return 0;
}
#endif

#ifdef CPORTA

int main()
{
    base_test();

    std::fstream outFile("test_out.txt", std::fstream::out);
    std::fstream inFile("standard_input.txt", std::fstream::in);



    TEST(Menu, Input)
    {
        Menu::menu(inFile,outFile);

        EXPECT_TRUE(CheckOutput("test_out.txt","triangle 1 2 2.25983 4.46018\ntriangle 1 2 9 12"));

    }ENDM


    outFile.close();
    inFile.close();

    return 0;
}
#endif