//tools.h, Adam Coste et Max Ciriani, version 1
#ifndef TOOLS_H
#define TOOLS_H

#include <cmath>
#include <iostream>
#include <cstdlib>

//#include "graphic.h"

constexpr double epsil_zero(0.5);

struct S2d {
    double x = 0.;
    double y = 0.;
};

class Vecteur {
public:
    Vecteur(const S2d& p1 = {0, 0}, const S2d& p2 = {0, 0});
    Vecteur(const S2d& p, const double& norme, const double& angle);
    Vecteur reflechis(const S2d& point);
    double get_x() const{ return x; };
    double get_y() const{ return y; };
    double get_angle() const{ return angle; };
    double get_norme() const{ return norme; };
    void set_x(double x);
    void set_y(double y);
    void set_angle(double angle);
    void set_norme(double norme);
    
private:
    double x = 0.;
    double y = 0.;
    double angle = 0.; // en radians
    double norme = 0.;
};

class Cercle {
public:
    Cercle(S2d centre, double rayon);
    S2d get_centre() const{ return centre; };
    double get_rayon() const{ return rayon; };
    static bool get_epsil(){ return epsil; };
    void set_centre(S2d centre);
    void set_rayon(double rayon);
    static bool epsil;
    static void epsilTrue();
    static void epsilFalse();
    static bool inclusion(const Cercle &c1, const Cercle &c2);
    static bool intrusion(const Cercle &c1, const Cercle &c2);

private:
    S2d centre = {0, 0};
    double rayon = 0.;
};

#endif // TOOLS_H
