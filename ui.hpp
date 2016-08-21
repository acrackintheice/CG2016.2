#ifndef UI_HPP
#define UI_HPP

#include <gtk/gtk.h>
#include <iostream>
#include <string.h>
#include "transformations.cpp"
#include "point.hpp"
#include "object.hpp"
#include "color.hpp"
#include "world.hpp"
#include "line.hpp"
#include "wireframe.hpp"
#include "coordinates.hpp"
#include "polygon.hpp"

class UI 
{
public:
	UI(int argc, char *argv[], World* world);
	~UI();
	void draw();
	void add_object_from_dialog();
	void show_add_object_dialog();
	void hide_add_object_dialog();
	void add_point_to_polygon();
	void move_window(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
	void remove_object();
	void zoom_in();
	void zoom_out();
	void translate();
	void scale();
	void rotate();
private:
	const gchar* get_current_page_label(GtkNotebook* notebook);
	char* get_text_of_textview(GtkWidget *text_view);
	void set_text_of_textview(GtkWidget *text_view, gchar* text);
	bool input_is_valid();
	void reset_polygon_points();
	void add_name_to_list(const gchar* name);
	void remove_name_from_list(const gchar* name);
	void update_text_view_window();
	Coordinates get_rotation_point();
	Object* get_selected_object();
	std::string get_selected_object_name();
	

	GtkBuilder* _builder;
	// Main window widgets
	GObject* _main_window;
	GObject* _button_add_object;
	GObject* _button_remove_object;
	GObject* _button_up;
	GObject* _button_left;
	GObject* _button_down;
	GObject* _button_right;
	GObject* _button_zoom_in;
	GObject* _button_zoom_out;
	GObject* _button_translate;
	GObject* _text_entry_dx;
	GObject* _text_entry_dy;
	GObject* _button_scale;
	GObject* _text_entry_sx;
	GObject* _text_entry_sy;
	GObject* _dialog_add_object;
	GObject* _canvas;
	GObject* _object_list;
	GObject* _text_view_window;
	GObject* _text_entry_angle;
	GObject* _radio_button_center;
	GObject* _radio_button_origin;
	GObject* _radio_button_arbitrary_point;
	GObject* _text_entry_rotation_point_x;
	GObject* _text_entry_rotation_point_y;
	GObject* _button_rotate;
	// Add object dialog widgets
	GObject* _button_add;
	GObject* _button_cancel;
	GObject* _notebook;
	GObject* _text_entry_object_name;
	GObject* _text_entry_point_x;
	GObject* _text_entry_point_y;
	GObject* _text_entry_line_x1;
	GObject* _text_entry_line_y1;
	GObject* _text_entry_line_x2;
	GObject* _text_entry_line_y2;
	GObject* _text_entry_polygon_x;
	GObject* _text_entry_polygon_y;
	GObject* _button_add_point_to_polygon;
	GObject* _textview_number_of_points;
	GObject* _radio_button_polygon;
	GObject* _radio_button_wireframe;

	// Non-widget attributes
	World* _world;
	std::vector<Coordinates> _polygon_points;

};

#endif // UI_HPP