difference(){
    union(){
        translate([0,0,0]){
            cube([70,90,1], center=true);
        };
        translate([32.5,0,1]){
            cube([5,90,3], center=true);
        };
        translate([16.25,0,1]){
            cube([5,90,3], center=true);
        };
        translate([5,0,1]){
            cube([5,90,3], center=true);
        };
        translate([-16.25,0,1]){
            cube([5,90,3], center=true);
        };
        translate([-34.5,0,34.5]){
            cube([1,90,70], center=true);
        };
        translate([0,0,1]){
            cube([35,90,3], center=true);
        };
        translate([26.25,0,1]){
            cube([15,90,3], center=true);
        };
        translate([-26.25,0,1]){
            cube([15,90,3], center=true);
        };
        hull(){
            translate([0,44.5,1]){
                cube([70,1,3], center=true);
            };
            translate([-33.5,44.5,35]){
                cube([3,1,70], center=true);
            };
        };
        hull(){
            translate([0,-44.5,1]){
                cube([70,1,3], center=true);
            };
            translate([-33.5,-44.5,35]){
                cube([3,1,70], center=true);
            };
        };
    };
    translate([18,-36.5,0])
        rotate([0,180,-90])
            linear_extrude(10){
                text("E D S A C", font = "Liberation Mono:style=Bold", center=true);
            };
    translate([-0.5,0,0]){
        cube([6,44,30], center=true);
    };
    translate([-0.5,0,2]){
        cube([20,54,3], center=true);
    };
    translate([-0.5,32,0]){
        cylinder(r=1.6, $fn=24, h=6, center=true);
    };
    translate([-0.5,-32,0]){
        cylinder(r=1.6, $fn=24, h=6, center=true);
    };
    translate([-0.5,32,0]){
        cylinder(r=3.4, $fn=24, h=1.5, center=true);
    };
    translate([-0.5,-32,0]){
        cylinder(r=3.4, $fn=24, h=1.5, center=true);
    };
    translate([-22,-20,0]){
        cube([15,16,30], center=true);
    };
    translate([-27,0,0]){
        cylinder(r=2.8, $fn=24, h=6, center=true);
    };
    translate([-27,10,0]){
        cylinder(r=2.8, $fn=24, h=6, center=true);
    };
    translate([-27,20,0]){
        cylinder(r=2.8, $fn=24, h=6, center=true);
    };
    translate([-17,-2.54,0]){
        cylinder(r=1.2, h=6, center=true, $fn=12);
    };
    translate([-17,2.54,0]){
        cylinder(r=1.2, h=6, center=true, $fn=12);
    };
    translate([-17,7.46,0]){
        cylinder(r=1.2, h=6, center=true, $fn=12);
    };
    translate([-17,12.54,0]){
        cylinder(r=1.2, h=6, center=true, $fn=12);
    };
    translate([-17,17.46,0]){
        cylinder(r=1.2, h=6, center=true, $fn=12);
    };
    translate([-17,22.54,0]){
        cylinder(r=1.2, h=6, center=true, $fn=12);
    };
};