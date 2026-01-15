/*!
  \file   gui.cc
  \author Imane Jennane , Daniel Elmaleh
			310900			311287
  \date   Mai 2021
*/

#include <cairomm/context.h>
#include "graphic.h"
#include "gui.h"
#include "constantes.h"
#include "graphic_gui.h"

#define GTK_COMPATIBILITY_MODE

#ifdef GTK_COMPATIBILITY_MODE
namespace Gtk
{
	template<class T, class... T_Args>
	auto make_managed(T_Args&&... args) -> T*
	{
	return manage(new T(std::forward<T_Args>(args)...));
	}
}
#endif

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame);

using namespace std;

MyArea::MyArea() :
	fileIn(false), my_window(nullptr)
{
}

MyArea::~MyArea() {
	
}

MyArea* MyBox::getDessin() {
	
	return &m_dessin;
}

MyBox::MyBox() :
	m_Box(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box_Upper(Gtk::ORIENTATION_HORIZONTAL, 10),
	m_Box_Bottom(Gtk::ORIENTATION_HORIZONTAL, 10),
	m_Box_Right(Gtk::ORIENTATION_VERTICAL, 10),
	m_Box_Left(Gtk::ORIENTATION_VERTICAL),
	m_Button_Exit("Exit"),
	m_Button_Open("Open"),
	m_Button_Save("Save"),
	m_Button_Start("Start"),
	m_Button_Step("Step"),
	m_Button_Toggle_Link("Toggle_Link"),
	m_Button_Toggle_Range("Toggle_Range"),
	m_Label_1("General"),
	m_Label_2("Toggle display")
{

	m_Box.pack_start(m_Box_Upper);
	
	m_Box_Bottom.add(_scrolled_window);
	_scrolled_window.set_size_request(-1, 200);  
	_scrolled_window.add(_tree_view);

	_scrolled_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC,
						  Gtk::PolicyType::POLICY_AUTOMATIC);
	_scrolled_window.set_hexpand();

	_tree_view.append_column("uid", _columns._col_id);
	_tree_view.append_column("nbP", _columns._col_nbP);
	_tree_view.append_column("nbF", _columns._col_nbF);
	_tree_view.append_column("nbT", _columns._col_nbT);
	_tree_view.append_column("nbC", _columns._col_nbC);
	_tree_view.append_column_numeric("Amount resource", _columns._col_resource, "%.2f");

	auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
	int cols_count = _tree_view.append_column("Mission completeness", *cell);

	auto progress_col = _tree_view.get_column(cols_count - 1);
	if(progress_col)
	progress_col->add_attribute(cell->property_value(),
								_columns._col_resource_percentage);
								
	m_Box.pack_start(m_Box_Bottom);
	
	m_Box_Upper.pack_start(m_Box_Left);
	m_Box_Upper.pack_start(m_Box_Right);
	
	Frame fr = {-dim_max, dim_max, -dim_max, dim_max, 1, 500, 500};
	m_dessin.setFrame(fr); 
	
	m_dessin.set_size_request(600,600);
	m_Box_Right.pack_start(m_dessin);

	m_Box_Left.pack_start(m_Label_1);
	m_Box_Left.pack_start(m_Button_Exit,false,false);
	m_Box_Left.pack_start(m_Button_Open,false,false);
	m_Box_Left.pack_start(m_Button_Save,false,false);
	m_Box_Left.pack_start(m_Button_Start,false,false);
	m_Box_Left.pack_start(m_Button_Step,false,false);
	m_Box_Left.pack_start(m_Label_2);
	m_Box_Left.pack_start(m_Button_Toggle_Link,false,false);// keep fixed width
	m_Box_Left.pack_start(m_Button_Toggle_Range,false,false); // and aligned to left;
	m_Box_Left.set_halign(Gtk::ALIGN_START);
	m_Box_Left.set_valign(Gtk::ALIGN_START);

}

MyBox::~MyBox()
{
}


Gtk::Button* MyBox::getButton(ButtonType bt) {
	switch (bt) {
		case EXIT_B :
			return &m_Button_Exit;
		case OPEN_B :
			return &m_Button_Open;
		case SAVE_B :
			return &m_Button_Save;
		case START_B :
			return &m_Button_Start;
		case STEP_B :
			return &m_Button_Step;
		case TOGG_LINK_B :
			return &m_Button_Toggle_Link;
		case TOGG_RANGE_B :
			return &m_Button_Toggle_Range;
	}
	return &m_Button_Exit;
}


Gtk::Box* MyBox::getBox() {
	return &m_Box;
}


Gtk::Box* MyBox::getBottomBox() {
	return &m_Box_Bottom;
}

Gui::Gui() : 
	running(false), step(false), toggle_link(false), toggle_range(false), draw_link(false)
{
	
	simulation = new Simulation();
	
	add(*(m_box.getBox()));

	set_title("Planet Donut");
	set_border_width(0);
	
	(*m_box.getButton(EXIT_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_exit) );

	(*m_box.getButton(OPEN_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_open) ); 
			  
	(*m_box.getButton(SAVE_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_save) ); 
			  
	(*m_box.getButton(START_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_start) ); 
			  
	(*m_box.getButton(STEP_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_step) ); 
			  
	(*m_box.getButton(TOGG_LINK_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_toggleLink) ); 
			  
	(*m_box.getButton(TOGG_RANGE_B)).signal_clicked().connect(sigc::mem_fun(*this,
			  &Gui::on_button_clicked_toggleRange) ); 
			  
	Glib::signal_idle().connect( sigc::mem_fun(*this, &Gui::on_idle) );
	
	add_events(Gdk::KEY_RELEASE_MASK);
	
	
	(*(m_box.getDessin())).setMy_window(this);

	show_all_children();
}

Gui::~Gui()
{
}

//Button Signal handlers:
void Gui::on_button_clicked_exit() {
	
	exit(0);
}

void Gui::on_button_clicked_save() {
	
	running = false;
	step = false;
	
	Gtk::FileChooserDialog dialog("Please choose a file",
								  Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Save", Gtk::RESPONSE_OK);

	m_Label_Info.set_text("choosing a file");

	int result = dialog.run();

	m_Label_Info.set_text("Done choosing a file");

	switch(result) {
		
		case(Gtk::RESPONSE_OK):
		{
			if(m_box.getDessin()->getFileIn()) {
				std::cout << "Open clicked." << std::endl;
				std::string filename = dialog.get_filename();
				std::cout << "File selected: " <<  filename << std::endl;
				simulation->ecriture(filename);
				MyArea* ptr_dessin = m_box.getDessin();
				ptr_dessin->refresh();
				break;
			}
		}
		case(Gtk::RESPONSE_CANCEL):
		{
			std::cout << "Cancel clicked." << std::endl;
			break;
		}
		default:
		{
			std::cout << "Unexpected button clicked." << std::endl;
			break;
		}
	}
}

void Gui::on_button_clicked_start() {
	
	if(m_box.getDessin()->getFileIn()) {
		if(running) {
			running = false;
			(*m_box.getButton(START_B)).set_label("Start");
		}
		else {
			running = true;
			(*m_box.getButton(START_B)).set_label("Stop");
		}
	}
}

void Gui::on_button_clicked_step() {
	
	if(m_box.getDessin()->getFileIn()) {
		if(!running) {
			step = true;
		}
		else {
			running = false;
			(*m_box.getButton(START_B)).set_label("Start");
		}
	}
	
	MyArea* ptr_dessin = m_box.getDessin();
	ptr_dessin->refresh();
}

void Gui::on_button_clicked_toggleLink() {
	
	if(m_box.getDessin()->getFileIn()) {
		if(!toggle_link) {
			toggle_link = true;
		}
		else {
			toggle_link = false;
		}
	}
	MyArea* ptr_dessin = m_box.getDessin();
	ptr_dessin->refresh();
}

void Gui::on_button_clicked_toggleRange() {
	
	if(m_box.getDessin()->getFileIn()) {
		if(!toggle_range) toggle_range = true;
		else toggle_range = false;
	}
	MyArea* ptr_dessin = m_box.getDessin();
	ptr_dessin->refresh();
}


void Gui::on_button_clicked_open() {
	
	Gtk::FileChooserDialog dialog("Please choose a file",
								  Gtk::FILE_CHOOSER_ACTION_OPEN);
	dialog.set_transient_for(*this);

	dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
	dialog.add_button("_Open", Gtk::RESPONSE_OK);

	m_Label_Info.set_text("choosing a file");
	
	int result_temp;

	do {
		//Show the dialog and wait for a user response:
		int result = dialog.run();
		result_temp = result;
		m_Label_Info.set_text("Done choosing a file");
		
		switch(result) {
		
			case(Gtk::RESPONSE_OK):
			{
				std::cout << "Open clicked." << std::endl;
				std::string filename = dialog.get_filename();
				std::cout << "File selected: " <<  filename << std::endl;
				if(simulation->getReussite_lecture()) {
					MyArea* ptr_dessin = m_box.getDessin();
					ptr_dessin->setFileIn(false);
					Simulation::renew_sim((*simulation));
				}
				setSim_filename(filename);
				break;
			}
			case(Gtk::RESPONSE_CANCEL):
			{
				std::cout << "Cancel clicked." << std::endl;
				break;
			}
			default:
			{
				std::cout << "Unexpected button clicked." << std::endl;
				break;
			}
		}
	}while(!(simulation->getReussite_lecture()) && result_temp==Gtk::RESPONSE_OK);
}

void MyArea::setFileIn(bool fileI) {
	
	fileIn = fileI;
	refresh();
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
	graphic_set_context(cr);
	
	Gtk::Allocation allocation = get_allocation();
	const double width = allocation.get_width();
	const double height = allocation.get_height();
	
	adjust_frame(width, height);
 
	orthographic_projection(cr, frame); 
	
	draw_frame(dim_max); //?
	
	if(fileIn) {
		dessin();
	}
	return true;
}



void MyArea::setFrame(Frame x)
{
	frame_ref = x;
	frame = frame_ref;
} 

void MyArea::adjust_frame(double width, double height)
{
	
	frame.width  = width;
	frame.height = height;
	

    double new_aspect_ratio((double)width/height);
    if( new_aspect_ratio > frame_ref.asp)
    {
	    frame.yMax = frame_ref.yMax ;
	    frame.yMin = frame_ref.yMin ;	
	  
	    double delta(frame_ref.xMax - frame_ref.xMin);
	    double mid((frame_ref.xMax + frame_ref.xMin)/2);
	    frame.xMax = mid + 0.5*(new_aspect_ratio/frame_ref.asp)*delta ;
	    frame.xMin = mid - 0.5*(new_aspect_ratio/frame_ref.asp)*delta ;		  	  
    }
    else
    {
	    frame.xMax = frame_ref.xMax ;
	    frame.xMin = frame_ref.xMin ;
	  	  
 	    double delta(frame_ref.yMax - frame_ref.yMin);
	    double mid((frame_ref.yMax + frame_ref.yMin)/2);
	    frame.yMax = mid + 0.5*(frame_ref.asp/new_aspect_ratio)*delta ;
	    frame.yMin = mid - 0.5*(frame_ref.asp/new_aspect_ratio)*delta ;		  	  
    }
}

static void orthographic_projection(const Cairo::RefPtr<Cairo::Context>& cr, 
									Frame frame)
{

	cr->translate(frame.width/2, frame.height/2);

	cr->scale(frame.width/(frame.xMax - frame.xMin), 
             -frame.height/(frame.yMax - frame.yMin));
  

	cr->translate(-(frame.xMin + frame.xMax)/2, -(frame.yMin + frame.yMax)/2);
}

bool Gui::on_idle()
{
	if(running) {

		Tab_ptr_Bases t_ptr_Bs = (*(simulation->getTab_ptr_Bases()));
		for(auto elem : t_ptr_Bs) {
			elem->init_zero_voisins();
		}
		simulation->idle_sim();
		MyArea* ptr_dessin = m_box.getDessin();
		ptr_dessin->refresh();
		
	}
	else if(step) {
		Tab_ptr_Bases t_ptr_Bs = (*(simulation->getTab_ptr_Bases()));
		for(auto elem : t_ptr_Bs) {
			elem->init_zero_voisins();
		}
		//appelle a idle_sim
		simulation->idle_sim();
		step = false;
		MyArea* ptr_dessin = m_box.getDessin();
		ptr_dessin->refresh();
	}
	
	MyArea* ptr_dessin = m_box.getDessin();
	ptr_dessin->refresh();

	return true;  
}

void MyArea::refresh() 
{
	auto win = get_window();
	if(win)
	{
		Gdk::Rectangle r(0,0, get_allocation().get_width(), 
						      get_allocation().get_height());
								
		win->invalidate_rect(r,false);
	}
}

void MyArea::setMy_window(Gui* ptr_win) {
	
	my_window = ptr_win;
	refresh();
}

void Gui::dessin_gui() { 

		simulation->dessin_Gisements_sim();
		simulation->dessin_Bases_sim(this->toggle_range, this->toggle_link);

}

void MyArea::dessin() {
	
	(*my_window).dessin_gui();
	refresh();
}

bool Gui::on_key_press_event(GdkEventKey * key_event)
{
	if(key_event->type == GDK_KEY_PRESS)
	{
		switch(gdk_keyval_to_unicode(key_event->keyval))
		{
			case '1'://step
				on_button_clicked_step();
				break;
			case 's'://start-stop
				on_button_clicked_start();
				break;
		}
	}
	return Gtk::Window::on_key_press_event(key_event);
}

bool MyArea::getFileIn() {
	
	return fileIn;
}

void Gui::setSim_filename(string argv) {
		
	sim_filename = argv;
	simulation->cree_simulation(sim_filename);
	MyArea* ptr_dessin = m_box.getDessin();
	ptr_dessin->setFileIn(true);
	ptr_dessin->refresh();
}


//~ // ==============================================================================
//~ // cette constante et le modèle de struct qui suit simulent les données que pourrait
//~ // fournir le module simulation en réponse à une demande de tree_view_update()
//~ constexpr unsigned max_tab(10);

//~ struct SimData
//~ {
  //~ unsigned nbP;
  //~ unsigned nbF;
  //~ unsigned nbT;
  //~ unsigned nbC;
  //~ double ressource;
  //~ double ressource_p;
//~ };


//~ // =================================


//~ Scroll::Scroll()
     //~ :_v_box(Gtk::ORIENTATION_VERTICAL, 10),
      //~ m_button("Add one more"), count(0)
//~ {
  //~ set_title("démo scroll");
  //~ // Sets the border width of the window. // cosmetique
  //~ set_border_width(5);

  //~ // When the button receives the "clicked" signal, it will call the
  //~ // on_button_clicked() method defined below.
  //~ m_button.signal_clicked().connect(sigc::mem_fun(*this,
              //~ &Scroll::on_button_clicked));

  //~ add(_v_box);
 
  //~ // This packs the buttonfirst into the vertical box
  //~ _v_box.add(m_button);
  
  //~ // This is the part for the scrolled_window
  //~ _v_box.add(_scrolled_window);
  //~ _scrolled_window.set_size_request(500, 200);  // replace 500 by -1 for the project
  //~ _scrolled_window.add(_tree_view);

  //~ _scrolled_window.set_policy(Gtk::PolicyType::POLICY_AUTOMATIC,
							  //~ Gtk::PolicyType::POLICY_AUTOMATIC);
  //~ _scrolled_window.set_hexpand();

  //~ _tree_view.append_column("uid", _columns._col_id);
  //~ _tree_view.append_column("nbP", _columns._col_nbP);
  //~ _tree_view.append_column("nbF", _columns._col_nbF);
  //~ _tree_view.append_column("nbT", _columns._col_nbT);
  //~ _tree_view.append_column("nbC", _columns._col_nbC);
  //~ _tree_view.append_column_numeric("Amount resource", _columns._col_resource, "%.2f");

  //~ auto cell = Gtk::make_managed<Gtk::CellRendererProgress>();
  //~ int cols_count = _tree_view.append_column("Mission completeness", *cell);

  //~ auto progress_col = _tree_view.get_column(cols_count - 1);
  //~ if(progress_col)
	//~ progress_col->add_attribute(cell->property_value(),
								//~ _columns._col_resource_percentage);

  //~ show_all_children();
//~ }

//~ Scroll::~Scroll()
//~ {
//~ }

//~ // ==================== to adapt for the project  =====================================
//~ // in this simple example, the button action increases a counter each time it is
//~ // used. Then it asks to update the diaplay of the table of values.
//~ // HOWEVER, for the project, many other causes should lead to such an update: file
//~ // reading, simulation update, etc... For these reason the call to tree_view_update()
//~ // should be done in the method on_draw of your GUI.

//~ void Scroll::on_button_clicked()
//~ {
  //~ ++count;
  //~ std::cout << "count value is now " << count << std::endl;
    
  //~ // for the project, move this call in a method analog to refresh() in myEvent
  //~ // The goal is to produce a simultaneous indirect call to on_draw()
  //~ tree_view_update(); 
//~ }

//~ // the declaration below should not exist in your gui module; instead you should have a
//~ // local vector declared in the method tree_view_update() and such a vector such be
//~ // updated with the value returned by a call to your simulation module.

//~ namespace
//~ {
  //~ static std::vector<SimData> report(max_tab); // init with zeros
//~ }


