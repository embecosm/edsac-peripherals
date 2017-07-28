
//ReaderUpperHalf.scad (c) by Embecosm Ltd.
//
//ReaderUpperHalf.scad is licensed under a
//Creative Commons Attribution-ShareAlike 4.0 International License.
//
//You should have received a copy of the license along with this
//work. If not, see <http://creativecommons.org/licenses/by-sa/4.0/>.

rotate([180,0,0]){
    difference(){
        union(){
            difference(){
                //motor holster shenanigans
                translate([50,25,-4.75])
                    cube([29,25,13.5],center=true);
                translate([45,20.5,-0.75])
                    cube([13,25,11],center=true); 
                translate([33.75,36,0])
                    cube([12,10,14],center=true);
                translate([35.75,36,-2])
                    cube([16,10,10],center=true);
            };
            difference(){
                //main body
                union(){
                    translate([45,0,-2])
                        cube([120,86,19],center=true);
                };
                //motor hole
                translate([45,20.5,-0.75])
                    cube([13,25,11],center=true);
                //general central cavity
                translate([27.5,0,-9.25])
                    cube([70,58,20],center=true);
                //in tray
                translate([120,0,0])
                    cube([100,58,34],center=true);
                //wheel hole
                translate([45,0,0])
                    cube([25,25,34],center=true);
                //slanty end
                translate([139,0,-38])
                    rotate([0,45,0])
                        cube([100,146,34],center=true);
                //wire holes
                translate([11.25,36,0])
                    cube([12,10,17],center=true);
                translate([11.25,-36,0])
                    cube([12,10,17],center=true);
                translate([33.75,-36,0])
                    cube([12,10,17],center=true);
                translate([33.75,36,1.75])
                    cube([12,10,16],center=true);
                translate([35.75,36,-0.75])
                    cube([16,10,11],center=true);
                //connections to main cavity
                translate([11.25,0,-9.25])
                    cube([12,82,20],center=true);
                translate([33.75,-18,-9.25])
                    cube([12,46,20],center=true);
                //LED Holes
                translate([5,0,0])
                    rotate([0,45,0])
                        union(){
                            cube([7,46,7], center=true);
                                cylinder(r=2.7, h=27, center=true, $fn=30);
                                translate([0,7.62,0])
                                        cylinder(r=2.7, h=27, center=true, $fn=30);
                                translate([0,-7.62,0])
                                        cylinder(r=2.7, h=27, center=true, $fn=30);
                                translate([0,15.24,0])
                                        cylinder(r=2.7, h=27, center=true, $fn=30);
                                translate([0,-15.24,0])
                                        cylinder(r=2.7, h=27, center=true, $fn=30);
                            };
                //LDR Holes
                translate([24,0,0])
                    rotate([0,-45,0])
                        union(){
                                cylinder(r=2.3, h=27, center=true, $fn=30);
                                translate([0,7.62,0])
                                        cylinder(r=2.3, h=27, center=true, $fn=30);
                                translate([0,-7.62,0])
                                        cylinder(r=2.3, h=27, center=true, $fn=30);
                                translate([0,15.24,0])
                                        cylinder(r=2.3, h=27, center=true, $fn=30);
                                translate([0,-15.24,0])
                                        cylinder(r=2.3, h=27, center=true, $fn=30);
                            };
                //Bolt holes
                union(){
                    translate([0,36,0])
                            cylinder(r=1.6, h=22, center=true, $fn=30);
                    translate([0,-36,0])
                            cylinder(r=1.6, h=22, center=true, $fn=30);
                    translate([0,36,-8])
                            cylinder(r=3.2, h=12, center=true, $fn=30);
                    translate([0,-36,-8])
                            cylinder(r=3.2, h=12, center=true, $fn=30);
                };
                translate([45,0,0]){
                    union(){
                        translate([0,-36,0])
                                cylinder(r=1.6, h=22, center=true, $fn=30);
                        translate([0,-36,-8])
                                cylinder(r=3.2, h=12, center=true, $fn=30);
                    };
                };
                translate([90,0,0]){
                    union(){
                        translate([0,36,0])
                                cylinder(r=1.6, h=22, center=true, $fn=30);
                        translate([0,-36,0])
                                cylinder(r=1.6, h=22, center=true, $fn=30);
                        translate([0,36,-8])
                                cylinder(r=3.2, h=12, center=true, $fn=30);
                        translate([0,-36,-8])
                                cylinder(r=3.2, h=12, center=true, $fn=30);
                    };
                };
            };
        };
        hull(){
            translate([13,0,7])
                cube([21,45,1],center=true);
            translate([13,0,-3])
                cube([32,57,1],center=true);
        };            
    };
};
