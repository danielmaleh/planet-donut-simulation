/*!
  \file   gui.h
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

#include "simulation.h"

#include "graphic.h"
#include <gtkmm.h>


enum ButtonType {EXIT_B, OPEN_B, SAVE_B, START_B, STEP_B, TOGG_LINK_B, TOGG_RANGE_B};
enum TypeDessin {D_GISEMENT, D_BASE, D_ROBOT, D_CERCLE_COMM, D_LIGNE_COMM};

struct Frame 
{
	double xMin; 
	double xMax;
	double yMin;
	double yMax;
	double asp;  
	double height;  
	double width;   
};

class Gui;

class MyArea : public Gtk::DrawingArea
{
public:
	MyArea();
	virtual ~MyArea();
	void setFrame(Frame x); 
	void setFileIn(bool fileI);
	bool getFileIn();
	void dessin();
	void setMy_window(Gui* ptr_win);
	void refresh();

private:
    void adjust_frame(double width, double height);
	Frame frame_ref;
	Frame frame;
	bool fileIn;
	Gui* my_window;
	
protected:
	bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
};


class MyBox : public Gtk::Box {
	
public:
	MyBox();
	virtual ~MyBox();
	MyArea* getDessin();
	Gtk::Button* getButton(ButtonType bt);
	Gtk::Box* getBox();
	Gtk::Box* getBottomBox();
	void tree_view_update(); 


private:
	Gtk::Box m_Box, m_Box_Upper, m_Box_Bottom, m_Box_Right;
	Gtk::ButtonBox m_Box_Left;
	Gtk::Button m_Button_Exit;
	Gtk::Button m_Button_Open;
	Gtk::Button m_Button_Save;
	Gtk::Button m_Button_Start;
	Gtk::Button m_Button_Step;
	Gtk::Button m_Button_Toggle_Link;
	Gtk::Button m_Button_Toggle_Range;
	Gtk::Label m_Label_1, m_Label_2;
	
	MyArea m_dessin;
	
		class Columns : public Gtk::TreeModel::ColumnRecord {
		
		public:
			Columns()
			{
			add(_col_id);
			add(_col_nbP);
			add(_col_nbF);
			add(_col_nbT);
			add(_col_nbC);
			add(_col_resource);
			add(_col_resource_percentage);
			}

		Gtk::TreeModelColumn<int> _col_id;
		Gtk::TreeModelColumn<int> _col_nbP;
		Gtk::TreeModelColumn<int> _col_nbF;
		Gtk::TreeModelColumn<int> _col_nbT;
		Gtk::TreeModelColumn<int> _col_nbC;
		Gtk::TreeModelColumn<double> _col_resource;
		Gtk::TreeModelColumn<int> _col_resource_percentage;
	};

	Columns _columns;

	Gtk::ScrolledWindow _scrolled_window;
	Gtk::TreeView _tree_view;

	unsigned count;

};

class Gui : public Gtk::Window {
	
public:
	Gui();
	virtual ~Gui();
	void dessin_gui();
	void setSim_filename(std::string argv);

protected:
	//Signal handlers:
	bool on_idle();
	//Button Signal handlers:
	void on_button_clicked_exit();  
	void on_button_clicked_open();
	void on_button_clicked_save();
	void on_button_clicked_start();
	void on_button_clicked_step();
	void on_button_clicked_toggleLink();
	void on_button_clicked_toggleRange();
	bool on_key_press_event(GdkEventKey * key_event);
	Gtk::Label m_Label_Info;
	bool running, step, toggle_link, toggle_range, draw_link;

	MyBox m_box;
	std::string sim_filename;
	Simulation* simulation;
	
};


#endif // GUI_H_INCLUDED

