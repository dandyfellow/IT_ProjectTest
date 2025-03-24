#include "mobile.h"


int Particule::nbrs_particules = 0;
vector<Particule*> Particule::liste_particule;
vector<Faiseur*> Faiseur::liste_faiseurs;


Mobile::Mobile(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init)
    : position(position_init), vitesse(vitesse_init), alpha(alpha_init), rayon(rayon_init) {}

double Mobile::get_positionx() const {
    return position.x;
}

double Mobile::get_positiony() const {
    return position.y;
}

Particule::Particule(S2d position_init, Vecteur vitesse_init, double alpha_init, int compteur)
    : Mobile(position_init, vitesse_init, alpha_init, 0.), compteur(compteur) {
    ++nbrs_particules;
    liste_particule.push_back(this);
}


Particule::~Particule() {
    --nbrs_particules;
}

int Particule::get_compteur() const {
    return compteur;
}

void Particule::set_compteur(int c) {
    compteur = c;
}

int Particule::get_nbrs_particules() {
    return nbrs_particules;
}

void Particule::set_nbrs_particules(int n) {
    nbrs_particules = n;
}


Faiseur::Faiseur(S2d position_init, Vecteur vitesse_init, double alpha_init, double rayon_init, int nb_elements)
    : Mobile(position_init, vitesse_init, alpha_init, rayon_init), nbs_elements(nb_elements) {
    elements.resize(nbs_elements, position_init);
    liste_faiseurs.push_back(this);
}


bool Faiseur::collisions(const Faiseur* autre) {
    for (const auto &e1 : elements) {
        Cercle c1(e1, rayon);
        for (const auto &e2 : autre->elements) {
            Cercle c2(e2, autre->rayon);
            if (Cercle::intrusion(c1, c2)) {
                return true;
            }
        }
    }
    return false;
}

bool lecture_p(istringstream& data) {
    Cercle arene({0, 0}, r_max);
    double x, y, angle, deplacement, compteur;
    data >> x >> y >> angle >> deplacement >> compteur;

    Cercle c1({x, y}, 0.);
    Vecteur v({x, y}, deplacement, angle);

    if (compteur >= time_to_split || compteur < 0) {
        cout << message::particule_counter(compteur) << endl;
        return false;
    }
    if (!Cercle::inclusion(arene, c1)) {
        cout << message::particule_outside(x, y) << endl;
        return false;
    }
    if (v.get_norme() < 0 || v.get_norme() > d_max) {
        cout << message::mobile_displacement(deplacement) << endl;
        return false;
    }
    return true;
}

bool lecture_f(istringstream& data) {
    double x, y, angle, deplacement, rayon, nbe;
    data >> x >> y >> angle >> deplacement >> rayon >> nbe;

    Vecteur v({x, y}, deplacement, angle);
    Cercle arene({0, 0}, r_max);
    Cercle c2({x, y}, rayon);

    if (nbe <= 0) {
        cout << message::faiseur_nbe(nbe) << endl;
        return false;
    }
    if (rayon < r_min_faiseur || rayon > r_max_faiseur) {
        cout << message::faiseur_radius(rayon) << endl;
        return false;
    }
    if (v.get_norme() < 0 || v.get_norme() > d_max) {
        cout << message::mobile_displacement(deplacement) << endl;
        return false;
    }
    if (!Cercle::inclusion(arene, c2)) {
        cout << message::faiseur_outside(x, y) << endl;
        return false;
    }
    return true;
}

vector<Faiseur*> Faiseur::liste_faiseurs;





// NE PAS TOUCHER CE QU IL Y A APRES_ RIEN EFFACER 

/*int main() {
    // Créer une arène avec un rayon de 10 unités
    Arene arene(10.0);

    // Créer deux Faiseurs qui se touchent après deux mises à jour
    S2d positionFaiseur1 = {0.0, 0.0};
    Vecteur vitesseFaiseur1(positionFaiseur1, 1.0, 0.0); // Vitesse dirigée vers la droite
    Faiseur faiseur1(positionFaiseur1, vitesseFaiseur1, 0.0, 1.0, 5);

    S2d positionFaiseur2 = {2.0, 0.0};
    Vecteur vitesseFaiseur2(positionFaiseur2, 1.0, M_PI); // Vitesse dirigée vers la gauche
    Faiseur faiseur2(positionFaiseur2, vitesseFaiseur2, M_PI, 1.0, 5);

    // Mettre à jour les positions des Faiseurs
    faiseur1.mise_a_jour(arene);
    faiseur2.mise_a_jour(arene);
    faiseur1.mise_a_jour(arene);
    faiseur2.mise_a_jour(arene);

    // Vérifier s'ils se touchent
    if (faiseur1.collisions(&faiseur2)) {
        std::cout << "Les Faiseurs se touchent après deux mises à jour." << std::endl;
    } else {
        std::cout << "Les Faiseurs ne se touchent pas." << std::endl;
    }

    // Créer une Particule qui rebondit
    S2d positionParticule = {5.0, 0.0};
    Vecteur vitesseParticule(positionParticule, 2.0, M_PI / 4); // Vitesse dirigée en diagonale
    Particule particule(positionParticule, vitesseParticule, M_PI / 4);

    // Mettre à jour la position de la Particule
    particule.mise_a_jour(arene);
    particule.mise_a_jour(arene);

    // Afficher la position finale de la Particule
    std::cout << "Position finale de la Particule : ("
              << particule.get_positionx() << ", "
              << particule.get_positiony() << ")" << std::endl;

    return 0;
}*/

   /*void mise_a_jour(const Arene &arene){
        Mobile::mise_a_jour(arene);
        for (const auto& autre : liste_faiseurs){
            if (autre != this && collisions(autre)){
                return; 
            }
        } 
        for(int i = nbs_elements - 1; i > 0; --i){
            elements[i]=elements[i-1];
        } 
        elements[0]={(position.x),(position.y)};
    }*/

     /*void mise_a_jour(const Arene& arene) override{
        Mobile::mise_a_jour(arene);
        ++compteur;
        if(compteur==time_to_split){
            if(nbrs_particules >= nb_particule_max){
                delete this;
            }else{
                Vecteur nouvelle_vitesse1(position, (vitesse.get_norme()*coef_split), alpha+delta_split);
                Particule* particule1 = new Particule(position, nouvelle_vitesse1, alpha+delta_split);
                Vecteur nouvelle_vitesse2(position, (vitesse.get_norme()*coef_split), alpha-delta_split);
                Particule* particule2 = new Particule(position, nouvelle_vitesse2, alpha-delta_split);
                delete this;
            }
        }
    };*/

    /*virtual void mise_a_jour(const Arene& arene){
        position.x += vitesse.get_norme() * cos(alpha);
        position.y += vitesse.get_norme() * sin(alpha);
        if (arene.in_cercle(position, rayon)){
            return;
        }else{
            position.x -= vitesse.get_norme() * cos(alpha);
            position.y -= vitesse.get_norme() * sin(alpha);
            vitesse = vitesse.reflechis(position);
            alpha = vitesse.get_angle(); 
            position.x += vitesse.get_norme() * cos(alpha);
            position.y += vitesse.get_norme() * sin(alpha);
        }       
     };*/