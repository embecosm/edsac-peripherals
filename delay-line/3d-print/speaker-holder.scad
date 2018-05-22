// Speaker
SPEAK_D = 15 + 1;
SPEAK_H = 8;

// GAP & EPS
GAP = 0.4;
EPS = 0.01;

// Holder
S_HOLD_H = SPEAK_H + GAP + 2;
S_HOLD_D = SPEAK_D + 2*GAP + 10;

// Wire
WIRE_D = 4;
WIRE_EDGE = 3; // distance from the edge

// Grub screw & nut
M3_SHANK_R = 3.0 / 2 + GAP;
M3_HEAD_R   = 5.5 / 2 + GAP;
SHANK_R  = M3_SHANK_R;
HEAD_R   = M3_HEAD_R;
HEAD_H   = 3.5;
NUT_H    = 2.5;
LENGTH   = S_HOLD_D / 2 + 10;

module speaker() {
    translate([0,0, -EPS])
    cylinder(SPEAK_H + EPS, d = SPEAK_D + 2*GAP, d = SPEAK_D + 2*GAP);
}

module wire() {
    translate([0, SPEAK_D/2 - WIRE_EDGE - 2*GAP, 0])
        cylinder(100, d = WIRE_D + 4*GAP);
    translate([0,-(SPEAK_D/2 - WIRE_EDGE - 2*GAP), 0])
        cylinder(100, d = WIRE_D + 4*GAP);
    translate([0, S_HOLD_D / 2, -EPS])
    cylinder(S_HOLD_D, d = WIRE_D + 4* GAP);
}

module grub () {
    union () {
        translate([0, 0, -17])
        cylinder (r = SHANK_R, h = LENGTH + EPS, center = true, $fn = 24);
        translate (v = [0, 0, - (LENGTH - NUT_H) / 2 - EPS])
            cylinder (r = HEAD_R + 2*GAP, h = NUT_H + 2*GAP, center = true, $fn = 6);
    }
}

module all_grub () {
    translate ([-0.8, 0, 0]) {
    translate ([0, 0, SPEAK_H / 2])
    rotate([0, 90, 0])
    grub();
        translate ([- (LENGTH - NUT_H) / 2 - EPS, 0, 1])
            rotate([0, 90, 0])            
                cylinder (r = HEAD_R + 2*GAP, h = NUT_H + 2*GAP, center = true, $fn = 6);
    }
    translate([0.8, 0, 0]) {
    translate ([0, 0, SPEAK_H / 2])
    rotate([0, 270, 0])
    grub();
        translate ([(LENGTH - NUT_H) / 2 + EPS, 0, 1])
            rotate([0, 90, 0])            
                cylinder (r = HEAD_R + 2*GAP, h = NUT_H + 2*GAP, center = true, $fn = 6);
    }
}

module speak_holder() {
    difference() {
        cylinder(S_HOLD_H + EPS, d = S_HOLD_D, d = S_HOLD_D);
        speaker();
        wire();
        all_grub();
    }
}

speak_holder();

