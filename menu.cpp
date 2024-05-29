
#include "menu.h"

void Menu::DrawMain(int shapeCount, std::ostream& os)
{
    os<<"------------------------------------"<<std::endl;
    os<<"Shape manager\tLoaded shapes: x"<<shapeCount<<std::endl;
    os<<"(1.) Add shapes from file"<<std::endl;
    os<<"(2.) Add shape from console"<<std::endl;

    if(shapeCount > 0)
    {
        os<<"(3.) Remove shape"<<std::endl;

        os<<"(4.) Move shape"<<std::endl;
        os<<"(5.) Rotate shape"<<std::endl;
        os<<"(6.) Scale shape"<<std::endl;

        os<<"(7.) Get shape in circle"<<std::endl;
        os<<"(8.) Get shape with point"<<std::endl;

        os<<"(9.) List shapes"<<std::endl;

        os<<"(10.) Save to file"<<std::endl;
    }

    os<<"(Press any other key to exit)"<<std::endl;
    os<<std::endl<<"Choice: ";
}

int Menu::GetIndex(Paper& paper, std::ostream& os, std::istream& input)
{
    int idx;

    os<<"Select shape (0-"<<paper.GetShapeCount()-1<<"): ";
    input>>idx;

    while(idx < 0 || idx > (int)paper.GetShapeCount()-1)
    {
        os<<"Select shape (0-"<<paper.GetShapeCount()-1<<"): ";
        input>>idx;
    }

    return idx;
}

Shape* Menu::Selector(Paper& paper, std::ostream& os, std::istream& input)
{
    int idx = GetIndex(paper, os, input);

    Shape* val;
    val = paper.GetShape(idx);

    return val;
}

template<typename T>
T Menu::GetParameter(const mString& question, std::ostream& os, std::istream& input)
{
    T out;

    os<<question;
    input>>out;

    return out;
}

void Menu::menu(std::istream& input, std::ostream& value_out, std::ostream& interface_out)
{
    Paper paper;
    int choice = 0;

    DrawMain(paper.GetShapeCount(), interface_out);

    while((input>>choice).good())
    {
        if(choice == 1)
        {
            interface_out<<"File path:";
            mString path;

            input >> path;

            std::fstream file(path.getText(), std::ostream::in);

            if(file.is_open()) {
                try {
                    file >> paper;
                }
                catch (std::invalid_argument &e) {
                    interface_out << "Invalid argument!" << std::endl;
                }
            }
            else
            {
                interface_out << "File not found!" << std::endl;
            }

        }
        else if(choice == 2)
        {
            interface_out<<"Shape (<name> <cx> <cy> <vx> <vy>):";

            Shape* shape;

            try
            {
                input>>shape;
                paper.AddShape(shape);
            }
            catch(std::invalid_argument& e)
            {
                interface_out<<"Invalid argument!"<<std::endl;
            }

        }
        else if(paper.GetShapeCount() > 0)
        {
            if (choice == 3)
            {
                int idx = GetIndex(paper,interface_out, input);
                paper.RemoveShape(idx);
            }
            else if (choice == 4)
            {
                Shape* shape = Selector(paper,interface_out, input);
                interface_out << "Vector of move (x y):";
                double x, y;
                input >> x >> y;

                Vector v(x, y);

                shape->Move(v);
            }
            else if (choice == 5)
            {
                Shape* shape = Selector(paper,interface_out, input);
                double deg = GetParameter<double>("Amount of rotation (deg): ",interface_out,input);
                shape->Rotate(deg);
            }
            else if(choice == 6)
            {
                Shape* shape = Selector(paper,interface_out, input);
                double x = GetParameter<double>("Amount of scale (x): ",interface_out,input);
                shape->Scale(x);
            }
            else if(choice == 7)
            {
                double r = GetParameter<double>("Radius of circle (r): ",interface_out,input);
                paper.GetShapesInCircle(r,value_out);
            }
            else if(choice == 8)
            {
                interface_out << "Vector of point (x y):";
                double x, y;
                input >> x >> y;

                Vector p(x, y);
                paper.GetShapesWithPoint(p,value_out);
            }
            else if(choice == 9)
            {
                value_out<<paper;
            }
            else if(choice == 10)
            {
                mString path = GetParameter<mString>("Path of file: ",interface_out,input);

                std::fstream file(path.getText(),std::fstream::app);

                file<<paper;

                file.close();
            }
        }
        DrawMain(paper.GetShapeCount(),interface_out);
    }
}

