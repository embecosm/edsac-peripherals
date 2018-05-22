// Microphone
MIC_D = 4.1;
MIC_H = 2.9;

// GAP & EPS
GAP = 0.4;
EPS = 0.1;

// Holder
HOLD_D = 4 * MIC_D + 4 * GAP;
HOLD_H = 2*MIC_H + 2 * GAP;

// Grub screw & nut
M3_SHANK_R = 3.0 / 2 + GAP;
M3_HEAD_R   = 5.5 / 2 + GAP;
SHANK_R  = M3_SHANK_R;
HEAD_R   = M3_HEAD_R;
HEAD_H   = 3.5;
NUT_H    = 2.5;
LENGTH   = HOLD_D / 2 + 10;

// Wire
WIRE_L = 100;
WIRE_D = 2;

module microphone () {
    cylinder(MIC_H + EPS, d = MIC_D + 2 * GAP, d = MIC_D + 2 * GAP, $fn = 50);
}

module grub () {
    union () {
        translate([0, 0, -20])
        cylinder (r = SHANK_R, h = LENGTH + EPS, center = true, $fn = 24);
        translate (v = [0, 0, - (LENGTH - NUT_H) / 2 - EPS])
            cylinder (r = HEAD_R + 2*GAP, h = NUT_H + 2*GAP, center = true, $fn = 6);
    }
}

module grub_screws (){
    translate ([MIC_D + NUT_H + GAP + 5, 0, MIC_H / 2])
    rotate ([0,90,0])
        grub ();
    translate ([-MIC_D - NUT_H - GAP - 5, 0, MIC_H / 2])
    rotate ([0,270,0])
        grub ();
}

module screw_cover () {
    difference() {
        union(){
    translate([MIC_D + NUT_H - 1, 0, MIC_H / 2])
    rotate ([0,90,0])
        cylinder (MIC_D / 2, SHANK_R + 2, SHANK_R + 2, $fn = 24);
    translate([-MIC_D - NUT_H + 1, 0, MIC_H / 2])
    rotate ([0,270,0])
        cylinder (MIC_D / 2, SHANK_R + 2, SHANK_R + 2, $fn = 24);
            }
    translate ([-20, -20, HOLD_H])
        cube(40,0);
    }
}

module wire () {
    translate([0, 0, WIRE_D / 2])
    rotate([90, 90, 0])
    cylinder(WIRE_L, WIRE_D, WIRE_D);
}

module holder () {
    difference () {
        union() {
            screw_cover();
            cylinder(HOLD_H, d = HOLD_D, d = HOLD_D);
        }
        translate ([0,0, -EPS])
        microphone ();
        grub_screws();
        wire();
    }
}
holder ();