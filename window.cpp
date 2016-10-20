#include "window.hpp"

using namespace std;

Window::Window(Coordinates_3d* p1, Coordinates_3d* p2, Coordinates_3d* p3, Coordinates_3d* p4, Coordinates_3d* vup, Coordinates_3d* vpn)
{
    _vup = vup;
    _vpn = vpn;
    _name = "Window";
    _points.push_back(p1);
    _points.push_back(p2);
    _points.push_back(p3);
    _points.push_back(p4);


    _edges.push_back(Edge(p1,p2));
    _edges.push_back(Edge(p2,p3));
    _edges.push_back(Edge(p3,p4));
    _edges.push_back(Edge(p4,p1));

    _color = new Color(255, 0, 0, 1);
    _background_color = new Color(1, 1, 1, 1);
    _filled = false;
}
/* 
The window's transform function is different from the Object's one because  
it also needs to transform the Vup vector
*/
void Window::transform(Matriz4x4 transformation){
    /* Transforming the points */
    vector<Coordinates_3d*>::iterator it;
    for(it = _points.begin(); it != _points.end(); it++){
        double l4[] = {0,0,0,1};
        Coordinates_3d* point = (*it);
        l4[0] = point->get_x();
        l4[1] = point->get_y();
        l4[2] = point->get_z();
        Matriz1x4 point_matrix = Matriz1x4(l4);
        Matriz1x4 transformed_point = point_matrix.multiplicarPor4x4(transformation);
        point->set_x(transformed_point.get(0));
        point->set_y(transformed_point.get(1));
        point->set_z(transformed_point.get(2));
    }
    /* Transforming the vup vector */
    double l4[] = {0,0,0,1};
    Coordinates_3d* point = _vup;
    l4[0] = point->get_x();
    l4[1] = point->get_y();
    l4[2] = point->get_z();
    Matriz1x4 point_matrix = Matriz1x4(l4);
    Matriz1x4 transformed_point = point_matrix.multiplicarPor4x4(transformation);
    point->set_x(transformed_point.get(0));
    point->set_y(transformed_point.get(1));
    point->set_z(transformed_point.get(2));
    /* Transforming the VPN */
    double v[] = {0,0,0,1};
    point = _vpn;
    v[0] = point->get_x();
    v[1] = point->get_y();
    v[2] = point->get_z();
    Matriz1x4 point_matrix_2 = Matriz1x4(v);
    transformed_point = point_matrix_2.multiplicarPor4x4(transformation);
    point->set_x(transformed_point.get(0));
    point->set_y(transformed_point.get(1));
    point->set_z(transformed_point.get(2));
}
void Window::transform2(Matriz4x4 transformation){
    /* Transforming the points */
    vector<Coordinates_3d*>::iterator it;
    for(it = _points.begin(); it != _points.end(); it++){
        Coordinates_3d* point = (*it);
        Matriz4x1 point_matrix = Matriz4x1(point->get_x(), point->get_y(), point->get_z(), 1);
        Matriz4x1 transformed_point = transformation.multiplicar4x1(point_matrix);
        point->set_x(transformed_point.get(0));
        point->set_y(transformed_point.get(1));
        point->set_z(transformed_point.get(2));
    }
    /* Transforming the vup vector */
    Coordinates_3d* point = _vup;
    Matriz4x1 point_matrix = Matriz4x1(point->get_x(), point->get_y(), point->get_z(), 1);
    Matriz4x1 transformed_point = transformation.multiplicar4x1(point_matrix);
    point->set_x(transformed_point.get(0));
    point->set_y(transformed_point.get(1));
    point->set_z(transformed_point.get(2));
    /* Transforming the VPN */
    point = _vpn;
    Matriz4x1 point_matrix_2 = Matriz4x1(point->get_x(), point->get_y(), point->get_z(), 1);
    Matriz4x1 transformed_point_2 = transformation.multiplicar4x1(point_matrix_2);
    point->set_x(transformed_point_2.get(0));
    point->set_y(transformed_point_2.get(1));
    point->set_z(transformed_point_2.get(2));
}
void Window::move(double dx, double dy, double dz){
	translate(dx,dy,dz);
    //Getting the difference of the view-up of the window and 90ª (view-up of the world)
    //double rad = get_vup_angle() - (M_PI / 2);
    /*
    //Naming variables in a character (to use in WolframAlpha):
    center = get_geometric_center();
    a = center.get_x();
    b = center.get_y();
    c = dx;
    d = dy;
    u = rad;

	//Matrices of transformations (1 per line) to move the window:
    ---------------------------
    {{1,0,0},{0,1,0},{-a,-b,1}}*
    {{cos(-u),-sin(-u),0},{sin(-u),cos(-u),0},{0,0,1}}*
    {{1,0,0},{0,1,0},{c,d,1}}*
    {{cos(u),-sin(u),0},{sin(u),cos(u),0},{0,0,1}}*
    {{1,0,0},{0,1,0},{a,b,1}}
	---------------------------
    //Use WolframAlpha to obtain the resultant matrix (and a nice vision of the matrices).
    
    double l1[] = {1,0,0};
    double l2[] = {0,1,0};
    double l3[] = { dx*cos(rad) + dy*sin(rad), dx*-sin(rad) + dy*cos(rad), 1};
    Matriz3x3 resultant(l1,l2,l3);
    transform(resultant);
    */
}
Coordinates_3d* Window::get_p1(){
    return _points[0];
}
Coordinates_3d* Window::get_p2(){
    return _points[1];
}
Coordinates_3d* Window::get_p3(){
    return _points[2];
}
Coordinates_3d* Window::get_p4(){
    return _points[3];
}
Coordinates_3d* Window::get_vup(){
    return _vup;
}
Coordinates_3d* Window::get_vpn(){
    return _vpn;
}
double Window::get_vup_angle(){
	//Getting the window's center
    Coordinates_3d center = get_geometric_center();
    //Getting the vector that indicates the upward direction of the window
    Coordinates_3d window_vup = Coordinates_3d(center.get_x()-_vup->get_x(), -(center.get_y()-_vup->get_y()), 0);
    //Getting the length (magnitude) of the window_vup
    double length = sqrt(pow(window_vup.get_x(),2)+pow(window_vup.get_y(),2));
	//Normalizing the window_vup
    Coordinates_3d normalized_window_vup = Coordinates_3d(window_vup.get_x()/length, window_vup.get_y()/length, 0);
	//Getting the angle of the window in radians
    double radians = acos(normalized_window_vup.get_x()) * ((normalized_window_vup.get_y()<0) ? -1 : 1);
    return radians;
}
