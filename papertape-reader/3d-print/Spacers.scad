
//Spacers.scad (c) by Embecosm Ltd.
//
//Spacers.scad is licensed under a
//Creative Commons Attribution-ShareAlike 4.0 International License.
//
//You should have received a copy of the license along with this
//work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

difference(){
    translate([45,0,0])
        cube([120,72,10],center=true);
    translate([45,0,-1])
        cube([120,72,10],center=true);
    translate([60,0,8])
        cube([160,44,10],center=true);
    translate([11.25,29,0])
        cube([12,10,15],center=true);
    translate([11.25,-29,0])
        cube([12,10,15],center=true);
    translate([33.75,-29,0])
        cube([12,10,17],center=true);
    translate([33.75,29,3])
        cube([12,10,16],center=true);
    cylinder(r=2.7, h=12, center=true, $fn=30);
    translate([0,7.62,0])
            cylinder(r=2.7, h=12, center=true, $fn=30);
    translate([0,-7.62,0])
            cylinder(r=2.7, h=12, center=true, $fn=30);
    translate([0,15.24,0])
            cylinder(r=2.7, h=12, center=true, $fn=30);
    translate([0,-15.24,0])
            cylinder(r=2.7, h=12, center=true, $fn=30);
    translate([67.5,0,0]){
        union(){
            translate([0,29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,29,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
    translate([22.5,0,0]){
        union(){
            translate([0,29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,29,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
    union(){
        translate([0,29,0])
                cylinder(r=3.2, h=12, center=true, $fn=30);
        translate([0,-29,0])
                cylinder(r=3.2, h=12, center=true, $fn=30);
        translate([0,29,-8])
                cylinder(r=3.2, h=12, center=true, $fn=30);
        translate([0,-29,-8])
                cylinder(r=3.2, h=12, center=true, $fn=30);
    };
    translate([45,0,0]){
        union(){
            translate([0,29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,29,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
    translate([90,0,0]){
        union(){
            translate([0,29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,0])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,29,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
            translate([0,-29,-8])
                    cylinder(r=3.2, h=12, center=true, $fn=30);
        };
    };
};
