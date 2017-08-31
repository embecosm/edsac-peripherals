difference(){
     union(){
        cube([140,80,60], center=true);
        translate([0,55,-25])
            cube([140,40,10], center=true);
    };
    translate([60,42,-29.5])
        rotate([0,180,0])
            linear_extrude(10){
                text("E D S A C", size = 16, font = "Liberation Mono:style=Bold", center=true);
            };
    cube([108,60,80], center=true);
    translate([0,0,5])
        cube([120,40,60], center=true);
    translate([60,30,20])
        cylinder(h=30, r=1.6, $fn=36, center=true);
    translate([-60,30,20])
        cylinder(h=30, r=1.6, $fn=36, center=true);
    translate([60,-30,20])
        cylinder(h=30, r=1.6, $fn=36, center=true);
    translate([-60,-30,20])
        cylinder(h=30, r=1.6, $fn=36, center=true);
};
difference(){
    translate([0,0,-25])
        rotate([0,90,0])
            cylinder(h=130, r=7, $fn=36, center=true);
    cube([108,60,80], center=true);
    translate([0,0,-40])
        cube([150,150,20], center=true);
};