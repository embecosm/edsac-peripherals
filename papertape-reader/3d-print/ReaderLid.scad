
//ReaderLid.scad (c) by Embecosm Ltd.
//
//ReaderLid.scad is licensed under a
//Creative Commons Attribution-ShareAlike 4.0 International License.
//
//You should have received a copy of the license along with this
//work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

difference(){
    union(){
        cube([120,86,6], center=true);
        translate([0,-36,3])
            cylinder(r=2.7, h=10, center=true, $fn=36);
        translate([45,-36,3])
            cylinder(r=2.7, h=10, center=true, $fn=36);
        translate([-45,-36,3])
            cylinder(r=2.7, h=10, center=true, $fn=36);
        translate([45,36,3])
            cylinder(r=2.7, h=10, center=true, $fn=36);
        translate([-45,36,3])
            cylinder(r=2.7, h=10, center=true, $fn=36);
    };
    translate([148,0,0])
        cube([200,100,10], center=true);
    translate([-18,0,2])
        cube([70,58,6], center=true);
    translate([59,0,2])
        cube([70,58,10], center=true);
    translate([0,-20,0])
        cylinder(r=3.7, h=10, center=true, $fn=36);
    translate([0,-7,0])
        cylinder(r=1.0, h=10, center=true, $fn=36);
    translate([0,-12,0])
        cylinder(r=1.0, h=10, center=true, $fn=36);
};
