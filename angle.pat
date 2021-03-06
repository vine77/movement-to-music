max v2;
#N vpatcher 795 171 1179 377;
#P window setfont "Sans Serif" 9.;
#P comment 265 51 24 196617 Az;
#P comment 158 51 24 196617 Ay;
#P window linecount 2;
#P newex 247 80 94 196617 expr acos($f1/64.) * 180. / 3.141593;
#P newex 140 80 94 196617 expr asin($f1/64.) * 180. / 3.141593;
#P newex 33 81 94 196617 expr asin($f1/64.) * 180. / 3.141593;
#P window linecount 1;
#P comment 247 146 94 196617 z angle in degrees;
#P comment 140 146 94 196617 Roll (y) in degrees;
#P outlet 247 126 15 0;
#P outlet 140 126 15 0;
#P outlet 33 126 15 0;
#P inlet 247 51 15 0;
#P inlet 140 51 15 0;
#P inlet 33 51 15 0;
#P comment 30 26 311 196617 Calculates inclination of axes from acceleration of gravity;
#P comment 33 146 94 196617 Pitch (x) in degrees;
#P comment 51 51 24 196617 Ax;
#P connect 3 0 11 0;
#P connect 11 0 6 0;
#P connect 4 0 12 0;
#P connect 12 0 7 0;
#P connect 5 0 13 0;
#P connect 13 0 8 0;
#P pop;
