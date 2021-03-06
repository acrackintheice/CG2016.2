#include "ui.hpp"
#include "bezier_curve.hpp"
#include "bezier_surface.hpp"
#include "spline_surface.hpp"

using namespace std;

static gboolean draw_world(GtkWidget *widget, cairo_t *cr, gpointer data) {
    UI *ui = static_cast<UI *>(data);
    World *world = ui->world();
    bool clip_flag = ui->clip_flag();
    bool projection_flag = ui->projection_flag();
    /* Getting the viewport and window coordinates*/
    double vp_width = (double) (gtk_widget_get_allocated_width(widget));
    double vp_height = (double) (gtk_widget_get_allocated_height(widget));
    Coordinates vp_min = Coordinates(10, 10, 0);
    Coordinates vp_max = Coordinates(vp_width - 10, vp_height - 10, 0);
    Coordinates win_min = Coordinates(-1, -1, 0);
    Coordinates win_max = Coordinates(1, 1, 0);
    /* Filling the background, setting line width and cap */
    cairo_set_source_rgba(cr, 1, 1, 1, 1);
    cairo_paint(cr);
    cairo_set_line_width(cr, 1);
    cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
    /* Projecting */
    world->project(projection_flag);
    /* Drawing */
    vector<Object *> objects = world->objects();
    for (vector<Object *>::iterator it = objects.begin(); it != objects.end(); it++) {
        Object *obj = (*it);
        /* Setting the line color */
        Color *color = obj->color();
        cairo_set_source_rgba(cr, color->r(), color->g(), color->b(), color->a());
        obj->clip_and_draw(cr, win_min, win_max, vp_min, vp_max, clip_flag);
    }
    return FALSE;
}

static void show_add_object_dialog_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->show_add_object_dialog();
}

static void hide_add_object_dialog_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->hide_add_object_dialog();
}

static void add_object_from_dialog_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->add_object_from_dialog();
}

static void remove_object_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->remove_object();
}

static void move_up_callback(GtkWidget *widget, gpointer data) {
    UI *ui = static_cast<UI *>(data);
    ui->move_window(0, 1);
}

static void move_left_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->move_window(-1, 0);
}

static void move_down_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->move_window(0, -1);
}

static void move_right_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->move_window(1, 0);
}

static void zoom_in_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->zoom_in();
}

static void zoom_out_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->zoom_out();
}

static void translate_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->translate();
}

static void scale_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->scale();
}

static void rotate1_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->rotate1();
}

static void resize_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->update_text_view_window();
}

static void cohen_sutherland_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->update_clip_type(true);
}

static void liang_barsky_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->update_clip_type(false);
}

static void perspective_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->update_projection_type(true);
}

static void parallel_callback(GtkWidget *widget, gpointer data) {
    static_cast<UI *>(data)->update_projection_type(false);
}

/* Member Functions */
UI::UI(int argc, char *argv[], World *world) : _world(world) {
    /* This initializes something, no idea what*/
    gtk_init(&argc, &argv);
    /* Constructing a GtkBuilder instance */
    _builder = gtk_builder_new();
    /* Loading the UI from a XML description */
    gtk_builder_add_from_file(_builder, "simple.glade", NULL);
    /* Main window widgets*/
    _main_window = gtk_builder_get_object(_builder, "main_window");
    _button_add_object = gtk_builder_get_object(_builder, "button_add_object");
    _button_remove_object = gtk_builder_get_object(_builder, "button_remove_object");
    _button_up = gtk_builder_get_object(_builder, "button_up");
    _button_left = gtk_builder_get_object(_builder, "button_left");
    _button_down = gtk_builder_get_object(_builder, "button_down");
    _button_right = gtk_builder_get_object(_builder, "button_right");
    _button_zoom_in = gtk_builder_get_object(_builder, "button_zoom_in");
    _button_zoom_out = gtk_builder_get_object(_builder, "button_zoom_out");
    _button_translate = gtk_builder_get_object(_builder, "button_translate");
    _text_entry_dx = gtk_builder_get_object(_builder, "text_entry_dx");
    _text_entry_dy = gtk_builder_get_object(_builder, "text_entry_dy");
    _text_entry_dz = gtk_builder_get_object(_builder, "text_entry_dz");
    _button_scale = gtk_builder_get_object(_builder, "button_scale");
    _text_entry_sx = gtk_builder_get_object(_builder, "text_entry_sx");
    _text_entry_sy = gtk_builder_get_object(_builder, "text_entry_sy");
    _text_entry_sz = gtk_builder_get_object(_builder, "text_entry_sz");
    _canvas = gtk_builder_get_object(_builder, "canvas");
    _object_list = gtk_builder_get_object(_builder, "object_list");
    _text_view_window = gtk_builder_get_object(_builder, "text_view_window");
    _background_color_button = gtk_builder_get_object(_builder, "background_color_button");
    _line_color_button = gtk_builder_get_object(_builder, "line_color_button");
    _radio_button_cohen_sutherland = gtk_builder_get_object(_builder, "radio_button_cohen_sutherland");
    _radio_button_liang_barsky = gtk_builder_get_object(_builder, "radio_button_liang_barsky");
    _radio_button_perspective = gtk_builder_get_object(_builder, "radio_button_perspective");
    _radio_button_parallel = gtk_builder_get_object(_builder, "radio_button_parallel");
    _radio_button_any_axis = gtk_builder_get_object(_builder, "radio_button_any_axis");
    _radio_button_x_axis = gtk_builder_get_object(_builder, "radio_button_x_axis");
    _radio_button_y_axis = gtk_builder_get_object(_builder, "radio_button_y_axis");
    _radio_button_z_axis = gtk_builder_get_object(_builder, "radio_button_z_axis");
    _text_entry_rotation_point_x1 = gtk_builder_get_object(_builder, "text_entry_rotation_point_x1");
    _text_entry_rotation_point_x2 = gtk_builder_get_object(_builder, "text_entry_rotation_point_x2");
    _text_entry_rotation_point_y1 = gtk_builder_get_object(_builder, "text_entry_rotation_point_y1");
    _text_entry_rotation_point_y2 = gtk_builder_get_object(_builder, "text_entry_rotation_point_y2");
    _text_entry_rotation_point_z1 = gtk_builder_get_object(_builder, "text_entry_rotation_point_z1");
    _text_entry_rotation_point_z2 = gtk_builder_get_object(_builder, "text_entry_rotation_point_z2");
    _button_rotate1 = gtk_builder_get_object(_builder, "button_rotate1");
    _text_entry_angle1 = gtk_builder_get_object(_builder, "text_entry_angle1");
    /* Add object dialog widgets*/
    _dialog_add_object = gtk_builder_get_object(_builder, "dialog_add_object");
    _button_add = gtk_builder_get_object(_builder, "button_add");
    _button_cancel = gtk_builder_get_object(_builder, "button_cancel");
    _notebook = gtk_builder_get_object(_builder, "notebook");
    _text_entry_object_name = gtk_builder_get_object(_builder, "text_entry_object_name");
    _radio_button_bezier = gtk_builder_get_object(_builder, "radio_button_bezier");
    _text_entry_curve = gtk_builder_get_object(_builder, "text_entry_curve");
    _text_entry_wireframe_points = gtk_builder_get_object(_builder, "text_entry_wireframe_points");
    _text_entry_wireframe_edges = gtk_builder_get_object(_builder, "text_entry_wireframe_edges");
    _radio_button_surface_bezier = gtk_builder_get_object(_builder, "radio_button_surface_bezier");
    _text_entry_surface = gtk_builder_get_object(_builder, "text_entry_surface");
    _text_entry_movement = gtk_builder_get_object(_builder, "text_entry_movement");
    _radio_button_surface_blending = gtk_builder_get_object(_builder, "radio_button_surface_blending");
    // Signals
    g_signal_connect (_main_window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect (_main_window, "check-resize", G_CALLBACK(resize_callback), this);
    g_signal_connect (_button_add_object, "clicked", G_CALLBACK(show_add_object_dialog_callback), this);
    g_signal_connect (_button_remove_object, "clicked", G_CALLBACK(remove_object_callback), this);
    g_signal_connect (_button_up, "clicked", G_CALLBACK(move_up_callback), this);
    g_signal_connect (_button_left, "clicked", G_CALLBACK(move_left_callback), this);
    g_signal_connect (_button_down, "clicked", G_CALLBACK(move_down_callback), this);
    g_signal_connect (_button_right, "clicked", G_CALLBACK(move_right_callback), this);
    g_signal_connect (_button_zoom_in, "clicked", G_CALLBACK(zoom_in_callback), this);
    g_signal_connect (_button_zoom_out, "clicked", G_CALLBACK(zoom_out_callback), this);
    g_signal_connect (_button_translate, "clicked", G_CALLBACK(translate_callback), this);
    g_signal_connect (_button_scale, "clicked", G_CALLBACK(scale_callback), this);
    g_signal_connect (_button_rotate1, "clicked", G_CALLBACK(rotate1_callback), this);
    g_signal_connect (_radio_button_cohen_sutherland, "toggled", G_CALLBACK(cohen_sutherland_callback), this);
    g_signal_connect (_radio_button_liang_barsky, "toggled", G_CALLBACK(liang_barsky_callback), this);
    g_signal_connect (_radio_button_perspective, "toggled", G_CALLBACK(perspective_callback), this);
    g_signal_connect (_radio_button_parallel, "toggled", G_CALLBACK(parallel_callback), this);
    /* Add object dialog widget signals */
    g_signal_connect (_button_add, "clicked", G_CALLBACK(add_object_from_dialog_callback), this);
    g_signal_connect (_button_cancel, "clicked", G_CALLBACK(hide_add_object_dialog_callback), this);
    /* Adding the test objects to the list */
    vector<Object *> objects = _world->objects();
    vector<Object *>::iterator it;
    for (it = objects.begin(); it != objects.end(); it++) {
        Object *obj = (*it);
        add_name_to_list(obj->name().c_str());
    }
    update_clip_type(true);
    update_projection_type(true);
    /* Drawing the world*/
    draw();
    gtk_widget_show(GTK_WIDGET(_main_window));
    update_text_view_window();
    /* Entering loop mode*/
    gtk_main();
}

UI::~UI() {
    delete _world;
}

World *UI::world() {
    return _world;
}

bool UI::clip_flag() {
    return _clip_flag;
}

void UI::update_clip_type(bool flag) {
    _clip_flag = flag;
    gtk_widget_queue_draw((GtkWidget *) _canvas);
}

bool UI::projection_flag() {
    return _projection_flag;
}

void UI::update_projection_type(bool flag) {
    _projection_flag = flag;
    gtk_widget_queue_draw((GtkWidget *) _canvas);
}

void UI::update_text_view_window() {
    Window *window = _world->window();
    double x1 = window->min().x();
    double y1 = window->min().y();
    double x2 = window->max().x();
    double y2 = window->max().y();

    int vp_width = gtk_widget_get_allocated_width(GTK_WIDGET(_canvas));
    int vp_height = gtk_widget_get_allocated_height(GTK_WIDGET(_canvas));

    string text =
            "WINDOW : (" + to_string(x1) + "," + to_string(y1) + ")" + ",(" + to_string(x2) + "," + to_string(y2) + ")";
    text = text + "   +-+-+  VP : (" + to_string(vp_width) + ", " + to_string(vp_height) + " )";
    set_text_of_textview((GtkWidget *) _text_view_window, (char *) text.c_str());
    gtk_widget_queue_draw((GtkWidget *) _canvas);
}

void UI::draw() {
    g_signal_connect (_canvas, "draw", G_CALLBACK(draw_world), this);
    gtk_widget_queue_draw((GtkWidget *) _canvas);
}

void UI::remove_object() {
    string name = selected_object_name();
    _world->remove_object(name);
    remove_name_from_list(name.c_str());
    gtk_widget_queue_draw((GtkWidget *) _canvas);
}

void UI::move_window(double dx, double dy) {
    Window *window = _world->window();
    double d = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_movement), NULL);
    window->move(dx*d, dy*d, 0);
    gtk_widget_queue_draw((GtkWidget *) _canvas);
    update_text_view_window();
}

void UI::zoom_in() {
    Window *window = _world->window();
    window->scale(0.9, 0.9, 0.9);
    gtk_widget_queue_draw((GtkWidget *) _canvas);
    update_text_view_window();
}

void UI::zoom_out() {
    Window *window = _world->window();
    window->scale(1.1, 1.1, 1.1);
    gtk_widget_queue_draw((GtkWidget *) _canvas);
    update_text_view_window();
}

void UI::scale() {
    double sx = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_sx), NULL);
    double sy = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_sy), NULL);
    double sz = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_sz), NULL);
    Object *obj = selected_object();
    if (obj != NULL) {
        obj->scale(sx, sy, sz);
        gtk_widget_queue_draw((GtkWidget *) _canvas);
    }
    update_text_view_window();
}

void UI::translate() {
    double dx = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_dx), NULL);
    double dy = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_dy), NULL);
    double dz = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_dz), NULL);
    Object *obj = selected_object();
    if (obj != NULL) {
        obj->translate(dx, dy, dz);
        gtk_widget_queue_draw((GtkWidget *) _canvas);
    }
    update_text_view_window();
}

void UI::rotate1() {
    double angle = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_angle1), NULL);
    Object *obj = selected_object();
    if (obj != NULL) {
        if (gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_x_axis)) {
            obj->rotate_x(angle);
        } else if (gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_y_axis)) {
            obj->rotate_y(angle);
        } else if (gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_z_axis)) {
            obj->rotate_z(angle);
        } else if (gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_any_axis)) {
            double x1 = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_rotation_point_x1), NULL);
            double y1 = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_rotation_point_y1), NULL);
            double z1 = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_rotation_point_z1), NULL);
            Coordinates p1 = Coordinates(x1, y1, z1);
            double x2 = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_rotation_point_x2), NULL);
            double y2 = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_rotation_point_y2), NULL);
            double z2 = g_ascii_strtod(gtk_entry_get_text((GtkEntry *) _text_entry_rotation_point_z2), NULL);
            Coordinates p2 = Coordinates(x2, y2, z2);
            obj->rotate(angle, p1, p2);
        }
        gtk_widget_queue_draw((GtkWidget *) _canvas);
    }
    update_text_view_window();
}

void UI::show_add_object_dialog() {
    gtk_widget_show(GTK_WIDGET(_dialog_add_object));
}

void UI::hide_add_object_dialog() {
    gtk_widget_hide(GTK_WIDGET(_dialog_add_object));
}

void UI::set_text_of_textview(GtkWidget *text_view, gchar *text) {
    GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *) text_view);
    gtk_text_buffer_set_text(buffer, text, strlen(text));
}

void UI::remove_name_from_list(const gchar *name) {
    GtkListBoxRow *list_row = gtk_list_box_get_selected_row((GtkListBox *) _object_list);
    if ((GtkWidget *) list_row != NULL) {
        gtk_container_remove((GtkContainer *) _object_list, (GtkWidget *) list_row);
        gtk_widget_show_all(GTK_WIDGET(_object_list));
    }
}

void UI::add_name_to_list(const gchar *name) {
    GtkWidget *label = gtk_label_new(name);
    gtk_list_box_insert((GtkListBox *) _object_list, label, 1);
    gtk_widget_show_all(GTK_WIDGET(_object_list));
}

void UI::add_object_from_dialog() {
    GtkNotebook *notebook = (GtkNotebook *) _notebook;
    const gchar *page_name = current_page_label(notebook);
    const gchar *name = gtk_entry_get_text((GtkEntry *) _text_entry_object_name);
    GdkRGBA *color_rgba = new GdkRGBA(); /* had to create this because of gtk*/
    GdkRGBA *background_rgba = new GdkRGBA(); /* this too */
    gtk_color_chooser_get_rgba((GtkColorChooser *) _line_color_button, color_rgba);
    gtk_color_chooser_get_rgba((GtkColorChooser *) _background_color_button, background_rgba);
    Color *background_color = new Color(background_rgba->red, background_rgba->green, background_rgba->blue,
                                        background_rgba->alpha);
    Color *line_color = new Color(color_rgba->red, color_rgba->green, color_rgba->blue, color_rgba->alpha);
    delete color_rgba; /* Deleting these things we had to create*/
    delete background_rgba;  /* deleting this too*/
    if (strcmp(page_name, "Wireframe 3d") == 0) {
        if (input_is_valid()) {
            Object *obj;
            string points(gtk_entry_get_text((GtkEntry *) _text_entry_wireframe_points));
            vector<Coordinates *> wireframe_points = string_to_points(points);
            string edges(gtk_entry_get_text((GtkEntry *) _text_entry_wireframe_edges));
            vector<Edge> wireframe_edges = string_to_edges(wireframe_points, edges);
            obj = new Wireframe(wireframe_points, wireframe_edges, name, line_color, new Color(1, 1, 1, 1), false);
            _world->add_object(obj);
            add_name_to_list(name);
            draw();
            gtk_widget_hide(GTK_WIDGET(_dialog_add_object));
        }
    } else if (strcmp(page_name, "Curve") == 0) {
        if (input_is_valid()) {
            Object *obj;
            string points(gtk_entry_get_text((GtkEntry *) _text_entry_curve));
            vector<Coordinates *> curve_points = string_to_points(points);
            if (gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_bezier)) {
                obj = new Bezier_Curve(curve_points, name, line_color);
            } else {
                obj = new Spline_Curve(curve_points, name, line_color);
            }
            _world->add_object(obj);
            add_name_to_list(name);
            draw();
            gtk_widget_hide(GTK_WIDGET(_dialog_add_object));
        } else {
            //TODO - Showing a message if the input is invalid
        }
    } else if (strcmp(page_name, "Surface") == 0) {
        if (input_is_valid()) {
            Object *obj;
            string points(gtk_entry_get_text((GtkEntry *) _text_entry_surface));
            vector<Coordinates *> curve_points = string_to_points(points);
            bool blending = (bool)gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_surface_blending);
            if (gtk_toggle_button_get_active((GtkToggleButton *) _radio_button_surface_bezier)) {
                obj = new Bezier_Surface(curve_points, name, line_color, blending);
            } else {
                obj = new Spline_Surface(curve_points, name, line_color, blending);
            }
            _world->add_object(obj);
            add_name_to_list(name);
            draw();
            gtk_widget_hide(GTK_WIDGET(_dialog_add_object));
        } else {
            //TODO - Showing a message if the input is invalid
        }
    }
}

vector<Edge> UI::string_to_edges(vector<Coordinates *> points, string x) {
    vector<Edge> edges;
    Operations::remove_char_from_string(x, (char *) " ");
    vector<string> splitted = Operations::split(x, '#');
    vector<string>::iterator it;
    for (it = splitted.begin(); it != splitted.end(); it++) {
        string edge_string = *it;
        Operations::remove_char_from_string(edge_string, (char *) "()");
        vector<string> string_points = Operations::split(edge_string, ',');
        double p1_index = atof(string_points[0].c_str());
        double p2_index = atof(string_points[1].c_str());
        Edge e = Edge(points[p1_index], points[p2_index]);
        edges.push_back(e);
    }
    return edges;
}

vector<Coordinates *> UI::string_to_points(string s) {
    vector<Coordinates *> points;
    Operations::remove_char_from_string(s, (char *) " ");
    vector<string> split = Operations::split(s, '#');
    vector<string>::iterator it;
    for (it = split.begin(); it != split.end(); it++) {
        string coordinates_string = *it;
        /* coordinates_string = '(1,2)' */
        Operations::remove_char_from_string(coordinates_string, (char *) "()");
        /* coordinates_string = '1,2' */
        vector<string> string_points = Operations::split(coordinates_string, ',');
        /* string_points = ['1', '2', '3'] */
        double x = atof(string_points[0].c_str());
        double y = atof(string_points[1].c_str());
        double z = atof(string_points[2].c_str());
        Coordinates *c = new Coordinates(x, y, z);
        points.push_back(c);
    }
    return points;
}

bool UI::input_is_valid() {
    return true;
}

string UI::selected_object_name() {
    string name = "";
    GtkListBoxRow *list_row = gtk_list_box_get_selected_row((GtkListBox *) _object_list);
    if (list_row != NULL) {
        name = gtk_label_get_text(GTK_LABEL(gtk_bin_get_child(GTK_BIN(list_row))));
    }
    return name;
}

Object *UI::selected_object() {
    return _world->get_object(selected_object_name());
}

const gchar *UI::current_page_label(GtkNotebook *notebook) {
    const gchar *label = gtk_label_get_text((GtkLabel *) gtk_notebook_get_tab_label(notebook,
                                                                                    gtk_notebook_get_nth_page(notebook,
                                                                                                              gtk_notebook_get_current_page(
                                                                                                                      notebook))));
    return label;
}

