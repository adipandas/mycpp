/*
Private function to encapsulates the hidden checks required for the valid input.
Public Function to encapsulate the information required to calculate the volume of Pyramid.
*/ 


#include <cassert>
#include <stdexcept>


class Pyramid{
    public:
        Pyramid(int length, int width, int height):length_{length}, width_{width}, height_{height}{
            this->Validate();
        }

        int Length() const;
        int Width() const;
        int Height() const;

        void Length(int length);
        void Height(int height);
        void Width(int width);

        float Volume() const;
        
    private:
        int length_{1};
        int width_{1};
        int height_{1};

        void Validate(){
            if (length_<=0 || width_<=0 || height_<=0){
                throw std::invalid_argument("Non-positive dimension");
            }
        }
};


int Pyramid::Length() const{
    return this->length_;
}


int Pyramid::Width() const{
    return this->width_;
}


int Pyramid::Height() const{
    return this->height_;
}


void Pyramid::Length(int length){
    this->length_ = length;
    Validate();
}


void Pyramid::Width(int width){
    this->width_ =  width;
}


void Pyramid::Height(int height){
    this->height_ = height;
    Validate();
}


float Pyramid::Volume() const{
    return this->Length() * this->Width() * this->Height()/3.0;
}


int main(){
    Pyramid p(2, 2, 2);

    assert(p.Length() == 2);
    assert(p.Height() == 2);
    assert(p.Width() == 2);
    assert(abs(p.Volume()-(2*2*2./3.)) < 0.01);

    bool caught{false};
    try{
        Pyramid invalid(-100, -100, -100);
    } catch(...){
        caught = true;
    }
    assert(caught);
    
}