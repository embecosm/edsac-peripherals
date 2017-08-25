difference(){
    translate([0,0,0])
        cube([12,74,3], center=true);
    translate([1,0,0])
        cube([6,44,30], center=true);
    translate([-0.5,32,0])
        cylinder(r=1.6, $fn=24, h=6, center=true);
    translate([-0.5,-32,0])
        cylinder(r=1.6, $fn=24, h=6, center=true);
};