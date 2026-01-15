/*!
  \file   base.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include "base.h"
#include <string>

using namespace std;

Base::Base (Cercle c, double res, tab_Nb& tab, unsigned coul) 
	: cercleBas(c), baseR(res) {
	tab_nb_Robots = tab; 
	index_bas = coul;                       
} 

//surcharge
Base::Base (double xb, double yb, double res, tab_Nb& tab, unsigned coul) 
	: Base(setCercle(xb,yb,rayon_base), res, tab, coul) 
{}

Base::~Base() {
	for(auto& elem : tab_ptr_Rp) {
		delete elem;
	}
	for(auto& elem : tab_ptr_Rf) {
		delete elem;
	}
	for(auto& elem : tab_ptr_Rt) {
		delete elem;
	}
	for(auto& elem : tab_ptr_Rc) {
		delete elem;
	}
}

Tab_ptr_RobotsP Base::getTab_ptr_Rp(){
	return tab_ptr_Rp;
}

Tab_ptr_RobotsF Base::getTab_ptr_Rf(){
	return tab_ptr_Rf;
}

Tab_ptr_RobotsT Base::getTab_ptr_Rt(){
	return tab_ptr_Rt;
}

Tab_ptr_RobotsC Base::getTab_ptr_Rc(){
	return tab_ptr_Rc;
}

bool Base::inter_bases (const Base* ptr_bas2) {
	if(intersection_cercles(cercleBas, (*ptr_bas2).cercleBas)) {
		return true;
	}
	return false;
}

size_t Base::getNbRob(int i) {
	if (i>3 || i<0) exit(EXIT_FAILURE);
	return tab_nb_Robots[i];                    
}

Cercle Base::getCercleBas() {
	return cercleBas;
}

void Base::add_Robot(istringstream& ligne_dec, TypeR type) {
	unsigned uid;
	ligne_dec >> uid;
	if(type == ROB_P) {
		if (test_uid(uid)) {
			tab_ptr_Rp.push_back(RobotProspection::lectureRob(ligne_dec, uid));
			(*(tab_ptr_Rp.back())).setPosBas(this->cercleBas.centre);
		}
	}	
	if(type == ROB_F) {
		if (test_uid(uid)) {
			tab_ptr_Rf.push_back(RobotForage::lectureRob(ligne_dec, uid));
			(*(tab_ptr_Rf.back())).setPosBas(this->cercleBas.centre);
		}
	}		
	if(type == ROB_T) {
		if (test_uid(uid)) {
			tab_ptr_Rt.push_back(RobotTransport::lectureRob(ligne_dec, uid));
			(*(tab_ptr_Rt.back())).setPosBas(this->cercleBas.centre);
		}
	}		
	if(type == ROB_C) {
		if (test_uid(uid)) {
			tab_ptr_Rc.push_back(RobotCommunication::lectureRob(ligne_dec, uid));
			(*(tab_ptr_Rc.back())).setPosBas(this->cercleBas.centre);
		}
	}				
}

bool Base::test_uid(unsigned uid) {
	bool res(false);
	for (auto& elem : tab_ptr_Rp) {
		if ((*elem).getUid() == uid) {
			cout << message::identical_robot_uid(uid);
		}
	}
	for (auto& elem : tab_ptr_Rf) {
		if ((*elem).getUid() == uid) {
			cout << message::identical_robot_uid(uid);
		}
	}
	for (auto& elem : tab_ptr_Rt) {
		if ((*elem).getUid() == uid) {
			cout << message::identical_robot_uid(uid);
		}
	}
	for (auto& elem : tab_ptr_Rc) {
		if ((*elem).getUid() == uid) {
			cout << message::identical_robot_uid(uid);
		}
	}
	res = true;
	return res;
}

void Base::lectureBas(istringstream& ligne_dec, Tab_ptr_Bases& tab_ptr_Bas) {
	static unsigned coul(0);
	double xb, yb, resource_b;
	size_t nbP, nbF, nbT, nbC; 
	ligne_dec >> xb >> yb >> resource_b >> nbP >> nbF >> nbT >> nbC;
	tab_Nb tab_nb_Robots_temp {nbP, nbF, nbT, nbC};                    
	Base* ptr_base = new Base (xb, yb, resource_b, tab_nb_Robots_temp, coul); 
	++coul;
	
	if(!(tab_ptr_Bas.empty())) {
		for (auto& elem : tab_ptr_Bas) {
			if ((*ptr_base).inter_bases(elem)) {
				cout << message::base_superposition(xb, yb, (*elem).cercleBas.centre.X,
													(*elem).cercleBas.centre.Y);
			}
		}
	}
	tab_ptr_Bas.push_back(ptr_base);
}

void Base::test_Rcomm(const Tab_ptr_RobotsC& tab_c) {
	bool test (false);
	for(auto& elem : tab_c) {
		if (!test) {
			test = test_egalite((*elem).getPos(),cercleBas.centre);
		}
	}
	if (!test || tab_c.empty()) {
		cout << message::missing_robot_communication(cercleBas.centre.X,
													 cercleBas.centre.Y);
	}
}

void Base::erreur_Rcomm() {
	cout << message::missing_robot_communication(cercleBas.centre.X,
												 cercleBas.centre.Y);
}

string Base::base_info_string() {
	
	string info_bas = to_string(cercleBas.centre.X) + 
					  "  " + to_string(cercleBas.centre.Y) + 
					  "  " + to_string(baseR) + 
					  "  " + to_string(tab_nb_Robots[ROB_P]) + 
					  "  " + to_string(tab_nb_Robots[ROB_F]) + 
					  "  " + to_string(tab_nb_Robots[ROB_T]) + 
					  "  " + to_string(tab_nb_Robots[ROB_C]);
	
	return info_bas;
}

void Base::robots_save(std::ofstream& fichier, TypeR tr, int nbr) {
	
	switch (tr) {
		
		case ROB_P:
			for(int k(0); k< nbr; k++) {
				fichier << "  " << robotP_info_string(tab_ptr_Rp[k]) << endl;
			}
			break;
			
		case ROB_F:
			for(int k(0); k< nbr; k++) {
				fichier << "  " << robotF_info_string(tab_ptr_Rf[k]) << endl;
			}
			break;
			
		case ROB_T:
			for(int k(0); k< nbr; k++) {
				fichier << "  " << robotT_info_string(tab_ptr_Rt[k]) << endl;
			}
			break;
			
		case ROB_C:
			for(int k(0); k < nbr; k++) {
				fichier << "  " << robotC_info_string(tab_ptr_Rc[k]) << endl;
			}
			break;	
	}
}

string Base::robotP_info_string(RobotProspection* rob) {
	
	string info_robP;
	info_robP = to_string((*rob).getUid()) + "  " +
			   to_string((*rob).getDsitanceParcourue()) + "  " +
			   to_string((*rob).getPos().X) + to_string((*rob).getPos().Y) + "  " +
			   to_string((*rob).getBut().X) + to_string((*rob).getBut().Y) + "  " +
			   (((*rob).getAtteint()) ? "true" : "false") + "  " +
			   (((*rob).getRetour()) ? "true" : "false") + 
			   "  " + (((*rob).getFound()) ? "true" : "false") + "  " +
			   to_string((*(*rob).getGisAtteint()).getCercleGis().centre.X) + "  " +
			   to_string((*(*rob).getGisAtteint()).getCercleGis().centre.Y) + "  " +
			   to_string((*(*rob).getGisAtteint()).getCercleGis().rayon) + "  " +
			   to_string((*(*rob).getGisAtteint()).getResources());
	return info_robP;
}

string Base::robotF_info_string(RobotForage* rob) {
	
	string info_robF;
	info_robF = to_string((*rob).getUid()) + "  " +
			   to_string((*rob).getDsitanceParcourue()) + "  " +
			   to_string((*rob).getPos().X) + 
			   "  " + to_string((*rob).getPos().Y) + "  " +
			   to_string((*rob).getBut().X) + 
			   "  " + to_string((*rob).getBut().Y) + "  " +
			   (((*rob).getAtteint()) ? "true" : "false");
	return info_robF;
}

string Base::robotT_info_string(RobotTransport* rob) {
	
	string info_robT;
	info_robT = to_string((*rob).getUid()) + "  " +
			   to_string((*rob).getDsitanceParcourue()) + "  " +
			   to_string((*rob).getPos().X) + 
			   "  " + to_string((*rob).getPos().Y) + "  " +
			   to_string((*rob).getBut().X) + to_string((*rob).getBut().Y) + "  " +
			   (((*rob).getAtteint()) ? "true" : "false") + "  " +
			   (((*rob).getRetour()) ? "true" : "false");
	return info_robT;
}

string Base::robotC_info_string(RobotCommunication* rob) {
	
	string info_robC;
	info_robC = to_string((*rob).getUid()) + "  " +
			   to_string((*rob).getDsitanceParcourue()) + "  " +
			   to_string((*rob).getPos().X) + 
			   "  " + to_string((*rob).getPos().Y) + "  " +
			   to_string((*rob).getBut().X) + 
			   "  " + to_string((*rob).getBut().Y) + "  " +
			   (((*rob).getAtteint()) ? "true" : "false");
	return info_robC;
}

Tab_ptr_Robots Base::getTabAllRobots() {
	
	Tab_ptr_Robots tab_ptr_R;
	
	if(tab_ptr_Rp.size() > 0) {
		for (size_t i(0); i < tab_ptr_Rp.size(); ++i) {
			tab_ptr_R.push_back(tab_ptr_Rp[i]);
		}
	}
	if(tab_ptr_Rf.size() > 0) {
		for (size_t i(0); i < tab_ptr_Rf.size(); ++i) {
			tab_ptr_R.push_back(tab_ptr_Rf[i]);
		}
	}
	if(tab_ptr_Rt.size() > 0) {
		for (size_t i(0); i < tab_ptr_Rt.size(); ++i) {
			tab_ptr_R.push_back(tab_ptr_Rt[i]);
		}
	}
	if(tab_ptr_Rc.size() > 0) {
		for (size_t i(0); i < tab_ptr_Rc.size(); ++i) {
			tab_ptr_R.push_back(tab_ptr_Rc[i]);
		}
	}
	
	return tab_ptr_R;
}

double Base::getBaseR() {
	return baseR;
}

void Base::set_remote_false() { 
	
	for(auto elem : this->getTabAllRobots()) {
		(*elem).setRemote(false);
	}
}

Tab_ptr_Robots Base::get_robots_remote() {  
	
	Tab_ptr_Robots robots_remote;
	for (auto elem : getTabAllRobots()) {
		if((*elem).getRemote()) {
			robots_remote.push_back(elem);
		}
	}
	return robots_remote;
}

Tab_ptr_Robots Base::get_robots_autonomous() {  
	
	Tab_ptr_Robots robots_auto;
	for (auto elem : getTabAllRobots()) {
		if(!(*elem).getRemote()) {
			robots_auto.push_back(elem);
		}
	}
	return robots_auto;
}

void Base::init_zero_voisins () {  
	
	Tab_ptr_Robots tab_ptr_r = getTabAllRobots();
	for (auto ptr_rob : tab_ptr_r) {
		Tab_ptr_Robots* tab_temp = ptr_rob->getTabVoisins();
		(*tab_temp).clear();
	}
}

void Base::repair(double resource_cost) {
	
	baseR -= resource_cost;
}

void Base::maintenance() { 
	
	Tab_ptr_Robots tab_robots = getTabAllRobots();
	for(auto elem : tab_robots) {
		if((*elem).sur_centre_base()) {
			repair(((*elem).getDsitanceParcourue())*cost_repair);
			(*elem).setDsitanceParcourue(0.0);
		}
	}
}

void Base::dessin_Base(bool togg_range, bool togg_link) { 
	
	dessin_cercle_geomod(C_BASE, cercleBas, index_bas%6);
	
	for (auto robP : getTab_ptr_Rp()) {
		(*robP).dessin_Robot(ROB_P, togg_range, togg_link, index_bas%6);
	}
	
	for (auto robF : getTab_ptr_Rf()) {
		(*robF).dessin_Robot(ROB_F, togg_range, togg_link, index_bas%6);
	}
	
	for (auto robT : getTab_ptr_Rt()) {
		(*robT).dessin_Robot(ROB_T, togg_range, togg_link, index_bas%6);
	}
	
	for (auto robC : getTab_ptr_Rc()) {
		(*robC).dessin_Robot(ROB_C, togg_range, togg_link, index_bas%6);
	}
}

void Base::setIndex(unsigned ind) {
	
	index_bas = ind;
}

unsigned Base::new_uid(Base* ptr_bas) {       
	
	Tab_ptr_Robots tab_rob = ptr_bas->getTabAllRobots();
	vector<unsigned> tab_uid;
	unsigned temp (0);
	for(size_t i(0); i < tab_rob.size(); ++i) {
		tab_uid[i] = tab_rob[i]->getUid();       
	}
	for(size_t i(0); i < tab_rob.size(); ++i) {
		if(tab_uid[i]>temp){
			temp = tab_uid[i];
		}
	}
	return temp+1;
}

void Base::creation() {  
	
	static unsigned iteration(1);
	if(iteration > 3) return;
	
	if(baseR > 100){
		if(!tab_gis_trouve.empty()) {
			for(auto ptr_gis : tab_gis_trouve) {
				if((ptr_gis->getResources()) > deltaR){
					make_Robot(ROB_F);
					make_Robot(ROB_T); 
					iteration += 2;
					creation();
				}
			}
		}else {
			make_Robot(ROB_P); 
			iteration++;
		}
	}else if (baseR > 10) {
		make_Robot(ROB_C);
		make_Robot(ROB_P);
		iteration += 2;
		creation();
	}else {
		if(tab_ptr_Rt.empty()) {
		make_Robot(ROB_C);
		iteration++;
		creation();
		}
	}
}

void Base::make_Robot(TypeR tr) { 

	unsigned uid = new_uid(this);
	Gisement* ptr_gis;
	if(!tab_gis_trouve.empty()) {
		ptr_gis = tab_gis_trouve[0];
	}

	switch(tr) {
		case ROB_P:
		{
			RobotProspection* ptr_Rp = new RobotProspection(uid, 0, cercleBas.centre, deter_but_creation(ROB_P), false, false, false);
			tab_ptr_Rp.push_back(ptr_Rp);
			ptr_Rp->setPosBas(this->cercleBas.centre);
			break;
		}
		
		case ROB_F:
		{
			RobotForage* ptr_Rf = new RobotForage(uid, 0, cercleBas.centre, deter_but_creation(ROB_F, ptr_gis), false);
			tab_ptr_Rf.push_back(ptr_Rf);
			ptr_Rf->setPosBas(this->cercleBas.centre);
			break;
		}
		
		case ROB_T:
		{
			RobotTransport* ptr_Rt = new RobotTransport(uid, 0, cercleBas.centre, deter_but_creation(ROB_T, ptr_gis), false, false);
			tab_ptr_Rt.push_back(ptr_Rt);
			ptr_Rt->setPosBas(this->cercleBas.centre);
			break;
		}
		
		case ROB_C:
		{
			RobotCommunication* ptr_Rc = new RobotCommunication(uid, 0, cercleBas.centre, deter_but_creation(ROB_C), false);
			tab_ptr_Rc.push_back(ptr_Rc);
			ptr_Rc->setPosBas(this->cercleBas.centre);
			break;
		}
	}
}

Tab_ptr_Gisements Base::getTab_gis_trouve() {
	
	return tab_gis_trouve;
}

P2D Base::deter_but_creation(TypeR tr, Gisement* ptr_gis) {
	
	P2D but;
	switch(tr) {
		case ROB_P:
		{
			Dir dir = static_cast<Dir> (2*((tab_ptr_Rp.size())%16));
			unsigned nb_rp = getTab_ptr_Rp().size();
			double norme = rayon_comm*(nb_rp/16);
			but = direction(dir,norme);
			return but;
		}
		case ROB_F:
		{
			but = (ptr_gis->getCercleGis()).centre;
			return but;
		}
		case ROB_T:
		{
			but = (ptr_gis->getCercleGis()).centre;
			return but;
		}
		case ROB_C:
		{
			unsigned nb_rc_nonCentre = (getTab_ptr_Rc().size()-1);
			Dir dir = static_cast<Dir> (2*(nb_rc_nonCentre%16));
			double norme = rayon_comm*(nb_rc_nonCentre/16);
			but = direction(dir,norme);
			return but;
		}
		default:
		{
			return cercleBas.centre;
		}
	}		
} 

void Base::deter_but_Rt(StadeSim stade, Robot* ptr_rob, RobotForage* ptr_robF) {
	
	P2D but;   //vect direction a partir du robot
	
	switch(stade) {
		case UP_REMOTE:
		{
			for (auto robT : tab_ptr_Rt) {
				if(robT->getAtteint()) {
					but = cercleBas.centre;
					ptr_rob->setBut(but);
				}
			}
			break;
		}
		
		case UP_AUTO:
		{
			for (auto robT : tab_ptr_Rt) {
				if(robT->getAtteint()) {
					but = cercleBas.centre;
					ptr_rob->setBut(but);
				}
			}
			break;
		}
	}
}

void Base::deter_but_Rf(StadeSim stade, Robot* ptr_rob, Gisement* ptr_gis) {  // dans Base //#
	
	P2D but;   //vect direction a partir du robot
	
	switch(stade) {
		case UP_REMOTE:
		{
			for(auto ptr_rF : getTab_ptr_Rf()) {
				if(ptr_rF->getAtteint()) {
					but = ptr_rF->getPos();
				}
			}
			break;
		}
		
		case UP_AUTO:
		{
			for(auto ptr_rF : getTab_ptr_Rf()) {
				if(ptr_rF->getAtteint()) {
					but = ptr_rF->getPos();
				}
			}
			break;
		}
	}
}

void Base::deter_but_Rp(StadeSim stade, Robot* ptr_rob) { 
	
	P2D but;   
	Dir dir = static_cast<Dir> (2*((tab_ptr_Rp.size())%16));
	
	switch(stade) {
		case UP_REMOTE:
		{
			static unsigned k(0);
			k++;
			for(auto ptr_rP : getTab_ptr_Rp()) {
				int dp = ptr_rP->getDsitanceParcourue();
				if(ptr_rP->getRetour()) {
					but = ptr_rP->getPosBas();
					ptr_rob->setBut(but);
				}
				else if(ptr_rP->getAtteint() == true) {
					if(norme_init_vect(ptr_rP->getPos(), cercleBas.centre) > (maxD_prosp-ptr_rP->getDsitanceParcourue())) {
						but = direction(static_cast<Dir>((dir/2)+1),rayon_comm);
						ptr_rob->setBut(but);
					}else {
						but = cercleBas.centre;
						ptr_rob->setBut(but);
					}
				}else if(dp%7 == 0){
					but = direction(static_cast<Dir>(k%8));
					ptr_rob->setBut(but);
				}
			}
			break;
		}
		
		case UP_AUTO:
		{
			static unsigned k(0);
			k++;
			for(auto ptr_rP : getTab_ptr_Rp()) {
				int dp = ptr_rP->getDsitanceParcourue();
				if(ptr_rP->getRetour()) {
					but = ptr_rP->getPosBas();
					ptr_rob->setBut(but);
				}
				else if(ptr_rP->getAtteint() == true) {
					if(norme_init_vect(ptr_rP->getPos(), cercleBas.centre) <= (maxD_prosp-ptr_rP->getDsitanceParcourue())) {
						ptr_rP->setRetour(true);
						but = cercleBas.centre;
						ptr_rob->setBut(but);
					}
				}else if(dp%7 == 0){
					but = direction(static_cast<Dir>(k%8));
				}
			}
			break;
		}
		
	}
}

void Base::deter_but_Rc(StadeSim stade, Robot* ptr_rob) {  //dans Base  RobotCommunication* Rc //#
	
	P2D but;   //vect direction a partir du robot
	
	switch(stade) {
		case UP_REMOTE:
		{
			ptr_rob->setBut(but);
			break;
		}
		
		case UP_AUTO:
		{
			static unsigned k(0);
			k++;
			for(auto ptr_rC : getTab_ptr_Rc()) {
				int dp = ptr_rC->getDsitanceParcourue();
				if(dp%7 == 0){
				but = direction(static_cast<Dir> (k%8));
				ptr_rob->setBut(but);
				}
			}
			break;
		}
	}
}

void Base::update_remote() {
	
	for(auto robP : tab_ptr_Rp) {
		deter_but_Rp(UP_REMOTE,robP);
	}
	for(auto robF : tab_ptr_Rf) {
		deter_but_Rf(UP_REMOTE,robF);
	}
	for(auto robT : tab_ptr_Rt) {
		deter_but_Rt(UP_REMOTE,robT);
	}
	for(auto robC : tab_ptr_Rc) {
		deter_but_Rc(UP_REMOTE,robC);
	}
}

void Base::update_autonomous() {
	
	for(auto robP : tab_ptr_Rp) {
		deter_but_Rp(UP_AUTO,robP);
	}
	for(auto robF : tab_ptr_Rf) {
		deter_but_Rf(UP_AUTO,robF);
	}
	for(auto robT : tab_ptr_Rt) {
		deter_but_Rt(UP_AUTO,robT);
	}
	for(auto robC : tab_ptr_Rc) {
		deter_but_Rc(UP_AUTO,robC);
	}
}

void Base::addBaseR(double val) {
	
	baseR += val; 
}

void Base::addTab_gis_trouve(Gisement* gis) {
	
	tab_gis_trouve.push_back(gis);
}
