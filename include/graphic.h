/*!
  \file   graphic.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef GRAPHIC_H_INCLUDED
#define GRAPHIC_H_INCLUDED

struct CouleurDessin {
	
	float r;
	float g;
	float b;
};

constexpr CouleurDessin BLACK = {0,0,0};
constexpr CouleurDessin PURPULE {0.5,0,0.5};
constexpr CouleurDessin GREY {0.5,0.5,0.5};
constexpr CouleurDessin RED {1,0,0};
constexpr CouleurDessin GREEN {0,1,0};
constexpr CouleurDessin BLUE {0,0,1};
constexpr CouleurDessin YELLOW {0.8,0.8,0};
constexpr CouleurDessin MAGENTA {1,0,1};
constexpr CouleurDessin CYAN {0,1,1};
constexpr CouleurDessin WHITE {1,1,1};


void graphic_draw_shape(const int width, const int height, int xc, int yc);
void draw_frame(double max);
void dessin_test();
void dessin_lignes (double x1, double y1, double x2, double y2);
void dessin_cercle_connexion (double xc, double yc);
void dessin_cercle (double xc, double yc, double rayon, CouleurDessin couleur);
void dessin_cercle_vide (double xc, double yc, double rayon, CouleurDessin couleur);
void dessin_comm (double xc, double yc, double rayon, CouleurDessin couleur);
void dessin_forag (double xc, double yc, double rayon, CouleurDessin couleur);
void dessin_prosp (double xc, double yc, double rayon, CouleurDessin couleur);
void dessin_trans (double xc, double yc, double rayon, CouleurDessin couleur);



#endif // GRAPHIC_H_INCLUDED
