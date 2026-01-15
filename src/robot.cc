/*!
  \file   robot.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include "robot.h"

using namespace std;

const double Robot::rayon_connexion = rayon_comm;

Robot::Robot (unsigned u, double d, P2D p, P2D pb, bool att)
	: uid(u), distParcourue(d), pos(p), but(pb)
{
	atteint = att;
} 

unsigned Robot::getUid() {
	return uid;
}

P2D Robot::getPos() {
	return pos;
}

RobotProspection::RobotProspection (unsigned u, double d, P2D p, P2D pb, bool att, 
									bool ret, bool fnd, P2D pos_gis)
	: RobotProspection(u, d, p, pb, att, ret, fnd) 
{
	this->pos_gis = pos_gis;
} 

RobotProspection::RobotProspection (unsigned u, double d, P2D p, P2D pb, bool att, 
									bool ret, bool fnd)
	: Robot(u, d, p, pb, att) 
{
	retour = ret;
	found = fnd;
} 

void RobotProspection::setGisement(Gisement* ptr_gis) {
	gisAtteint = ptr_gis;
}

P2D RobotProspection::getPos_gis(){
	return pos_gis;
}

bool RobotProspection::getFound() {
	return found;
}

RobotForage::RobotForage (unsigned u, double d, P2D p, P2D pb, bool att)
	: Robot(u, d, p, pb, att)
{
	resourcesF = 0.0;
} 

RobotTransport::RobotTransport (unsigned u, double d, P2D p, P2D pb, 
								bool att, bool ret)
	: Robot(u, d, p, pb, att)
{
	retour = ret;
} 

RobotCommunication::RobotCommunication (unsigned u, double d, P2D p, P2D pb, bool att)  
	: Robot(u, d, p, pb, att)
{ 
	centre_de_base = false;
} 

RobotProspection* RobotProspection::lectureRob(istringstream& ligne_dec, unsigned uid)
{	
	double dp, x, y, xb, yb, xg, yg, rayong, capaciteg;
	bool att, ret, fnd;
	string att_s, ret_s, fnd_s;

	RobotProspection* rp;
	ligne_dec >> dp >> x >> y >> xb >> yb >> att_s >> ret_s >> fnd_s;
	att = (att_s == "true") ? true : false;
	ret = (ret_s == "true") ? true : false;
	fnd = (fnd_s == "true") ? true : false;
	if (fnd) {
		ligne_dec >> xg >> yg >> rayong >> capaciteg;
		rp = new RobotProspection (uid, dp, init_pt(x,y), init_pt(xb,yb), att, ret, 
								   fnd, init_pt(xg,yg));
		return rp;
	} else {
		rp = new RobotProspection (uid, dp, init_pt(x,y), init_pt(xb,yb), 
								   att, ret, fnd);
		return rp;
	}
}

RobotForage* RobotForage::lectureRob(istringstream& ligne_dec, unsigned uid) {
	
	double dp, x, y, xb, yb;
	bool att;
	string att_s;

	RobotForage* rf;
	ligne_dec >> dp >> x >> y >> xb >> yb >> att_s;
	att = (att_s == "true") ? true : false;
	rf = new RobotForage (uid, dp, init_pt(x,y), init_pt(xb,yb), att);
	return rf;
}

RobotTransport* RobotTransport::lectureRob(istringstream& ligne_dec, unsigned uid) {
	
	double dp, x, y, xb, yb;
	bool att, ret;
	string att_s, ret_s;

	RobotTransport* rt;
	ligne_dec >> dp >> x >> y >> xb >> yb >> att_s >> ret_s;
	att = (att_s == "true") ? true : false;
	ret = (att_s == "true") ? true : false;
	rt = new RobotTransport (uid, dp, init_pt(x,y), init_pt(xb,yb), att, ret); 
	
	return rt;
}

RobotCommunication* RobotCommunication::lectureRob(istringstream& ligne_dec, 
												   unsigned uid) 
{
	double dp, x, y, xb, yb;
	bool att;
	string att_s;

	RobotCommunication* rc;
	ligne_dec >> dp >> x >> y >> xb >> yb >> att_s;
	att = (att_s == "true") ? true : false;
	rc = new RobotCommunication (uid, dp, init_pt(x,y), init_pt(xb,yb), att);
	return rc;
}

bool Robot::getAtteint() {
	return atteint;
}

bool RobotProspection::getRetour() {
	return retour;
}

bool RobotTransport::getRetour() {
	return retour;
}

Gisement* RobotProspection::getGisAtteint() {
	return gisAtteint;
}

double Robot::getDsitanceParcourue() {
	return distParcourue;
}

P2D Robot::getPosBas() {
	return pos_bas;
}

void Robot::setPosBas(P2D pos_b) {
	pos_bas = pos_b;
}

void RobotCommunication::setPosBas(P2D pos_b) {
	pos_bas = pos_b;
	if(test_egalite(pos_bas,pos)) centre_de_base = true;
}

void Robot::setRemote(bool rem_bol) {
	remote = rem_bol;
}

bool Robot::getRemote() {
	return remote;
}

bool Robot::sur_centre_base() {
	return test_egalite(pos_bas, pos);
}

bool RobotCommunication::getCentre_de_base() {
	return centre_de_base;
}

bool Robot::getVisited() {
	
	return visited;
}

void Robot::setVisited(bool vis) {
	
	visited = vis;
}

void Robot::setTabVoisins (Robot* ptr_r) {   
	
	bool est_dedan(false);
	if(tab_vosins.size() > 0) {
		for(auto elem : tab_vosins) {
			if((*elem).getUid() == (*ptr_r).getUid()) est_dedan = true;
		}
	}
	if (!est_dedan) tab_vosins.push_back(ptr_r);
}


Tab_ptr_Robots* Robot::getTabVoisins () {  
	
	return &tab_vosins;
}

void Robot::setDsitanceParcourue(double dp) {
	
	distParcourue = dp;
}

P2D Robot::getBut() {
	
	return but;
} 

void Robot::setBut(P2D pos_but) {
	
	but = pos_but;
}

void Robot::dessin_Robot (TypeR type_r, bool togg_range, bool togg_link, 
						  unsigned index_bas) { 
	
	Cercle c_rob;
	c_rob.centre = pos;
	c_rob.rayon = display_rayon_robot*10;
	if(togg_range) {
		double xc = pos.X;
		double yc = pos.Y;
		dessin_cercle_connexion(xc, yc);
	}
	switch(type_r) {
		case ROB_P:
			dessin_cercle_geomod(C_ROBOT_P, c_rob, index_bas);
			break;
		case ROB_F:
			dessin_cercle_geomod(C_ROBOT_F, c_rob, index_bas);
			break;
		case ROB_T:
			dessin_cercle_geomod(C_ROBOT_T, c_rob, index_bas);	
			break;
		case ROB_C:
			dessin_cercle_geomod(C_ROBOT_C, c_rob, index_bas);
			break;
	}
	if (togg_link) {
		
		for(auto ptr_rob : tab_vosins) {
			P2D p1 = this->pos;
			P2D p2 = ptr_rob->pos;
			dessin_toggle_link(p1,p2);
		}
	}
}

void RobotForage::creuser_gis(Gisement* ptr_gis) {
	
	if(resourcesF < deltaR && ptr_gis->getResources() > deltaR) {
		ptr_gis->reduce_resource();
		resourcesF += deltaR;
	}
}

double RobotForage::donnerResourceF() {
	
	resourcesF -= deltaR;
	return deltaR;
}

void RobotProspection::setFound(bool val) {
	
	found = val;
}

void Robot::setAtteint(bool val) {
	
	atteint = val;
}

void Robot::setPos(P2D new_pos) {

	pos = new_pos;
}

double RobotTransport::getResourcesT(){
	
	return resourcesT;
}

void RobotTransport::addResourcesT(double val) {
	
	resourcesT = val;
}

double RobotTransport::donnerResourceT() {
	
	resourcesT -= deltaR;
	return deltaR;
	
}

void RobotProspection::setRetour(bool val) {
	
	retour = val;
}
