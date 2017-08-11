
//LDRAligner.scad (c) by Embecosm Ltd.
//
//LDRAligner.scad is licensed under a
//Creative Commons Attribution-ShareAlike 4.0 International License.
//
//You should have received a copy of the license along with this
//work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

difference(){
    cube([9,44.5,1],center=true);
    cylinder(r=1.3, h=4, center=true, $fn=30);
    translate([0,7.62,0])
            cylinder(r=1.3, h=4, center=true, $fn=30);
    translate([0,-7.62,0])
            cylinder(r=1.3, h=4, center=true, $fn=30);
    translate([0,15.24,0])
            cylinder(r=1.3, h=4, center=true, $fn=30);
    translate([0,-15.24,0])
            cylinder(r=1.3, h=4, center=true, $fn=30);
    translate([4,0,0]){
            cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,7.62,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,-7.62,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,15.24,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,-15.24,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
    };
    translate([2,0,0]){
            cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,7.62,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,-7.62,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,15.24,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
        translate([0,-15.24,0])
                cylinder(r=1.3, h=4, center=true, $fn=30);
    };
};
