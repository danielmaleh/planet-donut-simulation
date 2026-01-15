/*!
  \file   base.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef BASE_H_INCLUDED
#define BASE_H_INCLUDED

#include "geomod.h"
#include "gisement.h"
#include "robot.h"
#include "constantes.h"
#include "message.h"

#include <sstream>
#include <vector>
#include <array>
#include <iostream>

class Base;
typedef std::vector<Base*> Tab_ptr_Bases;
typedef std::array<size_t,4> tab_Nb;
enum StadeSim { UP_REMOTE, UP_AUTO};

class Base {
	
public:
	Base (Cercle c, double res, tab_Nb& tab, unsigned coul=0);
	Base (double xb, double yb, double res, tab_Nb& tab, unsigned coul=0) ; //surcharge
	size_t getNbRob(int i);
	Cercle getCercleBas();
	double getBaseR();
	void addBaseR(double val);
	Tab_ptr_RobotsP getTab_ptr_Rp();
	Tab_ptr_RobotsF getTab_ptr_Rf();
	Tab_ptr_RobotsT getTab_ptr_Rt();
	Tab_ptr_RobotsC getTab_ptr_Rc();
	Tab_ptr_Robots getTabAllRobots();
	Tab_ptr_Robots get_robots_remote();
	Tab_ptr_Robots get_robots_autonomous();
	static void lectureBas(std::istringstream& ligne_dec, Tab_ptr_Bases& tab_bas); 
	bool inter_bases (const Base* ptr_bas2);
	void add_Robot(std::istringstream& ligne_dec, TypeR type);
	bool test_uid(unsigned uid);
	void test_Rcomm(const Tab_ptr_RobotsC& tab_c);
	void erreur_Rcomm();
	std::string base_info_string();
	std::string robotP_info_string(RobotProspection* rob);
	std::string robotF_info_string(RobotForage* rob);
	std::string robotT_info_string(RobotTransport* rob);
	std::string robotC_info_string(RobotCommunication* rob);
	void robots_save(std::ofstream& fichier, TypeR tr, int nbr);
	void set_remote_false();
	void init_zero_voisins ();
	void repair(double resource_cost);
	void maintenance();
	void dessin_Base(bool togg_range, bool togg_link);
	void setIndex(unsigned ind);
	unsigned new_uid(Base* ptr_bas);
	void creation();
	void make_Robot(TypeR tr);
	Tab_ptr_Gisements getTab_gis_trouve();
	void addTab_gis_trouve(Gisement* gis);
	void deter_but_Rt(StadeSim stade, Robot* ptr_rob=nullptr, RobotForage* ptr_robF=nullptr); 
	void deter_but_Rf(StadeSim stade, Robot* ptr_rob=nullptr, Gisement* ptr_gis=nullptr);
	void deter_but_Rp(StadeSim stade, Robot* ptr_rob=nullptr);
	void deter_but_Rc(StadeSim stade, Robot* ptr_rob=nullptr);
	P2D deter_but_creation(TypeR tr, Gisement* ptr_gis=nullptr);
	void update_remote();
	void update_autonomous();
	~Base();
	
private:
	Cercle cercleBas;
	double baseR;
	tab_Nb tab_nb_Robots; 
	Tab_ptr_RobotsP tab_ptr_Rp;
	Tab_ptr_RobotsF tab_ptr_Rf;
	Tab_ptr_RobotsT tab_ptr_Rt;
	Tab_ptr_RobotsC tab_ptr_Rc;
	unsigned index_bas;
	Tab_ptr_Gisements tab_gis_trouve; 
	
};

#endif	//BASE_H_INCLUDED	
