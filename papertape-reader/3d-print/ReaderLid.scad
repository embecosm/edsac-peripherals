
//ReaderLid.scad (c) by Embecosm Ltd.
//
//ReaderLid.scad is licensed under a
//Creative Commons Attribution-ShareAlike 4.0 International License.
//
//You should have received a copy of the license along with this
//work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

        union(){
            difference(){
                //main body
                union(){
                    translate([45,0,-21])
                        cube([120,86,19],center=true);
                };
                //motor hole
                translate([45,20.5,-0.75])
                    cube([13,25,11],center=true);
                //general central cavity
                translate([27.5,0,-9.25])
                    cube([70,58,30],center=true);
                //in tray
                translate([120,0,0])
                    cube([100,58,340],center=true);
                //wheel hole
                translate([45,0,0])
                    cube([25,25,34],center=true);
                //slanty end
                translate([139,0,-38])
                    rotate([0,45,0])
                        cube([100,146,340],center=true);
                //wire holes
                translate([11.25,36,0])
                    cube([12,10,27],center=true);
                translate([11.25,-36,0])
                    cube([12,10,27],center=true);
                translate([33.75,-36,0])
                    cube([12,10,27],center=true);
                translate([33.75,36,1.75])
                    cube([12,10,26],center=true);
                translate([35.75,36,-0.75])
                    cube([16,10,21],center=true);
                //connections to main cavity
                translate([11.25,0,-9.25])
                    cube([12,82,30],center=true);
                translate([33.75,-18,-9.25])
                    cube([12,46,30],center=true);

                //Bolt holes
               
            };
    };
     union(){
                    translate([0,36,-9])
                            cylinder(r=2.7, h=5, center=true, $fn=30);
                    translate([0,-36,-9])
                            cylinder(r=2.7, h=5, center=true, $fn=30);
                };
                translate([45,0,-1]){
                    union(){
                        translate([0,-36,-8])
                                cylinder(r=2.7, h=5, center=true, $fn=30);
                    };
                };
                translate([90,0,-1]){
                    union(){
                        translate([0,36,-8])
                                cylinder(r=2.7, h=5, center=true, $fn=30);
                        translate([0,-36,-8])
                                cylinder(r=2.7, h=5, center=true, $fn=30);
                    };
                };
