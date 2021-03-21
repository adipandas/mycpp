/*
- Use of stdexcept - standard exception classes.
- use of cmath
- abstraction: Hiding internal details from end user and exposing the interface. 
*/ 

#include <cassert>
#include <cmath>
#include <stdexcept>


class Sphere{
    public:
        Sphere(int radius): radius_(radius), volume_(pi_* 4 * pow(radius_, 3)/3) {
            if (radius<=0){
                throw std::invalid_argument("Radius must be positive!!");
            }
        }

        static float Volume(int radius){
            return pi_ * pow(radius, 3) * 4/3.;
        }

        void Radius(int radius){
            if (radius<=0){
                throw std::invalid_argument("Radius must be positive!!");
            }
            radius_  = radius;
            volume_ = pi_ * 4 * pow(radius_, 3)/3. ;
        }

        int Radius() const{
            return radius_;
        }

        float Volume() const{
            return volume_;
        }
    
    private:
        int radius_;
        static float constexpr pi_{3.14159};
        float volume_;
};


int main(){
    Sphere sph(5);
    assert(sph.Radius() == 5);
    assert(abs(sph.Volume() - 523.6) < 1);

    sph.Radius(3);
    assert(sph.Radius() == 3);
    assert(abs(sph.Volume() - 113.1)<1);

    bool caught{false};
    try{
        sph.Radius(-1);
    } catch (...) {
        caught = true;
    }
    assert(caught);
}
