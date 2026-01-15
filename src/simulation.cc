/*!
  \file   simulation.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include "simulation.h"
#include <iomanip>


using namespace std;

Simulation::Simulation () :
	reussite_lecture(false)
{
	setMaximum(dim_max); 
	etat_sim = S_STOP;
}

void Simulation::cree_simulation (string nom_fichier) {
	lecture(nom_fichier);
	setMaximum(dim_max); 
}

Simulation::~Simulation() {
	
	for(auto& elem : tab_ptr_Gis) {
		delete elem;
	}
	for(auto& elem : tab_ptr_Bas) {
		delete elem;
	}
}

void Simulation::lecture(string nom_fichier) {
	
    string line;
    ifstream fichier(nom_fichier); 
    if(!fichier.fail()) 
    {
        while(getline(fichier >> ws,line)) 
        {
			if(line[0]=='#')  continue; 
			decodage_ligne(line);
        }
	}
	else reussite_lecture = false;
}

void Simulation::decodage_ligne(string line) {
	istringstream ligne_dec(line);	 
	static int etat(NB_G), i(0), total(0); 
	static int nb_robotsP(0), nb_robotsF(0), nb_robotsT(0), nb_robotsC(0);
	switch(etat) {
		case NB_G : 
			ligne_dec >> total;
			i=0;
			if(total == 0) {
				etat = NB_B; 
				break;
			}else  etat = GISEMENT;
			break;
			
		case GISEMENT :
			Gisement::lectureGis(ligne_dec, tab_ptr_Gis);
			++i;
			if(i == total) {
				etat = NB_B;
				break;
			}
			break;	
		
		case NB_B : 
			ligne_dec >> total;
			i=0;
			if(total == 0) {
				cout << message::success();
				reussite_lecture = true; 
			}else  etat = BASE;
			break;
			
		case BASE :
			Base::lectureBas(ligne_dec, tab_ptr_Bas);
			++i;
			Gisement::inter_gis_bas(tab_ptr_Gis, (*(tab_ptr_Bas[i-1])).getCercleBas());
			for (int k(0); k<4; ++k) {
				if (k == ROB_P) nb_robotsP = (*(tab_ptr_Bas[i-1])).getNbRob(ROB_P); 
				if (k == ROB_F) nb_robotsF = (*(tab_ptr_Bas[i-1])).getNbRob(ROB_F);
				if (k == ROB_T) nb_robotsT = (*(tab_ptr_Bas[i-1])).getNbRob(ROB_T);
				if (k == ROB_C) nb_robotsC = (*(tab_ptr_Bas[i-1])).getNbRob(ROB_C);
			}
			if (nb_robotsC == 0) (*(tab_ptr_Bas[i-1])).erreur_Rcomm();
			etat = conditions(BASE, i, total, nb_robotsP, nb_robotsF, 
							  nb_robotsT, nb_robotsC);
			tab_ptr_Bas[i-1]->setIndex(i-1);
			break; 
		
		case ROBOT_P : 
			(*(tab_ptr_Bas[i-1])).add_Robot(ligne_dec, ROB_P);
			init_gisement(tab_ptr_Bas[i-1]);
			--nb_robotsP;
			etat = conditions(ROBOT_P, i, total, nb_robotsP, nb_robotsF, 
							nb_robotsT, nb_robotsC);
			break;
			
		case ROBOT_F : 
			(*(tab_ptr_Bas[i-1])).add_Robot(ligne_dec, ROB_F);
			--nb_robotsF;
			etat = conditions(ROBOT_F, i, total, nb_robotsP, nb_robotsF, 
							nb_robotsT, nb_robotsC);
			break;
			
		case ROBOT_T : 
			(*(tab_ptr_Bas[i-1])).add_Robot(ligne_dec, ROB_T);
			--nb_robotsT;
			etat = conditions(ROBOT_T, i, total, nb_robotsP, nb_robotsF, 
							nb_robotsT, nb_robotsC);
			break;
			
		case ROBOT_C : 
			(*(tab_ptr_Bas[i-1])).add_Robot(ligne_dec, ROB_C);
			--nb_robotsC;
			etat = conditions(ROBOT_C, i, total, nb_robotsP, nb_robotsF, 
							nb_robotsT, nb_robotsC);
			if (etat != FIN) break;
							
		case FIN :
			cout << message::success();
			reussite_lecture = true;
	}	
}

void Simulation::init_gisement(Base* tb) {
	RobotProspection* ptrLastRP;
	ptrLastRP = (*tb).getTab_ptr_Rp().back();
	if ((*ptrLastRP).getFound() == true) {
		(*ptrLastRP).setGisement(Gisement::find_gis((*ptrLastRP).getPos_gis(),
								 tab_ptr_Gis));
	}
}

Etat_lecture Simulation::conditions(const Etat_lecture& etat, const int& i, 
									const int& total, const int& np, const int& nf, 
									const int& nt, const int& nc) 
{ 
	
	switch (etat) {
		case BASE :
			if (np > 0) return  ROBOT_P; 
			else if(nf > 0) return  ROBOT_F; 
			else if(nt > 0) return  ROBOT_T; 
			else if(nc > 0) return  ROBOT_C; 
			else if (i < total) return  BASE; 
			else return  FIN;
			break;
			
		case ROBOT_P :
			if (np > 0) return  ROBOT_P; 
			else if(nf > 0) return  ROBOT_F; 
			else if(nt > 0) return  ROBOT_T; 
			else if(nc > 0) return  ROBOT_C; 
			else if (i < total) return  BASE; 
			else return  FIN;
			break;
			
		case ROBOT_F :
			if(nf > 0) return ROBOT_F; 
			else if(nt > 0) return  ROBOT_T; 
			else if(nc > 0) return  ROBOT_C; 
			else if (i < total) return  BASE; 
			else return  FIN;
			break;
		
		case ROBOT_T :
			if(nt > 0) return  ROBOT_T; 
			else if(nc > 0) return  ROBOT_C; 
			else if (i < total) return  BASE; 
			else return  FIN;
			break;
			
		case ROBOT_C :
			Etat_lecture eta;
			if(nc > 0) return ROBOT_C; 
			else {
			   (*(tab_ptr_Bas[i-1])).test_Rcomm((*(tab_ptr_Bas[i-1])).getTab_ptr_Rc());
			}
			if (i < total) return BASE; 
			else {
			   eta = FIN;
			}
			(*(tab_ptr_Bas[i-1])).test_Rcomm((*(tab_ptr_Bas[i-1])).getTab_ptr_Rc());
			return eta;
		default  :
			return FIN;
	}
}

void Simulation::ecriture(string nom_fichier) {
		
	ofstream fichier(nom_fichier); 
	if(!fichier.fail()) {
		fichier.precision(2);
		fichier << "# Gisements" << endl;
		gisements_save(fichier);
		fichier << endl;
		fichier << "# Bases" << endl;
		bases_save(fichier);
	}
	else exit(1);
	fichier.close();
}

void Simulation::gisements_save(std::ofstream& fichier) {
	
	fichier.precision(2);
	int nbG = tab_ptr_Gis.size();
	fichier << nbG << endl;
	for (auto& elem : tab_ptr_Gis) {
		fichier.precision(2);
		fichier << (*elem).gisement_info_string() << endl;
	}
}

void Simulation::bases_save(std::ofstream& fichier) {
	int nbB = tab_ptr_Bas.size();
	fichier << nbB  << " # nbB " << endl << endl;
	for (auto elem : tab_ptr_Bas) {
		fichier << (*elem).base_info_string() << endl;
		
		unsigned nbr = (*elem).getNbRob(0);
		(*elem).robots_save(fichier, ROB_P, nbr);
		
		nbr = (*elem).getNbRob(1);
		(*elem).robots_save(fichier, ROB_F, nbr);
		
		nbr = (*elem).getNbRob(2);
		(*elem).robots_save(fichier, ROB_T, nbr);
		
		nbr = (*elem).getNbRob(3);
		(*elem).robots_save(fichier, ROB_C, nbr);
		
		fichier << endl;
	}
}

void Simulation::destruction(Base* ptr_b) { 
	
	(*ptr_b).~Base();
}

void Simulation::idle_sim() {  
	
	nbB = tab_ptr_Bas.size();
	
	if(nbB>0) {
		for(unsigned i(0); i<nbB; ++i) {
			for(unsigned j(0); j<nbB; ++j) {
				update_voisin(tab_ptr_Bas[i], tab_ptr_Bas[j]);
			}
		}
		for(unsigned i(0); i<nbB; ++i) {
			move_robots(tab_ptr_Bas[i]);
			connexion(tab_ptr_Bas[i]);
			tab_ptr_Bas[i] -> maintenance();
			//tab_ptr_Bas[i] -> creation();
			update(tab_ptr_Bas[i]);
		}
		for(unsigned i(0); i < nbB; ++i) {
			if ((*tab_ptr_Bas[i]).getBaseR() <= 0) {
				(*tab_ptr_Bas[i]).~Base();
			}
		(tab_ptr_Bas[i]->getTab_gis_trouve()).clear();  
		}
	}
}

void Simulation::update_voisin(Base* ptrB_1, Base* ptrB_2) {  
	
	Tab_ptr_Robots tab_ptr_R_1 = (*ptrB_1).getTabAllRobots();
	Tab_ptr_Robots tab_ptr_R_2 = (*ptrB_2).getTabAllRobots();
	if(tab_ptr_R_1.size() > 0) {
		for(size_t i(0); i < tab_ptr_R_1.size(); ++i) {
			Cercle c_connex_rob = setCercle((*tab_ptr_R_1[i]).getPos(), rayon_comm);
			if(tab_ptr_R_2.size() > 0) {
				for(size_t j(0); j < tab_ptr_R_2.size(); ++j) {
					if(appartient_cercle(c_connex_rob, (*tab_ptr_R_2[j]).getPos())) {
						if(!test_egalite(c_connex_rob.centre, (*tab_ptr_R_2[j]).getPos())) {
							(*tab_ptr_R_1[i]).setTabVoisins(tab_ptr_R_2[j]);
						}
					}
				}
			}
		}
	}
}

void Simulation::all_visited_to_false (Tab_ptr_Bases tab_ptr_Bases) { 
	
	for (auto bas : tab_ptr_Bases) {
		Tab_ptr_Robots tab_rob_bi = (*bas).getTabAllRobots();
		for (auto rob : tab_rob_bi) {
			(*rob).setVisited(false);
		}
	}
}

void Simulation::connexion(Base* ptrB) { 
	
	(*ptrB).set_remote_false();
	for(auto rob_comm : (*ptrB).getTab_ptr_Rc()) {
		if((*rob_comm).getCentre_de_base()) {
			Tab_ptr_Robots tab_robots_conectes = parcours(rob_comm);
			for(auto rob : tab_robots_conectes) {
				if(test_egalite((*rob).getPosBas(), (*ptrB).getCercleBas().centre)) {
					(*rob).setRemote(true);
				}
			}
		}
	}
}

Tab_ptr_Robots Simulation::parcours(Robot* depart) { 
	Tab_ptr_Robots result_connexion;
	all_visited_to_false(tab_ptr_Bas); 
	rec_parcours(result_connexion, depart);
	return result_connexion;
}

void Simulation::rec_parcours(Tab_ptr_Robots result_connexion, Robot* next_robot)
{
	next_robot->setVisited(true);
	result_connexion.push_back(next_robot);
	
	const Tab_ptr_Robots* ptr_tab_voisins_rob = next_robot->getTabVoisins();
	const Tab_ptr_Robots tab_voisins_rob = (*ptr_tab_voisins_rob);
	
	for(unsigned i(0); i<tab_voisins_rob.size(); ++i){
		if(!(tab_voisins_rob[i]->getVisited())){
			rec_parcours(result_connexion, tab_voisins_rob[i]);
		}
	}
}

void Simulation::dessin_Bases_sim(bool togg_range, bool togg_link) {  
	
	for (auto bas : tab_ptr_Bas) {
		(*bas).dessin_Base(togg_range, togg_link);
	}
}

void Simulation::dessin_Gisements_sim() { 
	
	for (auto gis : tab_ptr_Gis) {
		(*gis).dessin_Gisement();
	}
}

bool Simulation::getReussite_lecture() {
	
	return reussite_lecture;
}

void Simulation::setReussite_lecture(bool reussite) {
	
	reussite_lecture = reussite;
}

void Simulation::renew_sim(Simulation& sim_orig) {
	
	Simulation* sim_temp = &sim_orig;
	Simulation* new_sim = new Simulation();
	sim_temp->~Simulation();
	sim_orig = *new_sim;
}

void Simulation::move_robots (Base* ptr_bas) {		
	
	for(auto rob : ptr_bas->getTabAllRobots()) {
		if(!test_egalite(rob->getPos(), rob->getBut())) {
			P2D pos_init = rob->getPos();
			double x_init(pos_init.X), y_init(pos_init.Y);
			P2D but = rob->getBut();
			Vecteur vect{0,0};
			double norme = norme_init_vect(pos_init, but, vect);
			double x_vect_n(vect.x/norme), y_vect_n(vect.y/norme);
			P2D pos_final = {(x_init)+(x_vect_n*(deltaD)), (y_init)+(y_vect_n*(deltaD))};
			rob->setPos(pos_final);
		}
	}
}

Tab_ptr_Bases* Simulation::getTab_ptr_Bases() {
	
	return &tab_ptr_Bas;
}

void Simulation::update(Base* ptr_bas) {
	ptr_bas->update_remote();
	ptr_bas->update_autonomous();
}

void Simulation::update_resources(Base* ptr_bas) { 
	
	for(auto robF : ptr_bas->getTab_ptr_Rf()) {
		if(robF->getAtteint()) {
			for(auto gis : tab_ptr_Gis) {
				if(test_egalite(gis->getCercleGis().centre, robF->getPos())) {
					robF->creuser_gis(gis);
				}
			}
		}
	}
	for(auto robT : ptr_bas->getTab_ptr_Rt()) {
		if(robT->getAtteint()) {
			for(auto robF : ptr_bas->getTab_ptr_Rf()) {
				if(test_egalite(robT->getPos(), robF->getPos())) {
					robT->addResourcesT(robF->donnerResourceF());
				}
			}
		}
		if(test_egalite(robT->getPos(), (ptr_bas->getCercleBas()).centre)) {
			ptr_bas->addBaseR(robT->donnerResourceT());
		}
	}
}

bool Simulation::check_gisement(Base* ptr_bas, TypeR tr) { 
	
	bool resultat(false);
	switch(tr) {
		case ROB_P:
			for (auto robP : ptr_bas->getTab_ptr_Rp()) {
				for(auto ptr_gis : tab_ptr_Gis) {
					if(appartient_cercle(ptr_gis->getCercleGis(), robP->getPos())) {
						resultat = true;
						ptr_bas->addTab_gis_trouve(ptr_gis);
						robP->setFound(true);
					}
				}
			}
	
		case ROB_F:
			for (auto robF : ptr_bas->getTab_ptr_Rf()) {
				for(auto ptr_gis : tab_ptr_Gis) {
					if(appartient_cercle(ptr_gis->getCercleGis(), robF->getPos())) {
						resultat = true;
						robF->setAtteint(true);
					}
				}
			}
			
		default:
			return resultat;
	}
}
