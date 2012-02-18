/* 
 * SvLis practical
 * 
 *   Irina Voiculescu, 5 Feb 2010
 * 
 */ 

#define _USE_MATH_DEFINES
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
    /*
    sv_point p = lowCorner + highCorner*0.2; 
    sv_point q = highCorner - highCorner*0.2; 

    sv_set a_cuboid = cuboid(p,q);
    a_cuboid = a_cuboid.colour(SV_GREEN); 
 
    sv_surface tex = sv_surface(); 

    sv_set a_sphere = sphere(sv_point(5,5,5),4) ;
    a_sphere = a_sphere.colour(SV_RED);

    sv_set a_line = sv_set(sv_line(sv_point(1,0,0),sv_point(8,6,5)));
    a_line = a_line.colour(SV_BLUE);

    sv_set plane_top = sv_set(sv_plane(sv_point(7,0,0), sv_point(7,5,5), sv_point(7,3,0)));
    plane_top = plane_top.colour(SV_WHEAT);
    
    sv_set cuboid_bottom = cuboid(sv_point(0.5,3,2),sv_point(1.5,9,8));
    cuboid_bottom = cuboid_bottom.colour(SV_RED);
    
    sv_set plane_bottom = sv_set(sv_plane(sv_point(1,0,0), sv_point(1,3,0), sv_point(1,5,5)));
    plane_bottom = plane_bottom.colour(SV_WHEAT);

	sv_set sphere_bottom = sphere(sv_point(1,6,5),3) ;
    sphere_bottom = sphere_bottom.colour(SV_RED);

    sv_set cylinder1 = cylinder(sv_line(sv_point(1,0,0),sv_point(8,6,5)), 3);
    cylinder1 = cylinder1.colour(SV_RED);
    
    sv_set cylinder2 = cylinder(sv_line(sv_point(1,0,0),sv_point(8,6,5)), 2.5);
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
	*/
	
	double radius = 3;
	
	// Construct the body:
	sv_set android_body_cylinder = cylinder(sv_line(sv_point(1,0,0),sv_point(8,6,5)), radius);
	android_body_cylinder = android_body_cylinder.colour(SV_GREEN);
	
	sv_set cuboid_bottom = cuboid(sv_point(2.5,3,2),sv_point(3.5,9,8));
    cuboid_bottom = cuboid_bottom.colour(SV_GREEN);
    
    sv_set plane_bottom = sv_set(sv_plane(sv_point(3,0,0), sv_point(3,3,0), sv_point(3,5,5)));
    plane_bottom = plane_bottom.colour(SV_GREEN);

	sv_set plane_top = sv_set(sv_plane(sv_point(8,0,0), sv_point(8,5,5), sv_point(8,3,0)));
    plane_top = plane_top.colour(SV_WHEAT);

	sv_set sphere_bottom = sphere(sv_point(3,6,5),radius);
    sphere_bottom = sphere_bottom.colour(SV_GREEN);
	
	// Construct the head (and neck):
	double neck_height = 0.25;
	sv_set head_sphere = sphere(sv_point(8.25,6,5),radius) ;
    head_sphere = head_sphere.colour(SV_GREEN);
	
	sv_set head_plane = sv_set(sv_plane(sv_point(8.25,0,0), sv_point(8.25,3,0), sv_point(8.25,5,5)));
    head_plane = head_plane.colour(SV_GREEN);

	// Eyes:
	sv_set left_eye = sphere(sv_point(9.5,7,7.5),0.5) ;
    left_eye = left_eye.colour(SV_WHITE);
	
	sv_set right_eye = sphere(sv_point(9.5,5,7.5),0.5) ;
    right_eye = right_eye.colour(SV_WHITE);
	
	// Neck:	
	sv_set neck_cylinder = cylinder(sv_line(sv_point(1,0,0),sv_point(8.125,6,5)),2) ;
    neck_cylinder = head_sphere.colour(SV_WHITE);
	
	sv_set neck_plane_top = sv_set(sv_plane(sv_point(8.25,0,0), sv_point(8.25,5,5), sv_point(8.25,3,0)));
    neck_plane_top = neck_plane_top.colour(SV_WHITE);
	
	sv_set neck_plane_bottom = sv_set(sv_plane(sv_point(8,0,0), sv_point(8,3,0), sv_point(8,5,5)));
    neck_plane_bottom = neck_plane_bottom.colour(SV_WHITE);
	

	
	// Construct the arms:
	double arm_radius = 0.8;
	
	sv_set arm_plane_top = sv_set(sv_plane(sv_point(7,0,0), sv_point(7,5,5), sv_point(7,3,0)));
    arm_plane_top = arm_plane_top.colour(SV_GREEN);
	
	sv_set arm_plane_bottom = sv_set(sv_plane(sv_point(3.5,0,0), sv_point(3.5,3,0), sv_point(3.5,5,5)));
    arm_plane_bottom = arm_plane_bottom.colour(SV_GREEN);

	//Right arm:	
	sv_set right_arm_cylinder = cylinder(sv_line(sv_point(1,0,0),sv_point(0,10,5)), arm_radius);
	right_arm_cylinder = right_arm_cylinder.colour(SV_GREEN);
	
    sv_set right_arm_sphere_top = sphere(sv_point(7,10,5),arm_radius) ;
    right_arm_sphere_top = right_arm_sphere_top.colour(SV_GREEN);

    sv_set right_arm_sphere_bottom = sphere(sv_point(3.5,10,5),arm_radius) ;
    right_arm_sphere_bottom = right_arm_sphere_bottom.colour(SV_GREEN);
	
	// Left arm:	
	sv_set left_arm_cylinder = cylinder(sv_line(sv_point(1,0,0),sv_point(0,2,5)), arm_radius);
	left_arm_cylinder = left_arm_cylinder.colour(SV_GREEN);
	
	sv_set left_arm_sphere_top = sphere(sv_point(7,2,5),arm_radius) ;
    left_arm_sphere_top = left_arm_sphere_top.colour(SV_GREEN);

    sv_set left_arm_sphere_bottom = sphere(sv_point(3.5,2,5),arm_radius) ;
    left_arm_sphere_bottom = left_arm_sphere_bottom.colour(SV_GREEN);
	
	// Construct the legs:
	double leg_radius = 0.8;
	
	sv_set leg_plane_top = sv_set(sv_plane(sv_point(3,0,0), sv_point(3,5,5), sv_point(3,3,0)));
    leg_plane_top = leg_plane_top.colour(SV_GREEN);
	
	sv_set leg_plane_bottom = sv_set(sv_plane(sv_point(0.75,0,0), sv_point(0.75,3,0), sv_point(0.75,5,5)));
    leg_plane_bottom = leg_plane_bottom.colour(SV_GREEN);

	//Right leg:	
	sv_set right_leg_cylinder = cylinder(sv_line(sv_point(1,0,0),sv_point(0,7.5,5)), leg_radius);
	right_leg_cylinder = right_leg_cylinder.colour(SV_GREEN);
	
    sv_set right_leg_sphere_bottom = sphere(sv_point(0.75,7.5,5),leg_radius);
    right_leg_sphere_bottom = right_leg_sphere_bottom.colour(SV_GREEN);
	
	// Left leg:
	sv_set left_leg_cylinder = cylinder(sv_line(sv_point(1,0,0),sv_point(0,4.5,5)), leg_radius);
	left_leg_cylinder = left_leg_cylinder.colour(SV_GREEN);
	
    sv_set left_leg_sphere_bottom = sphere(sv_point(0.75,4.5,5),leg_radius) ;
    left_leg_sphere_bottom = left_leg_sphere_bottom.colour(SV_GREEN);
	
	// Teh result:
    sv_set result;
	result = ((android_body_cylinder - plane_top - plane_bottom) | (cuboid_bottom & sphere_bottom)) 
			| ((head_sphere - head_plane) | left_eye | right_eye | (neck_cylinder - neck_plane_top - neck_plane_bottom))
			| (((right_arm_cylinder | left_arm_cylinder) - arm_plane_top - arm_plane_bottom) | right_arm_sphere_top | right_arm_sphere_bottom | left_arm_sphere_top | left_arm_sphere_bottom)
			| (((right_leg_cylinder | left_leg_cylinder) - leg_plane_top - leg_plane_bottom) | right_leg_sphere_bottom | left_leg_sphere_bottom);
	
	//result = result.spin(sv_line(sv_point(0,0,1),sv_point(6,6,5)), M_PI/2);
	
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
    sv_point b_hi = sv_point(14,12,10); 
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
