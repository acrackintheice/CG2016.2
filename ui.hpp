#ifndef UI_HPP
#define UI_HPP

#include <gtk/gtk.h>
#include <iostream>
#include <string.h>
#include "transformations.cpp"
#include "ponto.hpp"
#include "objeto.hpp"
#include "cor.hpp"
#include "mundo.hpp"
#include "ponto.hpp"
#include "reta.hpp"
#include "wireframe.hpp"
#include "coordenadas.hpp"

class UI 
{
public:
	UI(int argc, char *argv[], Mundo* mundo);
	~UI();
	void draw();
	void real_draw(Objeto* obj, cairo_t *cr, GtkWidget *widget);
	void add_object_from_dialog();
	void show_add_object_dialog();
	void hide_add_object_dialog();
	void add_point_to_polygon();
	void move_window(double x1_offset, double y1_offset, double x2_offset, double y2_offset);
	void remove_object();
	void zoom_in();
	void zoom_out();
private:
	const gchar* get_current_page_label(GtkNotebook* notebook);
	char* get_text_of_textview(GtkWidget *text_view);
	void set_text_of_textview(GtkWidget *text_view, gchar* text);
	bool input_is_valid();
	void reset_polygon_points();
	void add_name_to_list(const gchar* name);
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
	GObject* _dialog_add_object;
	GObject* _canvas;
	GObject* _object_list;
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


	// Non-widget attributes
	Mundo* _mundo;
	std::vector<Coordenadas*> polygon_points;

};

#endif // UI_HPP