/*!
  \file   graphic.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include "graphic_gui.h"
#include "constantes.h"

static const Cairo::RefPtr<Cairo::Context>* ptcr(nullptr);

void graphic_set_context(const Cairo::RefPtr<Cairo::Context>& cr) {
	ptcr = &cr;
}

void draw_frame(double max) {

	(*ptcr)->set_line_width(3.0);
	(*ptcr) -> set_source_rgb(WHITE.r, WHITE.g, WHITE.b);
	(*ptcr) -> paint();
	(*ptcr)->set_source_rgb(GREY.r, GREY.g, GREY.b);
	(*ptcr)->rectangle(-max, -max, max*2, max*2);
	(*ptcr)->stroke();
}

void dessin_lignes (double x1, double y1, double x2, double y2) {  
	
	(*ptcr)->set_line_width(2); 

	(*ptcr)->set_source_rgb(PURPULE.r, PURPULE.g, PURPULE.b);
	(*ptcr)->move_to(x1, y1);
	(*ptcr)->line_to(x2, y2);
	(*ptcr)->stroke();
}

void dessin_cercle_connexion (double xc, double yc) {  
	
	double pas = (2.0 * M_PI)/30;
	double rayon = rayon_comm;
	(*ptcr)->set_line_width (1);
	for(double i(2.0 * M_PI); i > 0; i-=2*pas) {
		(*ptcr)->arc(xc, yc, rayon, i, i+pas); 
		(*ptcr)->set_source_rgb(PURPULE.r, PURPULE.g, PURPULE.b);    
		(*ptcr)->stroke();
	}
}

void dessin_cercle (double xc, double yc, double rayon, CouleurDessin couleur) {  
	
	(*ptcr)->arc(xc, yc, rayon, 0.0, 2.0 * M_PI); 
	(*ptcr)->set_source_rgb(couleur.r, couleur.g, couleur.b);    
	(*ptcr)->fill_preserve();
	(*ptcr)->stroke();
}

void dessin_cercle_vide (double xc, double yc, double rayon, CouleurDessin couleur) {  
	
	(*ptcr)->set_line_width (2);
	(*ptcr)->arc(xc, yc, rayon, 0.0, 2.0 * M_PI); 
	(*ptcr)->set_source_rgb(couleur.r, couleur.g, couleur.b);    
	(*ptcr)->stroke();
}

void dessin_prosp (double xc, double yc, double rayon, CouleurDessin couleur) { 
	
	double x1(xc+10*rayon), y1((yc+10*rayon)+20), x2(xc+10*rayon), y2((yc-10*rayon)+20), x3(xc-10*rayon), y3((yc-10*rayon)+20), x4(xc-10*rayon), y4((yc+10*rayon)+20);
	(*ptcr)->set_line_width(1.5); 
	(*ptcr)->set_source_rgb(couleur.r, couleur.g, couleur.b);
	(*ptcr)->move_to(x1, y1);
	(*ptcr)->line_to(x3, y3);
	(*ptcr)->move_to(x4, y4);
	(*ptcr)->line_to(x2, y2);
	(*ptcr)->stroke();
}

void dessin_forag (double xc, double yc, double rayon, CouleurDessin couleur) {  
	
	double x1(xc), y1(yc+20*rayon), x2(xc), y2(yc-20*rayon), x3(xc+20*rayon), y3(yc), x4(xc-20*rayon), y4(yc);
	double x5(xc+10*rayon), y5(yc+10*rayon), x6(xc-10*rayon), y6(yc-10*rayon), x7(xc-10*rayon), y7(yc+10*rayon), x8(xc+10*rayon), y8(yc-10*rayon);
	
	(*ptcr)->set_line_width (1.5);
	(*ptcr)->set_source_rgb(couleur.r, couleur.g, couleur.b);
	(*ptcr)->move_to(x1, y1);
	(*ptcr)->line_to(x2, y2);
	(*ptcr)->move_to(x3, y3);
	(*ptcr)->line_to(x4, y4);
	(*ptcr)->move_to(x5, y5);
	(*ptcr)->line_to(x6, y6);
	(*ptcr)->move_to(x7, y7);
	(*ptcr)->line_to(x8, y8);
	(*ptcr)->stroke();
}

void dessin_trans (double xc, double yc, double rayon, CouleurDessin couleur) {  
	
	double x1(xc+10*rayon), y1(yc+10*rayon), x2(xc+10*rayon), y2(yc-10*rayon), x3(xc-10*rayon), y3(yc-10*rayon), x4(xc-10*rayon), y4(yc+10*rayon);

	(*ptcr)->set_line_width(1.5); 
	(*ptcr)->set_source_rgb(couleur.r, couleur.g, couleur.b);
	(*ptcr)->move_to(x1, y1);
	(*ptcr)->line_to(x2, y2);
	(*ptcr)->line_to(x3, y3);
	(*ptcr)->line_to(x4, y4);
	(*ptcr)->line_to(x1, y1);
	(*ptcr)->stroke();
}

void dessin_comm (double xc, double yc, double rayon, CouleurDessin couleur) {  
	
	(*ptcr)->set_line_width (1);
	(*ptcr)->arc(xc, yc, 5*rayon, 0.25 * M_PI, 0.75 * M_PI);  
	(*ptcr)->arc(xc, yc, 15*rayon, 0.25 * M_PI, 0.75 * M_PI);  
	(*ptcr)->arc(xc, yc, 20*rayon, 0.25 * M_PI, 0.75 * M_PI); 
	(*ptcr)->set_source_rgb(couleur.r, couleur.g, couleur.b);  
	(*ptcr)->stroke();
}
