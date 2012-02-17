/* 
 * SvLis practical
 * 
 *   Irina Voiculescu, 5 Feb 2010
 * 
 */ 
 
#include "svlis.h" 
 
#include "sv_cols.h" 
#if macintosh 
 #pragma export on 
#endif 
 
#if macintosh 
 #define RES_FILE "::mug.mod" 
 #define RAY_FILE "::raytraced.ppm" 
#else 
 #define RES_FILE "mug.mod" 
 #define RAY_FILE "raytraced.ppm" 
#endif 

static void my_reporter(sv_real progress)
{
    std::cout << "Ray tracing progress: " << progress << "%"<<std::endl;
}

sv_set buildmymodel(sv_point lowCorner, sv_point highCorner) 
{
 
    //Cuboid is slightly smaller than parameters given in function
    sv_point p = lowCorner + highCorner*0.2; 
    sv_point q = highCorner - highCorner*0.2; 

    sv_set a_cuboid = cuboid(p,q);
    a_cuboid = a_cuboid.colour(SV_GREEN); 
 
    sv_surface tex = sv_surface(); 

    sv_set a_sphere = sphere(sv_point(5,5,5),4) ;
    a_sphere = a_sphere.colour(SV_RED);

    sv_set a_line = sv_set(sv_line(sv_point(1,0,0),sv_point(6,6,5)));
    a_line = a_line.colour(SV_BLUE);

    sv_set plane_top = sv_set(sv_plane(sv_point(7,0,0), sv_point(7,5,5), sv_point(7,3,0)));
    plane_top = plane_top.colour(SV_WHEAT);
    
    sv_set cuboid_bottom = cuboid(sv_point(0.5,3,2),sv_point(1.5,9,8));
    cuboid_bottom = cuboid_bottom.colour(SV_RED);
    
    sv_set plane_bottom = sv_set(sv_plane(sv_point(1,0,0), sv_point(1,3,0), sv_point(1,5,5)));
    plane_bottom = plane_bottom.colour(SV_WHEAT);

	sv_set sphere_bottom = sphere(sv_point(1,6,5),3) ;
    sphere_bottom = sphere_bottom.colour(SV_RED);

    sv_set cylinder1 = cylinder(sv_line(sv_point(1,0,0),sv_point(6,6,5)), 3);
    cylinder1 = cylinder1.colour(SV_RED);
    
    sv_set cylinder2 = cylinder(sv_line(sv_point(1,0,0),sv_point(6,6,5)), 2.5);
    cylinder2 = cylinder2.colour(SV_RED);
    
    sv_set torus_top = torus (sv_line(sv_point(1,0,0),sv_point(7,6,5)), 2.5, 0.5);
    torus_top = torus_top.colour(SV_RED);
    
    sv_set torus_handle = torus (sv_line(sv_point(0,0,1),sv_point(4,3,5)), 2, 0.5);
    torus_handle = torus_handle.colour(SV_RED);
    
    sv_set plane_handle = sv_set(sv_plane(sv_point(3,3,5), sv_point(0,3,0), sv_point(4,3,2)));
    plane_handle = plane_handle.colour(SV_WHEAT);
    
    //Experiment with different ways of using the cuboid, sphere, line and plane
    sv_set result;
    
    result = torus_top | (torus_handle - plane_handle) | (((cylinder1 - cylinder2) - plane_top - plane_bottom)) | (cuboid_bottom & sphere_bottom);

    //result= a_cuboid; 
    
    //result = a_sphere & a_cuboid; 
    
    //result = a_cuboid - a_sphere; 

    //result = a_cuboid | a_sphere;

    //result = a_cuboid ^ a_sphere;
    
    //The next one isn't a solid
    //result = a_cuboid ^ a_line;

    //result = a_sphere & a_cuboid - plane;
    
    return result;
}


int main(int argc, char **argv)
{ 
 
    // Initialise svLis 
    glutInit(&argc, argv);//Needed under some configurations of SvLis, but not others
    svlis_init(); 
 
    // Define the corners of a box, then the box 
    sv_point b_lo = SV_OO; 
    sv_point b_hi = sv_point(10,10,10); 
    sv_box mod_box = sv_box(b_lo,b_hi); 
 
    // Construct a model in the region of interest defined by (b_lo, b_hi)
    sv_set mymodel = buildmymodel(b_lo,b_hi);
 
    // Make sure anything that needs to can find attributes 
    // (i.e. colours) where it expects. 
    mymodel = mymodel.percolate(); 
 
    // Build a model with the result and the box 
    sv_model m = sv_model(mymodel,mod_box,sv_model()); 
 
 
    // Always write the file 
    std::ofstream opf(RES_FILE); 
    if(!opf) 
    { 
	svlis_error(argv[0],"can't open output file mug.mod in directory results", SV_WARNING); 
	return(svlis_end(1)); 
    } 
    else 
    {
        // Switch on pretty_print output 
        pretty_print(1); 
	opf << m; 
    }

    bool plot=true;
    if (plot)
    {
        // Display on the graphics screen
        m = m.facet(); 
        plot_m_p_gons(m); 
        // Keep the picture up until user says
        std::cout << SV_EL << SV_EL << "SvLis program "<<argv[0]<<" has finished successfully." << SV_EL << SV_EL; 
    }
    
    bool raytrace = false;
    sv_integer width=200;  //pixels. 800 is good 
    sv_integer height=150; //pixels. 600 is good
    // Raytrace to file "raytraced.ppm" 
    if (raytrace)
    {
        // Rendering parameters set here
        sv_view v;
	v.eye_point(sv_point(23,26,24));
	v.centre(sv_point(0,0,0));
   
	// For the raytracer we need to construct a linked list of light sources
	sv_light_list lightlist;
	sv_light_list lightlist2;

	sv_lightsource light1;
	light1.direction(sv_point(0.1,0.3,-1));
	light1.type(POINT_SOURCE);
	light1.location(sv_point(5, 2, 15));
	light1.angle_power(sv_real(2.0));
	sv_lightsource light2;
	light2.type(POINT_SOURCE);
	light2.location(sv_point(15, 5, 5));
	light2.direction(sv_point(-1,0,0));
	light2.angle_power(sv_real(2.2));

	lightlist2.source = &light2;
	lightlist2.name = "my point light";
	lightlist2.next = NULL;

	lightlist.source = &light1;
	lightlist.name = "my parallel light";
	lightlist.next = &lightlist2;

	sv_picture mypict;
	mypict.resolution(width, height);
	set_ground_colour(1.0, 1.0, 1.0, sqrt(3));//This is white background.  The sqrt(3) is there because the (r=1,b=1,g=1) vector gets normalised
    sv_real progress_interval = 5;
	sv_integer result;
	result = generate_picture(m, v, lightlist, mypict, progress_interval, my_reporter);

        write_image(RAY_FILE, &mypict, "bleh");
    }
    return(svlis_end(0)); 
} 

 
#if macintosh 
 #pragma export off 
#endif 
