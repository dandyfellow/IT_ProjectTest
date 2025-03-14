#ifndef TOOLS_H
#define TOOLS_H

#include <iostream>
#include <cmath>

using namespace std;
constexpr double epsil_zero(0.5);

struct S2d {double x=0.; double y=0.;};

class Vecteur { //Vecteur, x, y, angle, norme, avec deux constructeurs 
public:
    Vecteur(const S2d& p1={0,0}, const S2d& p2={0,0});
    Vecteur(const S2d& p, const double& angle, const double& norme);
    Vecteur reflechis(const S2d& point);
    //getters and setters
    double get_x() const;
    double get_y() const;
    double get_angle() const;
    double get_norme() const;
    void set_x(double x);
    void set_y(double y);
    void set_angle(double angle);
    void set_norme(double norme);

private:
    double x=0.;
    double y=0.;
    double angle=0.; //en radians
    double norme=0.;
};

class Cercle {
public:
    Cercle(S2d centre, double rayon);
    //getters and setters
    S2d get_centre() const;
    double get_rayon() const;
    void set_centre(S2d centre);
    void set_rayon(double rayon);
private:
    S2d centre;
    double rayon;
};
//----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//                          INDEPENDENT FUNCTIONS
//---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 bool inclusion(const Cercle &c1, const Cercle &c2);
 bool intrusion(const Cercle &c1, const Cercle &c2);
 void epsilTrue();
 void epsilFalse();

 #endif // TOOLS_H