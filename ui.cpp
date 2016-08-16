#include "ui.hpp"
#include <iostream>
#include <string.h>
#include "transformations.cpp"
#include "ddata.hpp"
#include "ponto.hpp"

using namespace std;

/* Callback signal functions */
static gboolean draw_background (GtkWidget *widget, cairo_t *cr, gpointer data){
	Cor* c = static_cast<Cor*>(data);
	cairo_set_source_rgba(cr, c->get_r(), c->get_g(), c->get_b(), c->get_a());
	/* fill in the background color*/
	cairo_paint(cr);
	return FALSE;
}
static gboolean draw_object(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	cout << "PAINTING GUYS " << endl;
	D_Data* d_data = static_cast<D_Data*>(data);
	Objeto* obj = d_data->_obj;
	Window* window = d_data->_window;
	/* Getting the viewport bounds coordinates*/
	Coordenadas* viewport_min = new Coordenadas(0,0);
	Coordenadas* viewport_max = new Coordenadas((double) (gtk_widget_get_allocated_width  (widget)),
											    (double) (gtk_widget_get_allocated_height (widget)));

	Coordenadas* window_min = window->get_min();
	Coordenadas* window_max = window->get_max();
	/* Transforming the void pointer into a object */
	/* Getting the points from the object*/
	vector<Coordenadas*> pontos = obj->get_pontos();
	/* Set the line color */
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	/* Set the line width */
	cairo_set_line_width(cr,3);
	/* Set the line cap, otherwise points dont show*/
	cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND); 
	/*  Starting the drawing process, drawing the first point	*/
	vector<Coordenadas*>::iterator it = pontos.begin();
	Coordenadas* xy = Transformations::viewport(*it, window_min, window_max, viewport_min, viewport_max);
	/* Setting the starting point */
	cairo_move_to(cr, xy->get_x(), xy->get_y());
	/* Drawing the starting point in case there are no others */
	cairo_line_to(cr, xy->get_x(), xy->get_y());
	it++;
	/* Drawing all other points */
	for(it ; it != pontos.end(); it++){
		xy = Transformations::viewport(*it, window_min, window_max, viewport_min, viewport_max);
		cairo_line_to(cr, xy->get_x(), xy->get_y());
	}
	/* The stroke function actually draws the object */
	cairo_stroke(cr);
	return FALSE;
}
static void show_add_object_dialog_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->show_add_object_dialog();
}
static void hide_add_object_dialog_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->hide_add_object_dialog();
}
static void add_object_from_dialog_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->add_object_from_dialog();
}
static void add_point_to_polygon_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->add_point_to_polygon();
}
static void remove_object_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->testing_wd();
}
static void move_up_callback (GtkWidget *widget, gpointer data){
	g_print ("move_up\n");
}
static void move_left_callback (GtkWidget *widget, gpointer data){
	g_print ("move_left\n");
}
static void move_down_callback (GtkWidget *widget, gpointer data){
	g_print ("move_down\n");
}
static void move_right_callback (GtkWidget *widget, gpointer data){
	g_print ("move_right\n");
}
static void zoom_in_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->zoom_in();
}
static void zoom_out_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->zoom_out();
}
/* Member Functions */
UI::UI(int argc, char *argv[], Mundo* mundo){
	_mundo = mundo;
	/* This intializes something, no idea what*/
	gtk_init (&argc, &argv);
  	/* Constructing a GtkBuilder instance */
	_builder = gtk_builder_new();
	/* Loading the UI from a XML description */
	gtk_builder_add_from_file (_builder, "simple.glade", NULL);
  	/* Main window widgets*/
	_main_window 		  = gtk_builder_get_object (_builder, "main_window");
	_button_add_object    = gtk_builder_get_object (_builder, "button_add_object");
	_button_remove_object = gtk_builder_get_object (_builder, "button_remove_object");
	_button_up 			  = gtk_builder_get_object (_builder, "button_up");
	_button_left 		  = gtk_builder_get_object (_builder, "button_left");
	_button_down 		  = gtk_builder_get_object (_builder, "button_down");
	_button_right 		  = gtk_builder_get_object (_builder, "button_right");
	_button_zoom_in 	  = gtk_builder_get_object (_builder, "button_zoom_in");
	_button_zoom_out 	  = gtk_builder_get_object (_builder, "button_zoom_out");
	_canvas 			  = gtk_builder_get_object (_builder, "canvas");
	/* Add object dialog widgets*/
	_dialog_add_object    			= gtk_builder_get_object (_builder, "dialog_add_object");
	_button_add	  		  			= gtk_builder_get_object (_builder, "button_add"); 
	_button_cancel		  			= gtk_builder_get_object (_builder, "button_cancel");
	_notebook	  		  			= gtk_builder_get_object (_builder, "notebook"); 
	_text_entry_point_name			= gtk_builder_get_object (_builder, "text_entry_point_name"); 
	_text_entry_point_x   			= gtk_builder_get_object (_builder, "text_entry_point_x"); 
	_text_entry_point_y   			= gtk_builder_get_object (_builder, "text_entry_point_y"); 
	_text_entry_line_name 			= gtk_builder_get_object (_builder, "text_entry_line_name"); 
	_text_entry_line_x1	  			= gtk_builder_get_object (_builder, "text_entry_line_x1"); 
	_text_entry_line_y1   			= gtk_builder_get_object (_builder, "text_entry_line_y1"); 
	_text_entry_line_x2	  			= gtk_builder_get_object (_builder, "text_entry_line_x2"); 
	_text_entry_line_y2	  			= gtk_builder_get_object (_builder, "text_entry_line_y2");
	_text_entry_polygon_name 		= gtk_builder_get_object (_builder, "text_entry_polygon_name");	
	_text_entry_polygon_x 			= gtk_builder_get_object (_builder, "text_entry_polygon_x");
	_text_entry_polygon_y 			= gtk_builder_get_object (_builder, "text_entry_polygon_y");
	_textview_number_of_points 		= gtk_builder_get_object (_builder, "textview_number_of_points");
	_button_add_point_to_polygon 	= gtk_builder_get_object (_builder, "button_add_point_to_polygon");

	// Signals
	g_signal_connect (_main_window, 		  "destroy", G_CALLBACK (gtk_main_quit), 					NULL);
	g_signal_connect (_button_add_object, 	  "clicked", G_CALLBACK (show_add_object_dialog_callback), 	this);
	g_signal_connect (_button_remove_object,  "clicked", G_CALLBACK (remove_object_callback), 			this);
	g_signal_connect (_button_up, 			  "clicked", G_CALLBACK (move_up_callback), 				this);
	g_signal_connect (_button_left, 		  "clicked", G_CALLBACK (move_left_callback), 				this);
	g_signal_connect (_button_down, 		  "clicked", G_CALLBACK (move_down_callback), 				this);
	g_signal_connect (_button_right, 		  "clicked", G_CALLBACK (move_right_callback), 				this);
	g_signal_connect (_button_zoom_in, 		  "clicked", G_CALLBACK (zoom_in_callback), 				this);
	g_signal_connect (_button_zoom_out, 	  "clicked", G_CALLBACK (zoom_out_callback), 				this);
	/* Add object dialog widget signals */
	g_signal_connect (_button_add, 	  				"clicked", G_CALLBACK (add_object_from_dialog_callback), 	this);
	g_signal_connect (_button_cancel, 				"clicked", G_CALLBACK (hide_add_object_dialog_callback),  	this);
	g_signal_connect (_button_add_point_to_polygon, "clicked", G_CALLBACK (add_point_to_polygon_callback),  	this);
	/* Painting the background white*/
	pintar_fundo(1,1,1,1);
	/* Showing the main window*/
	gtk_widget_show ( GTK_WIDGET(_main_window) );
	/* Entering loop mode*/
	gtk_main ();
}

UI::~UI(){}

void UI::testing_wd(){
}
void UI::zoom_in(){
	Window* window = _mundo->get_window();
	window->zoom_in(30);
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
}

void UI::zoom_out(){
	Window* window = _mundo->get_window();
	window->zoom_out(30);
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
}
void UI::pintar_fundo(double red, double green, double blue, double alpha){
	Cor* c = new Cor(red,green,blue,alpha);
	g_signal_connect (_canvas, "draw", G_CALLBACK (draw_background), c);
}
void UI::draw(Objeto* obj){
	D_Data* data = new D_Data(obj, _mundo->get_window());
	g_signal_connect (_canvas, "draw", G_CALLBACK (draw_object), data);
}
void UI::show_add_object_dialog(){
	gtk_widget_show (GTK_WIDGET(_dialog_add_object));
}
void UI::hide_add_object_dialog(){
	gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
}
void UI::add_point_to_polygon(){
	gdouble x = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_polygon_x), NULL);
	gdouble y = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_polygon_y), NULL);
	polygon_points.push_back(new Coordenadas(x,y));
	gchar* size_text = new gchar[100];
	g_ascii_dtostr (size_text, 100, (gdouble)polygon_points.size());
	set_text_of_textview(GTK_WIDGET(_textview_number_of_points), size_text);
	delete[] size_text;
}
char* UI::get_text_of_textview(GtkWidget *text_view) {
    GtkTextIter start, end;
    GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
    gchar* text;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
    return text;
}
void UI::set_text_of_textview(GtkWidget *text_view, gchar* text) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
    gtk_text_buffer_set_text (buffer, text, strlen(text));
}
void UI::add_object_from_dialog(){
	GtkNotebook* notebook = (GtkNotebook*)_notebook;
	const gchar* page_name = get_current_page_label(notebook);
	if(strcmp(page_name, "Point") == 0){
		const gchar* name = gtk_entry_get_text ((GtkEntry*) _text_entry_point_name);
		gdouble x = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_point_x), NULL);
		gdouble y = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_point_y), NULL);
		if(input_is_valid()){
			Ponto* p = new Ponto(new Coordenadas(x,y), name);
			_mundo->add_object(p);
			draw(p);
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{}
	}
	else if(strcmp(page_name, "Line")==0){
		const gchar* name = gtk_entry_get_text ((GtkEntry*) _text_entry_point_name);
		gdouble x1 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_x1), NULL);
		gdouble y1 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_y1), NULL);
		gdouble x2 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_x2), NULL);
		gdouble y2 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_y2), NULL);
		if(input_is_valid()){
			Reta* r = new Reta(new Coordenadas(x1,y1),new Coordenadas(x2,y2), name);
			_mundo->add_object(r);
			draw(r);
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{}
	}
	else if(strcmp(page_name, "Polygon")==0){
		const gchar* name = gtk_entry_get_text ((GtkEntry*) _text_entry_point_name);
		if(input_is_valid()){
			Wireframe* w = new Wireframe(polygon_points, name);
			_mundo->add_object(w);
			draw(w);
			reset_polygon_points();
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{}
	}
}
void UI::reset_polygon_points(){
	polygon_points.clear();
	set_text_of_textview(GTK_WIDGET(_textview_number_of_points), (char *)"0");
}
bool UI::input_is_valid(){
	return true;
}

const gchar* UI::get_current_page_label(GtkNotebook* notebook){
	const gchar* label = gtk_label_get_text( (GtkLabel*)gtk_notebook_get_tab_label(notebook, gtk_notebook_get_nth_page (notebook, gtk_notebook_get_current_page(notebook))));
	return label;
}

