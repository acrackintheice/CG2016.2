#include "ui.hpp"

using namespace std;

static gboolean draw_object(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	World* world = static_cast<World*>(data);
	Window* window = world->get_window();

	/* Getting the viewport coordinates*/
	double vp_width = (double) (gtk_widget_get_allocated_width  (widget));
	double vp_height = (double) (gtk_widget_get_allocated_height (widget));
	Coordinates viewport_min = Coordinates(10,10);
	Coordinates viewport_max = Coordinates(vp_width-10, vp_height-10);

	/* Getting the window coordinates */
	Coordinates window_min =  Coordinates(-1,-1);//window->get_min();
	Coordinates window_max =  Coordinates(1,1);//window->get_max();
	/* Filling the background */
	cairo_set_source_rgba(cr, 1, 1, 1, 1);
	cairo_paint(cr);
	/* Set the line width */
	cairo_set_line_width(cr,2);
	/* Set the line cap, otherwise points dont show*/
	cairo_set_line_cap  (cr, CAIRO_LINE_CAP_ROUND); 
	/* Drawing objects */
	world->scn_upate();
	world->clip();
	/* Drawing every object*/
	vector<Object*> objects = world->get_objects();
	vector<Object*>::iterator it;
	for(it = objects.begin(); it != objects.end(); it++){
		Object* obj = (*it);
		/* Set the line color */
		Color* color = obj->get_color();
		cairo_set_source_rgba(cr, color->get_r(), color->get_g(), color->get_b(), color->get_a());
        /* Getting the points from the object*/
		vector<Coordinates> points = obj->get_drawing_points();
		vector<Coordinates>::iterator it_points = points.begin();
		/* Flagging that the next point is the first */
		bool first_point = true;
		/* Drawing every point*/
		for(it_points; it_points != points.end(); it_points++){
			Coordinates w_point = *it_points;
			Coordinates vp_point = Transformations::viewport(w_point, window_min, window_max, viewport_min, viewport_max);
			/* If it is the first point we need to move the pen to the canvas */
			if (first_point)
			{
				cairo_move_to(cr, vp_point.get_x(), vp_point.get_y());
				/* Flagging that the next points are not the first anymore*/
				first_point = false;
			}
			/* 
			When it is not the first point we already have the pen on the canvas,  
			so we only need to keep drawing it 
			*/
			cairo_line_to(cr, vp_point.get_x(), vp_point.get_y());
		}
		/* If the object should be filled */
		if(obj->is_filled()){
			/* Setting the filling color */
			Color* bc = obj->get_background_color();
			cairo_set_source_rgba(cr, bc->get_r(), bc->get_g(), bc->get_b(), bc->get_a());
			cairo_stroke_preserve(cr);
			cairo_fill(cr);
		}
		else{
			/* The stroke function actually draws the object */
			cairo_stroke(cr);
		}
	}
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
static void add_point_to_curve_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->add_point_to_curve();
}
static void remove_object_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->remove_object();
}
static void move_up_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->move_window(0,25);
}
static void move_left_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->move_window(-25,0);
}
static void move_down_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->move_window(0,-25);
}
static void move_right_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->move_window(25,0);
}
static void zoom_in_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->zoom_in();
}
static void zoom_out_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->zoom_out();
}
static void translate_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->translate();
}
static void scale_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->scale();
}
static void rotate_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->rotate();
}
static void rotate_window_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->rotate_window();
}
static void resize_callback (GtkWidget *widget, gpointer data){
	static_cast<UI*>(data)->update_text_view_window();
}
/* Member Functions */
UI::UI(int argc, char *argv[], World* world) : _world(world)
{
	/* This intializes something, no idea what*/
	gtk_init (&argc, &argv);
  	/* Constructing a GtkBuilder instance */
	_builder = gtk_builder_new();
	/* Loading the UI from a XML description */
	gtk_builder_add_from_file (_builder, "simple.glade", NULL);
  	/* Main window widgets*/
	_main_window 		  			= gtk_builder_get_object (_builder, "main_window");
	_button_add_object    			= gtk_builder_get_object (_builder, "button_add_object");
	_button_remove_object 			= gtk_builder_get_object (_builder, "button_remove_object");
	_button_up 			  			= gtk_builder_get_object (_builder, "button_up");
	_button_left 		  			= gtk_builder_get_object (_builder, "button_left");
	_button_down 		  			= gtk_builder_get_object (_builder, "button_down");
	_button_right 		  			= gtk_builder_get_object (_builder, "button_right");
	_button_zoom_in 	  			= gtk_builder_get_object (_builder, "button_zoom_in");
	_button_zoom_out 	  			= gtk_builder_get_object (_builder, "button_zoom_out");
	_button_translate	  			= gtk_builder_get_object (_builder, "button_translate");
	_text_entry_dx		  			= gtk_builder_get_object (_builder, "text_entry_dx");
	_text_entry_dy        			= gtk_builder_get_object (_builder, "text_entry_dy");
	_button_scale	  	  			= gtk_builder_get_object (_builder, "button_scale");
	_text_entry_sx		  			= gtk_builder_get_object (_builder, "text_entry_sx");
	_text_entry_sy        			= gtk_builder_get_object (_builder, "text_entry_sy");
	_canvas 			  			= gtk_builder_get_object (_builder, "canvas");
	_object_list		  			= gtk_builder_get_object (_builder, "object_list");
	_text_view_window	  			= gtk_builder_get_object (_builder, "text_view_window");
	_text_entry_angle	  			= gtk_builder_get_object (_builder, "text_entry_angle");
	_radio_button_center   			= gtk_builder_get_object (_builder, "radio_button_center");
	_radio_button_origin   			= gtk_builder_get_object (_builder, "radio_button_origin");
	_radio_button_arbitrary_point 	= gtk_builder_get_object (_builder, "radio_button_arbitrary_point");
	_text_entry_rotation_point_x 	= gtk_builder_get_object (_builder, "text_entry_rotation_point_x");
	_text_entry_rotation_point_y 	= gtk_builder_get_object (_builder, "text_entry_rotation_point_y");
	_button_rotate 					= gtk_builder_get_object (_builder, "button_rotate");
	_button_rotate_window 			= gtk_builder_get_object (_builder, "button_rotate_window");
	_text_entry_angle_window 		= gtk_builder_get_object (_builder, "text_entry_angle_window");
	_background_color_button		= gtk_builder_get_object (_builder, "background_color_button");
	_line_color_button				= gtk_builder_get_object (_builder, "line_color_button");
	/* Add object dialog widgets*/
	_dialog_add_object    				= gtk_builder_get_object (_builder, "dialog_add_object");
	_button_add	  		  				= gtk_builder_get_object (_builder, "button_add");
	_button_cancel		  				= gtk_builder_get_object (_builder, "button_cancel");
	_notebook	  		  				= gtk_builder_get_object (_builder, "notebook");
	_text_entry_object_name				= gtk_builder_get_object (_builder, "text_entry_object_name");
	_text_entry_point_x   				= gtk_builder_get_object (_builder, "text_entry_point_x");
	_text_entry_point_y   				= gtk_builder_get_object (_builder, "text_entry_point_y");
	_text_entry_line_x1	  				= gtk_builder_get_object (_builder, "text_entry_line_x1");
	_text_entry_line_y1   				= gtk_builder_get_object (_builder, "text_entry_line_y1");
	_text_entry_line_x2	  				= gtk_builder_get_object (_builder, "text_entry_line_x2");
	_text_entry_line_y2	  				= gtk_builder_get_object (_builder, "text_entry_line_y2");
	_text_entry_polygon_x 				= gtk_builder_get_object (_builder, "text_entry_polygon_x");
	_text_entry_polygon_y 				= gtk_builder_get_object (_builder, "text_entry_polygon_y");
	_text_entry_curve_x 				= gtk_builder_get_object (_builder, "text_entry_curve_x");
	_text_entry_curve_y 				= gtk_builder_get_object (_builder, "text_entry_curve_y");
	_textview_number_of_points 			= gtk_builder_get_object (_builder, "textview_number_of_points");
	_textview_number_of_points_to_curve	= gtk_builder_get_object (_builder, "textview_number_of_points_to_curve");
	_button_add_point_to_polygon 		= gtk_builder_get_object (_builder, "button_add_point_to_polygon");
	_button_add_point_to_curve			= gtk_builder_get_object (_builder, "button_add_point_to_curve");
	_radio_button_polygon				= gtk_builder_get_object (_builder, "radio_button_polygon");
	_radio_button_wireframe 			= gtk_builder_get_object (_builder, "radio_button_wireframe");
	_radio_button_filled				= gtk_builder_get_object (_builder, "radio_button_filled");
	// Signals
	g_signal_connect (_main_window, 		  "destroy", 		G_CALLBACK (gtk_main_quit), 					NULL);
	g_signal_connect (_main_window,			  "check-resize",  	G_CALLBACK (resize_callback),              		this);
	g_signal_connect (_button_add_object, 	  "clicked", 		G_CALLBACK (show_add_object_dialog_callback), 	this);
	g_signal_connect (_button_remove_object,  "clicked", 		G_CALLBACK (remove_object_callback), 			this);
	g_signal_connect (_button_up, 			  "clicked", 		G_CALLBACK (move_up_callback), 					this);
	g_signal_connect (_button_left, 		  "clicked", 		G_CALLBACK (move_left_callback), 				this);
	g_signal_connect (_button_down, 		  "clicked", 		G_CALLBACK (move_down_callback), 				this);
	g_signal_connect (_button_right, 		  "clicked", 		G_CALLBACK (move_right_callback), 				this);
	g_signal_connect (_button_zoom_in, 		  "clicked", 		G_CALLBACK (zoom_in_callback), 					this);
	g_signal_connect (_button_zoom_out, 	  "clicked", 		G_CALLBACK (zoom_out_callback), 				this);
	g_signal_connect (_button_translate, 	  "clicked", 		G_CALLBACK (translate_callback),			    this);
	g_signal_connect (_button_scale,	 	  "clicked", 		G_CALLBACK (scale_callback),				    this);
	g_signal_connect (_button_rotate,	 	  "clicked", 		G_CALLBACK (rotate_callback),				    this);
	g_signal_connect (_button_rotate_window,  "clicked", 		G_CALLBACK (rotate_window_callback),			this);
	/* Add object dialog widget signals */
	g_signal_connect (_button_add, 	  				"clicked", 		G_CALLBACK (add_object_from_dialog_callback), 	this);
	g_signal_connect (_button_cancel, 				"clicked", 		G_CALLBACK (hide_add_object_dialog_callback),  	this);
	g_signal_connect (_button_add_point_to_polygon, "clicked", 		G_CALLBACK (add_point_to_polygon_callback)	,  	this);
	g_signal_connect (_button_add_point_to_curve, 	"clicked", 		G_CALLBACK (add_point_to_curve_callback)	,  	this);
	/* Adding the test objects to the list */
	vector<Object*> objects = _world->get_objects();
	vector<Object*>::iterator it;
	for(it = objects.begin(); it != objects.end(); it++){
		Object* obj = (*it);
		if(obj->get_name() != "Window")
			add_name_to_list(obj->get_name().c_str());
	}
	/* Draing the world*/
	draw();
	gtk_widget_show ( GTK_WIDGET(_main_window) );
	update_text_view_window();
	/* Entering loop mode*/
	gtk_main ();
}
UI::~UI(){
}
void UI::update_text_view_window(){
	Window* window = _world->get_window();
	int x1 = window->get_min().get_x();
	int y1 = window->get_min().get_y();
	int x2 = window->get_max().get_x();
	int y2 = window->get_max().get_y();

	int vp_width  = gtk_widget_get_allocated_width  (GTK_WIDGET(_canvas));
	int vp_height = gtk_widget_get_allocated_height (GTK_WIDGET(_canvas)); 

	string text = "WINDOW : (" + to_string(x1) + "," + to_string(y1) + ")" + ",(" + to_string(x2) + "," + to_string(y2) + ")"; 
	text = text + "   +-+-+  VP : ("+ to_string(vp_width) + ", " + to_string(vp_height) + " )";
	set_text_of_textview((GtkWidget*)_text_view_window, (char*)text.c_str());
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
}
void UI::draw(){
	g_signal_connect (_canvas, "draw", G_CALLBACK (draw_object), _world);
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
}
void UI::remove_object(){
	string name = get_selected_object_name();
	_world->remove_object(name);
	remove_name_from_list(name.c_str());
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
}
void UI::move_window(double dx, double dy){
	Window* window = _world->get_window();
	window->move(dx,dy);
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
	update_text_view_window();
}
void UI::zoom_in(){
	Window* window = _world->get_window();
	window->scale(0.9, 0.9);
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
	update_text_view_window();
}
void UI::zoom_out(){
	Window* window = _world->get_window();
	window->scale(1.1, 1.1);
	gtk_widget_queue_draw ((GtkWidget*) _canvas);
	update_text_view_window();
}
void UI::scale(){
	double sx = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_sx), NULL);
	double sy = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_sy), NULL);
	Object* obj = get_selected_object();
	if(obj != NULL){
		obj->scale(sx, sy);
		gtk_widget_queue_draw ((GtkWidget*) _canvas);
	}
}
void UI::translate(){
	double dx = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_dx), NULL);
	double dy = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_dy), NULL);
	Object* obj = get_selected_object();
	if(obj != NULL){
		obj->translate(dx, dy);
		gtk_widget_queue_draw ((GtkWidget*) _canvas);
	}
}
void UI::rotate_window(){
	double angle = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_angle_window), NULL);
	Object* obj = _world->get_window();
	if(obj != NULL){
		Coordinates ponto = obj->get_geometric_center();
		obj->rotate(angle, ponto);
		gtk_widget_queue_draw ((GtkWidget*) _canvas);
	}
	update_text_view_window();
}
void UI::rotate(){
	double angle = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_angle), NULL);
	Object* obj = get_selected_object();
	if(obj != NULL){
		Coordinates ponto = get_rotation_point();
		obj->rotate(angle, ponto);
		gtk_widget_queue_draw ((GtkWidget*) _canvas);
	}
}
Coordinates UI::get_rotation_point(){
	if(gtk_toggle_button_get_active ((GtkToggleButton*) _radio_button_origin)){
		return Coordinates(0,0);
	}
	else if(gtk_toggle_button_get_active ((GtkToggleButton*) _radio_button_arbitrary_point)){
		double x = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_rotation_point_x), NULL);
		double y = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_rotation_point_y), NULL);
		return Coordinates(x,y);
	}
	else{
		return get_selected_object()->get_geometric_center();
	}
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
	_polygon_points.push_back(Coordinates(x,y));
	gchar* size_text = (char *)to_string(_polygon_points.size()).c_str();
	set_text_of_textview(GTK_WIDGET(_textview_number_of_points), size_text);
}
void UI::add_point_to_curve(){
	gdouble x = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_curve_x), NULL);
	gdouble y = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_curve_y), NULL);
	_curve_points.push_back(Coordinates(x,y));
	gchar* size_text = (char *)to_string(_curve_points.size()).c_str();
	set_text_of_textview(GTK_WIDGET(_textview_number_of_points_to_curve), size_text);
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
void UI::remove_name_from_list(const gchar* name){
	GtkListBoxRow* list_row = gtk_list_box_get_selected_row ((GtkListBox*) _object_list);
	if((GtkWidget*)list_row != NULL){
		gtk_container_remove ((GtkContainer*) _object_list, (GtkWidget*)list_row);
		gtk_widget_show_all (GTK_WIDGET(_object_list));
	}
}
void UI::add_name_to_list(const gchar* name){
	GtkWidget *label = gtk_label_new(name);
	gtk_list_box_insert ((GtkListBox*)_object_list, label, 1);
	gtk_widget_show_all (GTK_WIDGET(_object_list));
}
void UI::add_object_from_dialog(){
	GtkNotebook* notebook = (GtkNotebook*)_notebook;
	const gchar* page_name = get_current_page_label(notebook);
	const gchar* name = gtk_entry_get_text ((GtkEntry*) _text_entry_object_name);
	GdkRGBA *color_rgba = new GdkRGBA();
	GdkRGBA *background_rgba = new GdkRGBA();
	gtk_color_chooser_get_rgba ( (GtkColorChooser*) _line_color_button, color_rgba);
	gtk_color_chooser_get_rgba ( (GtkColorChooser*) _background_color_button, background_rgba);
	Color* background_color = new Color(background_rgba->red, background_rgba->green, background_rgba->blue, background_rgba->alpha);
	Color* line_color = new Color(color_rgba->red, color_rgba->green, color_rgba->blue, color_rgba->alpha);
	delete color_rgba;
	delete background_rgba;
	if(strcmp(page_name, "Point") == 0){
		gdouble x = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_point_x), NULL);
		gdouble y = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_point_y), NULL);
		if(input_is_valid()){
			Point* p = new Point(Coordinates(x,y), name, line_color);
			_world->add_object(p);
			add_name_to_list(name);
			draw();
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{
				// TODO
		}
	}
	else if(strcmp(page_name, "Line")==0){
		gdouble x1 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_x1), NULL);
		gdouble y1 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_y1), NULL);
		gdouble x2 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_x2), NULL);
		gdouble y2 = g_ascii_strtod(gtk_entry_get_text ((GtkEntry*) _text_entry_line_y2), NULL);
		if(input_is_valid()){
			Line* r = new Line(Coordinates(x1,y1),Coordinates(x2,y2), name, line_color);
			_world->add_object(r);
			add_name_to_list(name);
			draw();
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{
				//TODO
		}
	}
	else if(strcmp(page_name, "Polygon")==0){
		if(input_is_valid()){
			Object* obj;
			if(gtk_toggle_button_get_active ((GtkToggleButton*) _radio_button_wireframe)){
				obj = new Wireframe(_polygon_points, name, line_color);
			}
			else if (gtk_toggle_button_get_active ((GtkToggleButton*) _radio_button_polygon)){
				obj = new Polygon(_polygon_points, name, line_color, background_color, false);
			}
			else if (gtk_toggle_button_get_active ((GtkToggleButton*) _radio_button_filled)){
				obj = new Polygon(_polygon_points, name, line_color, background_color, true);
			}
			_world->add_object(obj);
			add_name_to_list(name);
			reset_polygon_points();
			draw();
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{
					//TODO
		}
	}
	else if(strcmp(page_name, "Curve")==0){
		if(input_is_valid()){
			Object* obj = new Curve(_curve_points, name, line_color);
			_world->add_object(obj);
			add_name_to_list(name);
			reset_curve_points();
			draw();
			gtk_widget_hide (GTK_WIDGET(_dialog_add_object));
		}
		else{
					//TODO
		}
	}
}
void UI::reset_polygon_points(){
	_polygon_points.clear();
	set_text_of_textview(GTK_WIDGET(_textview_number_of_points), (char *)"0");
}
void UI::reset_curve_points(){
	_curve_points.clear();
	set_text_of_textview(GTK_WIDGET(_textview_number_of_points_to_curve), (char *)"0");
}
bool UI::input_is_valid(){
	return true;
}
string UI::get_selected_object_name(){
	string name = "";
	GtkListBoxRow* list_row = gtk_list_box_get_selected_row ((GtkListBox*) _object_list);
	if(list_row != NULL){
		name = gtk_label_get_text (GTK_LABEL(gtk_bin_get_child(GTK_BIN(list_row))));
	}
	return name;
}
Object* UI::get_selected_object(){
	return _world->get_object( get_selected_object_name() );
}
const gchar* UI::get_current_page_label(GtkNotebook* notebook){
	const gchar* label = gtk_label_get_text( (GtkLabel*)gtk_notebook_get_tab_label(notebook, gtk_notebook_get_nth_page (notebook, gtk_notebook_get_current_page(notebook))));
	return label;
}

