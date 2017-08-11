
//ReaderUndertray.scad (c) by Embecosm Ltd
//
//ReaderUndertray.scad is licensed under a
//Creative Commons Attribution-ShareAlike 4.0 International License.
//
//You should have received a copy of the license along with this
//work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

difference(){
    union(){
        translate([0,0,3])
            cube([120,86,6],center=true);
        translate([-22.5,0,0]){
            union(){
                translate([0,36,15])
                        cube([10,14,20], center=true);
                translate([0,-36,15])
                        cube([10,14,20], center=true);
            };
        };
        translate([22.5,0,0]){
            union(){
                translate([0,36,15])
                        cube([10,14,20], center=true);
                translate([0,-36,15])
                        cube([10,14,20], center=true);
            };
        };
    };
    translate([-22.5,0,16]){
        union(){
            translate([0,36,0])
                    cylinder(r=1.6, h=20, center=true, $fn=30);
            translate([0,-36,0])
                    cylinder(r=1.6, h=20, center=true, $fn=30);
        };
    };
    translate([22.5,0,16]){
        union(){
            translate([0,36,0])
                    cylinder(r=1.6, h=20, center=true, $fn=30);
            translate([0,-36,0])
                    cylinder(r=1.6, h=20, center=true, $fn=30);
        };
    };
};
