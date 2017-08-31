difference(){
    cube([140,80,10], center=true);
    translate([5,24,0])
        cube([30,10,12], center=true);
    translate([60,30,0])
        cylinder(h=30, r=2, $fn=36, center=true);
    translate([-60,30,0])
        cylinder(h=30, r=2, $fn=36, center=true);
    translate([60,-30,0])
        cylinder(h=30, r=2, $fn=36, center=true);
    translate([-60,-30,0])
        cylinder(h=30, r=2, $fn=36, center=true);
    translate([60,30,15])
        cylinder(h=30, r=3.4, $fn=36, center=true);
    translate([-60,30,15])
        cylinder(h=30, r=3.4, $fn=36, center=true);
    translate([60,-30,15])
        cylinder(h=30, r=3.4, $fn=36, center=true);
    translate([-60,-30,15])
        cylinder(h=30, r=3.4, $fn=36, center=true);
};