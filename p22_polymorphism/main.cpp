#include "polymorphism.h"


int main(){
    Hello();
    Hello(Human());
    Hello(Dog());

    ParticleModel p;
    BicycleModel b;

    p.Move(10, PI/9.);
    b.Move(10, PI/9);

    assert(p.x != b.x);
    assert(p.y != b.y);
    assert(p.theta != b.theta);


    Triangle t(3, 2);
    Rectangle r(3, 2);

    assert(t.Area() == 3);
    assert(r.Area() == 6);

    Point p1(10, 20), p2(30, 40);
    Point p3 = p1+p2;
    
    assert(p3.x == p1.x + p2.x);
    assert(p3.y == p1.y + p2.y);

}
