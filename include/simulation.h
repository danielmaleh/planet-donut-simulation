/*!
  \file   simulation.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef SIMULATION_H_INCLUDED
#define SIMULATION_H_INCLUDED

#include "geomod.h"
#include "message.h"
#include "constantes.h"
#include "base.h"
#include "robot.h"
#include "gisement.h"

#include <vector>
#include <array>
#include <fstream>
#include <iostream>

enum Etat_lecture {NB_G, GISEMENT, NB_B, BASE, ROBOT_P, ROBOT_F, ROBOT_T, 
					   ROBOT_C, FIN};
					   
enum Etat_simul {S_RUNNING, S_STEP, S_STOP, S_SAVE, S_OPEN};

class Simulation {
	
public:
	Simulation ();
	void cree_simulation (std::string nom_fichier);
	void lecture(std::string nom_fichier); 
	void decodage_ligne(std::string line); 
	void ecriture(std::string nom_fichier);
	void init_gisement(Base* tb);
	Etat_lecture conditions(const Etat_lecture& etat, const int& i, const int& total, 
							const int& np, const int& nf, 
							const int& nt, const int& nc);
	
	void run_simulation(Etat_simul); 
	void gisements_save(std::ofstream& fichier);
	void bases_save(std::ofstream& fichier);
	void destruction(Base* ptr_b);
	void idle_sim();
	void update_voisin(Base* ptrB_1, Base* ptrB_2);
	void connexion(Base* ptrB);
	void dessin_Bases_sim(bool togg_range, bool togg_link);
	void dessin_Gisements_sim();
	bool getReussite_lecture();
	void setReussite_lecture(bool reussite);
	static void renew_sim(Simulation& sim_orig);
	void move_robots (Base* ptr_bas);
	Tab_ptr_Bases* getTab_ptr_Bases();
	bool check_gisement(Base* ptr_bas, TypeR tr);
	void update_resources(Base* ptr_bas);
	void update(Base* ptr_bas);
	
	~Simulation();
	
protected:
	Tab_ptr_Robots parcours(Robot* depart);
	static void rec_parcours(Tab_ptr_Robots result_connexion, Robot* next_robot);
	void all_visited_to_false(Tab_ptr_Bases tab_ptr_Bases);

private:
	Tab_ptr_Gisements tab_ptr_Gis;
	Tab_ptr_Bases tab_ptr_Bas;
	Etat_simul etat_sim;
	unsigned nbB;
	bool reussite_lecture;
};

#endif	//SIMULATION_H_INCLUDED	


