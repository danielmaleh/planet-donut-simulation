/*!
  \file   robot.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef ROBOT_H_INCLUDED
#define ROBOT_H_INCLUDED

#include "geomod.h"
#include "constantes.h"
#include "gisement.h"
#include "message.h"

#include <vector>

class Robot;
class RobotProspection;
class RobotForage;
class RobotTransport;
class RobotCommunication;

typedef std::vector<Robot*> Tab_ptr_Robots;
typedef std::vector<RobotProspection*> Tab_ptr_RobotsP; 
typedef std::vector<RobotForage*> Tab_ptr_RobotsF;
typedef std::vector<RobotTransport*> Tab_ptr_RobotsT;
typedef std::vector<RobotCommunication*> Tab_ptr_RobotsC;
enum TypeR {ROB_P, ROB_F, ROB_T, ROB_C};

class Robot {

public:
	Robot (unsigned u, double d, P2D p, P2D pb, bool att);
	unsigned getUid();
	P2D getPos();
	void setPos(P2D new_pos);
	bool getAtteint();
	void setAtteint(bool val);
	double getDsitanceParcourue();
	void setDsitanceParcourue(double dp);
	P2D getPosBas();
	P2D getBut();
	void setBut(P2D pos_but);
	void setPosBas(P2D pos_b);
	void setRemote(bool rem_bol);
	bool getRemote();
	bool sur_centre_base();
	bool getVisited();
	void setVisited(bool vis);
	void setTabVoisins(Robot* ptr_r);
	Tab_ptr_Robots* getTabVoisins();
	void dessin_Robot (TypeR type_r, bool togg_range, bool togg_link, unsigned index_bas=-1);
	
	
protected:
	const unsigned uid; 
	double distParcourue;
	P2D pos, but, pos_bas;
	bool atteint;
	static const double rayon_connexion;
	bool remote;
	bool visited;
	Tab_ptr_Robots tab_vosins; 
};

class RobotProspection : public Robot {
	
public:
	RobotProspection (unsigned u, double d, P2D p, P2D pb, 
					  bool att, bool ret, bool fnd, P2D pos_gis);
	RobotProspection (unsigned u, double d, P2D p, P2D pb, 
					  bool att, bool ret, bool fnd);
	static RobotProspection* lectureRob(std::istringstream& ligne_dec, unsigned uid);		  
	void setGisement(Gisement* ptr_gis);
	P2D getPos_gis();
	bool getFound();
	void setFound(bool val);
	bool getRetour();
	void setRetour(bool val);
	Gisement* getGisAtteint();

private:
	bool retour, found;
	P2D pos_gis;
	Gisement* gisAtteint;
};


class RobotForage : public Robot {
	
public:
	RobotForage (unsigned u, double d, P2D p, P2D pb, bool att);
	static RobotForage* lectureRob(std::istringstream& ligne_dec, unsigned uid);
	void creuser_gis(Gisement* ptr_gis);
	double donnerResourceF();
	
private:
	double resourcesF;
	
};


class RobotTransport : public Robot {
	
public:
	RobotTransport (unsigned u, double d, P2D p, P2D pb, bool att, bool ret);
	static RobotTransport* lectureRob(std::istringstream& ligne_dec, unsigned uid);
	bool getRetour();
	double getResourcesT();
	void addResourcesT(double val);
	double donnerResourceT();
	
private:
	bool retour;
	double resourcesT;
};


class RobotCommunication : public Robot {
	
public:
	RobotCommunication (unsigned u, double d, P2D p, P2D pb, bool att);
	static RobotCommunication* lectureRob(std::istringstream& ligne_dec, unsigned uid);
	bool getCentre_de_base();
	void setPosBas(P2D pos_b);
	
private:
	bool centre_de_base;

};


#endif	//ROBOT_H_INCLUDED	
