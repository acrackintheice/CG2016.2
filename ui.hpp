#ifndef UI_HPP
#define UI_HPP

#include <gtk/gtk.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include "transformations.cpp"
#include "point.hpp"
#include "object.hpp"
#include "color.hpp"
#include "world.hpp"
#include "line.hpp"
#include "wireframe.hpp"
#include "color.hpp"
#include "bspline.hpp"
#include "curve.hpp"
#include "operations.cpp"

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
	void move_window(double dx, double dy);
	void remove_object();
	void zoom_in();
	void zoom_out();
	void translate();
	void scale();
	void rotate1();
	void update_text_view_window();
	void update_clip_type(bool flag);
	World* world();
	bool clip_flag();
    void update_projection_type(bool flag);
    bool projection_flag();
private:
	const gchar* current_page_label(GtkNotebook* notebook);
	void set_text_of_textview(GtkWidget *text_view, gchar* text);
	bool input_is_valid();
	void reset_polygon_points();
	void add_name_to_list(const gchar* name);
	void remove_name_from_list(const gchar* name);
	std::vector<Coordinates*> string_to_points(string x);
	Object* selected_object();
	std::string selected_object_name();
	std::vector<Edge> edges_from_points(std::vector<Coordinates*> points);
	std::vector<Edge> string_to_edges(std::vector<Coordinates*> points, std::string x);

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
	GObject* _text_entry_dz;
	GObject* _button_scale;
	GObject* _text_entry_sx;
	GObject* _text_entry_sy;
    GObject* _text_entry_sz;
	GObject* _dialog_add_object;
	GObject* _canvas;
	GObject* _object_list;
	GObject* _text_view_window;
	GObject*  _line_color_button;
	GObject* _background_color_button;
	GObject* _radio_button_cohen_sutherland;
	GObject* _radio_button_liang_barsky;
	GObject* _radio_button_perspective;
	GObject* _radio_button_parallel;
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
	GObject* _radio_button_filled;
	GObject* _text_entry_curve;
	GObject* _radio_button_bezier;
	GObject* _radio_button_bspline;
	GObject* _text_entry_wireframe_edges;
	GObject* _text_entry_wireframe_points;
	GObject* _radio_button_any_axis;
	GObject* _radio_button_x_axis;
	GObject* _radio_button_y_axis;
	GObject* _radio_button_z_axis;
	GObject* _text_entry_rotation_point_x1;
	GObject* _text_entry_rotation_point_x2;
	GObject* _text_entry_rotation_point_y1;
	GObject* _text_entry_rotation_point_y2;
	GObject* _text_entry_rotation_point_z1;
	GObject* _text_entry_rotation_point_z2;
	GObject* _button_rotate1;
	GObject* _text_entry_angle1;

	// Non-widget attributes
	World* _world;
	std::vector<Coordinates*> _polygon_points;
	bool _clip_flag;
    bool _projection_flag;

};

#endif // UI_HPP