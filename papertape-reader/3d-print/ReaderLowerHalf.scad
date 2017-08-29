difference(){
    translate([45,0,0])
        cube([120,86,10],center=true);
    translate([45,0,40])
        rotate([90,0,0])
            cylinder(r= 40, h=59,  center=true, $fn = 360);
    translate([60,0,8])
        cube([160,59,10],center=true);
    translate([11.25,36,0])
        cube([12,10,15],center=true);
    translate([11.25,-36,0])
        cube([12,10,15],center=true);
    translate([33.75,36,0])
        cube([12,10,15],center=true);
    translate([33.75,-36,0])
        cube([12,10,15],center=true);
    translate([67.5,0,0]){
        union(){
            translate([0,36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,-36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,36,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-36,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
    translate([22.5,0,0]){
        union(){
            translate([0,36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,-36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,36,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-36,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
    union(){
        translate([0,36,0])
                cylinder(r=1.6, h=12, center=true, $fn=30);
        translate([0,-36,0])
                cylinder(r=1.6, h=12, center=true, $fn=30);
        translate([0,36,-8])
                cylinder(r=3.2, h=12, center=true, $fn=30);
        translate([0,-36,-8])
                cylinder(r=3.2, h=12, center=true, $fn=30);
    };
    translate([45,0,0]){
        union(){
            translate([0,36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,-36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,36,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-36,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
    translate([90,0,0]){
        union(){
            translate([0,36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,-36,0])
                    cylinder(r=1.6, h=12, center=true, $fn=30);
            translate([0,36,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-36,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
};