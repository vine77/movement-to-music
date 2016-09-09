max v2;
#N vpatcher 153 59 1114 719;
#P origin -146 0;
#P button 469 579 15 0;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P newex 453 599 30 196617 s hit;
#P message 453 579 14 196617 2;
#P newex 548 533 34 196617 * -1.;
#P newex 548 512 35 196617 r s2y;
#P newex 453 533 34 196617 * -1.;
#P newex 35 170 47 196617 * 25.59;
#P newex 35 191 31 196617 + 64;
#P window setfont "Sans Serif" 14.;
#P comment 454 389 151 196622 Data interpretation;
#P comment 311 229 108 196622 MIDI;
#P window setfont "Sans Serif" 9.;
#P window linecount 2;
#P newex 721 331 47 196617 print pitchbend;
#P newex 668 331 52 196617 print aftertouch;
#P newex 614 331 53 196617 print pgmchange;
#P newex 546 331 67 196617 print controlchange;
#P newex 481 331 64 196617 print polypressure;
#P newex 432 331 48 196617 print noteonoff;
#P window linecount 1;
#P newex 432 263 40 196617 unpack;
#P number 432 285 27 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P button 432 303 15 0;
#P number 462 285 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P number 524 285 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P number 494 285 27 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P newex 494 263 40 196617 unpack;
#P number 585 285 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P number 555 285 27 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P newex 555 263 40 196617 unpack;
#P number 618 263 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P button 618 285 15 0;
#P newex 432 237 340 196617 midiparse;
#B color 5;
#P number 762 263 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P button 762 285 15 0;
#P number 707 263 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P button 707 285 15 0;
#P button 664 285 15 0;
#P number 664 263 28 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P button 494 303 15 0;
#P button 555 303 15 0;
#P window linecount 2;
#P comment 509 301 47 196617 Poly Pressure;
#P comment 448 302 38 196617 Note On/Off;
#P comment 573 302 44 196617 Control Change;
#P comment 746 302 41 196617 MIDI Channel;
#P comment 662 302 34 196617 After Touch;
#P comment 617 302 40 196617 Pgm Change;
#P comment 705 302 32 196617 Pitch Bend;
#P window linecount 1;
#P newex 314 293 45 196617 midiinfo;
#P message 349 274 20 196617 0;
#P newex 349 254 52 196617 loadbang;
#P newex 314 338 41 196617 midiin;
#B color 5;
#P window setfont "Sans Serif" 14.;
#P comment 817 72 82 196622 Link quality;
#P window setfont "Sans Serif" 9.;
#P flonum 822 481 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 710 481 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 598 481 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 486 482 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P newex 234 170 47 196617 * 25.59;
#P newex 234 191 31 196617 + 64;
#P newex 183 170 47 196617 * 25.59;
#P newex 183 191 31 196617 + 64;
#P newex 132 170 47 196617 * 25.59;
#P newex 132 191 31 196617 + 64;
#P newex 81 170 47 196617 * 25.59;
#P newex 81 191 31 196617 + 64;
#P button 754 579 15 0;
#P button 659 579 15 0;
#P button 564 579 15 0;
#P slider 832 168 15 128 0 1;
#N vpatcher 947 197 1181 461;
#P window setfont "Sans Serif" 9.;
#P window linecount 0;
#P newex 124 136 72 196617 expr 255-$i1;
#P newex 124 78 30 196617 - 63;
#P window linecount 1;
#P message 124 183 75 196617 brgb \$1 255 0;
#P newex 124 101 27 196617 * 4;
#P window linecount 0;
#P newex 38 79 27 196617 * 4;
#P window linecount 1;
#P newex 38 55 96 196617 split 0 63;
#P outlet 38 209 15 0;
#P message 38 183 75 196617 brgb 255 \$1 0;
#P inlet 38 29 15 0;
#P connect 0 0 3 0;
#P connect 3 0 4 0;
#P connect 4 0 1 0;
#P fasten 6 0 2 0 129 203 43 203;
#P connect 1 0 2 0;
#P connect 3 1 7 0;
#P connect 7 0 5 0;
#P connect 5 0 8 0;
#P connect 8 0 6 0;
#P pop;
#P newobj 851 188 55 196617 p getcolor;
#P number 851 168 35 9 0 127 3 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P newex 832 143 53 196617 ctlin 13;
#P flonum 746 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 708 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 670 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 630 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 592 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 554 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 512 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 474 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 436 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 394 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 356 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P flonum 318 158 35 9 0 0 0 3 0 0 0 221 221 221 222 222 222 0 0 0;
#P window setfont "Sans Serif" 14.;
#P comment 311 74 108 196622 Sensor input;
#P comment 346 389 75 196622 Drum kit;
#B frgb 255 255 255;
#P window setfont "Sans Serif" 9.;
#P newex 738 599 31 196617 s hit;
#P message 738 579 14 196617 4;
#P newex 643 599 31 196617 s hit;
#P message 643 579 14 196617 3;
#P newex 548 599 30 196617 s hit;
#P message 548 579 14 196617 2;
#P newex 346 420 30 196617 r hit;
#P slider 273 480 15 128 0 1;
#P newex 273 458 39 196617 r s4zr;
#P slider 257 480 15 128 0 1;
#P newex 257 439 40 196617 r s4yr;
#P slider 241 480 15 128 0 1;
#P newex 241 420 40 196617 r s4xr;
#P slider 206 480 15 128 0 1;
#P newex 206 458 39 196617 r s3zr;
#P slider 190 480 15 128 0 1;
#P newex 190 439 40 196617 r s3yr;
#P slider 174 480 15 128 0 1;
#P newex 174 420 40 196617 r s3xr;
#P slider 140 480 15 128 0 1;
#P newex 140 458 38 196617 r s2zr;
#P slider 124 480 15 128 0 1;
#P newex 124 439 40 196617 r s2yr;
#P slider 108 480 15 128 0 1;
#P newex 108 420 40 196617 r s2xr;
#P window setfont "Sans Serif" 14.;
#P comment 35 387 162 196622 Sensor axes monitor;
#P slider 74 480 15 128 0 1;
#P window setfont "Sans Serif" 9.;
#P newex 74 458 38 196617 r s1zr;
#P slider 58 480 15 128 0 1;
#P newex 58 439 40 196617 r s1yr;
#P slider 42 480 15 128 0 1;
#P newex 42 420 40 196617 r s1xr;
#P user panel 23 377 303 248;
#X brgb 216 221 231;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#N vpatcher 86 120 760 512;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P message 408 350 72 196617 open tom.wav;
#P button 51 332 15 0;
#P button 69 217 15 0;
#P window linecount 0;
#P message 69 255 80 196617 open crash.wav;
#P message 154 275 73 196617 open kick.wav;
#P message 239 298 80 196617 open snare.wav;
#P message 323 323 105 196617 open closedhihat.wav;
#P newex 579 149 60 196617 send~ mix;
#P message 547 100 30 196617 open;
#P message 579 100 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 579 127 44 196617 sfplay~;
#P newex 494 149 60 196617 send~ mix;
#P message 462 100 30 196617 open;
#P message 494 100 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 494 127 44 196617 sfplay~;
#P newex 409 149 60 196617 send~ mix;
#P message 377 100 30 196617 open;
#P message 409 100 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 409 127 44 196617 sfplay~;
#P newex 69 58 521 196617 route 1 2 3 4 5 6;
#P inlet 69 32 15 0;
#P newex 69 332 48 196617 loadbang;
#P message 324 233 175 196617 open 31851_HardPCM_Chip011.wav;
#P message 239 213 175 196617 open 31873_HardPCM_Chip036.wav;
#P message 154 193 175 196617 open 31852_HardPCM_Chip012.wav;
#P message 69 173 175 196617 open 31842_HardPCM_Chip002.wav;
#P newex 324 149 60 196617 send~ mix;
#P newex 239 149 60 196617 send~ mix;
#P newex 154 149 60 196617 send~ mix;
#P newex 69 149 60 196617 send~ mix;
#P message 292 100 30 196617 open;
#P message 324 100 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 324 127 44 196617 sfplay~;
#P message 207 100 30 196617 open;
#P message 239 100 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 239 127 44 196617 sfplay~;
#P message 122 100 30 196617 open;
#P message 154 100 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 154 127 44 196617 sfplay~;
#P message 37 99 30 196617 open;
#P message 69 99 14 196617 1;
#N sfplay~  1 120960 0 ;
#P newobj 69 126 44 196617 sfplay~;
#P objectname sfplay~;
#P connect 21 0 22 0;
#P connect 22 0 1 0;
#P connect 1 0 0 0;
#P connect 2 0 0 0;
#P hidden connect 16 0 0 0;
#P connect 38 0 0 0;
#P connect 0 0 12 0;
#P hidden connect 39 0 16 0;
#P hidden connect 20 0 38 0;
#P hidden connect 40 0 20 0;
#P connect 22 1 4 0;
#P connect 5 0 3 0;
#P connect 4 0 3 0;
#P hidden connect 17 0 3 0;
#P connect 37 0 3 0;
#P connect 3 0 13 0;
#P hidden connect 39 0 17 0;
#P hidden connect 20 0 37 0;
#P connect 22 2 7 0;
#P connect 7 0 6 0;
#P connect 8 0 6 0;
#P hidden connect 18 0 6 0;
#P connect 36 0 6 0;
#P connect 6 0 14 0;
#P hidden connect 39 0 18 0;
#P hidden connect 20 0 36 0;
#P hidden connect 20 0 35 0;
#P connect 22 3 10 0;
#P connect 11 0 9 0;
#P connect 10 0 9 0;
#P hidden connect 19 0 9 0;
#P connect 35 0 9 0;
#P connect 9 0 15 0;
#P hidden connect 39 0 19 0;
#P connect 20 0 41 0;
#P connect 22 4 24 0;
#P connect 24 0 23 0;
#P connect 25 0 23 0;
#P connect 41 0 23 0;
#P connect 23 0 26 0;
#P connect 22 5 28 0;
#P connect 29 0 27 0;
#P connect 28 0 27 0;
#P connect 27 0 30 0;
#P connect 22 6 32 0;
#P connect 32 0 31 0;
#P connect 33 0 31 0;
#P connect 31 0 34 0;
#P pop;
#P newobj 346 454 55 196617 p drumset;
#P window setfont "Sans Serif" 14.;
#P comment 35 74 113 196622 Sensor monitor;
#P window setfont "Sans Serif" 9.;
#P newex 346 532 75 196617 receive~ mix;
#P user ezdac~ 346 576 390 609 0;
#P newex 738 531 34 196617 r s4z;
#P newex 643 531 34 196617 r s3z;
#P newex 453 512 35 196617 r s1y;
#P slider 234 221 15 128 0 1;
#P newex 234 149 31 196617 r s4;
#P slider 183 221 15 128 0 1;
#P newex 183 149 31 196617 r s3;
#P slider 132 220 15 128 0 1;
#P newex 132 149 31 196617 r s2;
#P slider 81 220 15 128 0 1;
#P newex 81 149 31 196617 r s1;
#P slider 35 220 15 128 0 1;
#P newex 140 103 31 196617 r s4;
#P newex 105 103 31 196617 r s3;
#P newex 70 103 31 196617 r s2;
#P newex 35 103 31 196617 r s1;
#P newex 789 481 30 196617 s s4;
#P newex 677 481 30 196617 s s3;
#P newex 565 481 30 196617 s s2;
#P newex 453 481 30 196617 s s1;
#P newex 643 556 92 196617 movement 2.2 1.1;
#P newex 548 556 92 196617 movement 2.2 1.1;
#P newex 453 556 92 196617 movement 2.2 1.1;
#P newex 738 556 92 196617 movement 2.2 1.1;
#P newex 863 433 34 196617 r s4z;
#P newex 826 433 35 196617 r s4y;
#P newex 789 433 35 196617 r s4x;
#P newex 751 433 34 196617 r s3z;
#P newex 714 433 35 196617 r s3y;
#P newex 677 433 35 196617 r s3x;
#P newex 639 433 34 196617 r s2z;
#P newex 602 433 35 196617 r s2y;
#P newex 565 433 35 196617 r s2x;
#P newex 527 433 34 196617 r s1z;
#P newex 490 433 35 196617 r s1y;
#P newex 453 433 35 196617 r s1x;
#P newex 739 179 34 196617 s s4z;
#P newex 701 179 35 196617 s s4y;
#P newex 663 179 35 196617 s s4x;
#P newex 623 179 34 196617 s s3z;
#P newex 585 180 35 196617 s s3y;
#P newex 547 179 35 196617 s s3x;
#P newex 505 179 34 196617 s s2z;
#P newex 467 179 35 196617 s s2y;
#P newex 429 179 35 196617 s s2x;
#P newex 387 179 34 196617 s s1z;
#P newex 349 179 35 196617 s s1y;
#P newex 311 179 35 196617 s s1x;
#P newex 35 125 116 196617 activity;
#P comment 647 103 108 196617 Left foot: High hat;
#P comment 535 103 108 196617 Right foot: Kick drum;
#P window linecount 2;
#P comment 423 103 108 196617 Left hand: Snare \, crash;
#P window linecount 1;
#P hidden newex 363 30 40 196617 angle;
#P newex 789 457 84 196617 totalaccel;
#P newex 677 457 84 196617 totalaccel;
#P newex 565 457 85 196617 totalaccel;
#P newex 453 457 85 196617 totalaccel;
#N vpatcher 991 395 1252 592;
#P window setfont "Sans Serif" 9.;
#P newex 163 63 39 196617 s s4zr;
#P newex 108 63 40 196617 s s4yr;
#P newex 53 63 40 196617 s s4xr;
#P newex 155 110 46 196617 / 25.59;
#P newex 100 110 46 196617 / 25.59;
#P newex 45 110 46 196617 / 25.59;
#P newex 155 86 30 196617 - 64;
#P newex 100 86 30 196617 - 64;
#P newex 45 86 30 196617 - 64;
#P outlet 155 135 15 0;
#P outlet 100 135 15 0;
#P outlet 45 135 15 0;
#P newex 155 37 45 196617 ctlin 12;
#P newex 100 37 45 196617 ctlin 11;
#P newex 45 37 45 196617 ctlin 10;
#P connect 0 0 6 0;
#P connect 6 0 9 0;
#P connect 9 0 3 0;
#P connect 0 0 12 0;
#P connect 1 0 7 0;
#P connect 7 0 10 0;
#P connect 10 0 4 0;
#P connect 1 0 13 0;
#P connect 2 0 8 0;
#P connect 8 0 11 0;
#P connect 11 0 5 0;
#P connect 2 0 14 0;
#P pop;
#P newobj 663 133 86 196617 p Sensor4;
#N vpatcher 562 275 812 465;
#P window setfont "Sans Serif" 9.;
#P newex 161 56 39 196617 s s3zr;
#P newex 106 56 40 196617 s s3yr;
#P newex 51 56 40 196617 s s3xr;
#P newex 153 103 46 196617 / 25.59;
#P newex 98 103 46 196617 / 25.59;
#P newex 43 103 46 196617 / 25.59;
#P newex 153 79 30 196617 - 64;
#P newex 98 79 30 196617 - 64;
#P newex 43 79 30 196617 - 64;
#P outlet 153 128 15 0;
#P outlet 98 128 15 0;
#P outlet 43 128 15 0;
#P newex 153 30 39 196617 ctlin 9;
#P newex 98 30 39 196617 ctlin 8;
#P newex 43 30 39 196617 ctlin 7;
#P connect 0 0 6 0;
#P connect 6 0 9 0;
#P connect 9 0 3 0;
#P connect 0 0 12 0;
#P connect 1 0 7 0;
#P connect 7 0 10 0;
#P connect 10 0 4 0;
#P connect 1 0 13 0;
#P connect 2 0 8 0;
#P connect 8 0 11 0;
#P connect 11 0 5 0;
#P connect 2 0 14 0;
#P pop;
#P newobj 547 133 87 196617 p Sensor3;
#N vpatcher 656 338 908 550;
#P window setfont "Sans Serif" 9.;
#P newex 163 70 39 196617 s s2zr;
#P newex 108 70 40 196617 s s2yr;
#P newex 53 70 40 196617 s s2xr;
#P newex 155 117 46 196617 / 25.59;
#P newex 100 117 46 196617 / 25.59;
#P newex 45 117 46 196617 / 25.59;
#P newex 155 93 30 196617 - 64;
#P newex 100 93 30 196617 - 64;
#P newex 45 93 30 196617 - 64;
#P outlet 155 142 15 0;
#P outlet 100 142 15 0;
#P outlet 45 142 15 0;
#P newex 155 44 39 196617 ctlin 6;
#P newex 100 44 39 196617 ctlin 5;
#P newex 45 44 39 196617 ctlin 4;
#P connect 0 0 6 0;
#P connect 6 0 9 0;
#P connect 9 0 3 0;
#P connect 0 0 12 0;
#P connect 1 0 7 0;
#P connect 7 0 10 0;
#P connect 10 0 4 0;
#P connect 1 0 13 0;
#P connect 2 0 8 0;
#P connect 8 0 11 0;
#P connect 11 0 5 0;
#P connect 2 0 14 0;
#P pop;
#P newobj 429 133 86 196617 p Sensor2;
#N vpatcher 643 299 889 496;
#P window setfont "Sans Serif" 9.;
#P window linecount 1;
#P newex 156 63 39 196617 s s1zr;
#P newex 101 63 40 196617 s s1yr;
#P window linecount 0;
#P newex 46 63 40 196617 s s1xr;
#P window linecount 1;
#P newex 148 110 46 196617 / 25.59;
#P newex 93 110 46 196617 / 25.59;
#P window linecount 0;
#P newex 38 110 46 196617 / 25.59;
#P window linecount 1;
#P newex 148 86 30 196617 - 64;
#P newex 93 86 30 196617 - 64;
#P window linecount 0;
#P newex 38 86 30 196617 - 64;
#P outlet 148 135 15 0;
#P outlet 93 135 15 0;
#P outlet 38 135 15 0;
#P newex 148 37 39 196617 ctlin 3;
#P newex 93 37 39 196617 ctlin 2;
#P newex 38 37 39 196617 ctlin 1;
#P connect 0 0 6 0;
#P connect 6 0 9 0;
#P connect 9 0 3 0;
#P connect 0 0 12 0;
#P connect 1 0 7 0;
#P connect 7 0 10 0;
#P connect 10 0 4 0;
#P connect 1 0 13 0;
#P connect 2 0 8 0;
#P connect 8 0 11 0;
#P connect 11 0 5 0;
#P connect 2 0 14 0;
#P pop;
#P newobj 311 133 86 196617 p Sensor1;
#P window linecount 2;
#P comment 23 26 299 196617 Wireless Wearable Sensor System for Gestural Control of Music Air drums patch;
#P comment 311 103 108 196617 Right hand: High-hat \, Tom;
#P user panel 23 64 270 307;
#X brgb 216 221 231;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#P user panel 333 377 100 248;
#X brgb 117 33 33;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#P window linecount 1;
#P comment 424 80 274 196617 Sensor patches send values from -2.5 to 2.46;
#P user panel 300 64 500 149;
#X brgb 216 221 231;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#P user panel 808 64 120 307;
#X brgb 0 255 0;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#P user umenu 314 313 96 196647 1 64 329 0;
#X add "Midiman Uno Port 1";
#X add "to MaxMSP 1";
#X add "to MaxMSP 2";
#P window linecount 2;
#P comment 371 285 50 196617 MIDI input port;
#P user panel 300 221 500 150;
#X brgb 216 221 231;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#P user panel 441 377 487 248;
#X brgb 216 221 231;
#X frgb 0 0 0;
#X border 1;
#X rounded 10;
#X shadow 0;
#X done;
#P connect 56 0 23 0;
#P connect 23 0 184 0;
#P connect 184 0 183 0;
#P connect 183 0 60 0;
#P connect 77 0 78 0;
#P connect 79 0 80 0;
#P connect 57 0 23 1;
#P connect 81 0 82 0;
#P connect 61 0 131 0;
#P connect 131 0 130 0;
#P connect 130 0 62 0;
#P connect 58 0 23 2;
#P connect 84 0 85 0;
#P connect 86 0 87 0;
#P connect 63 0 133 0;
#P connect 133 0 132 0;
#P connect 132 0 64 0;
#P connect 59 0 23 3;
#P connect 88 0 89 0;
#P connect 90 0 91 0;
#P connect 65 0 135 0;
#P connect 135 0 134 0;
#P connect 134 0 66 0;
#P connect 92 0 93 0;
#P connect 94 0 95 0;
#P connect 67 0 137 0;
#P connect 137 0 136 0;
#P connect 136 0 68 0;
#P connect 96 0 97 0;
#P connect 98 0 99 0;
#P connect 100 0 101 0;
#P connect 11 0 24 0;
#P connect 146 0 3 0;
#P fasten 3 1 143 0 405 332 319 332;
#P connect 11 0 111 0;
#P connect 102 0 75 0;
#P connect 73 0 72 0;
#P connect 11 1 25 0;
#P connect 144 0 145 0;
#P connect 145 0 146 1;
#P connect 11 1 112 0;
#P fasten 73 0 72 1 351 561 385 561;
#P connect 11 2 26 0;
#P connect 11 2 113 0;
#P connect 12 0 27 0;
#P fasten 143 0 162 0 319 357 425 357 425 231 437 231;
#P connect 162 0 174 0;
#P connect 174 0 173 0;
#P connect 173 0 172 0;
#P hidden connect 162 0 175 0;
#P connect 12 0 114 0;
#P connect 36 0 15 0;
#P connect 15 0 52 0;
#P connect 69 0 185 0;
#P connect 185 0 49 0;
#P connect 49 0 188 0;
#P connect 188 0 189 0;
#P connect 174 1 171 0;
#P connect 12 1 28 0;
#P connect 49 0 190 0;
#P connect 12 1 115 0;
#P hidden connect 162 1 176 0;
#P fasten 15 0 138 0 458 477 491 477;
#P connect 37 0 15 1;
#P fasten 162 1 168 0 492 259 499 259;
#P connect 168 0 169 0;
#P connect 169 0 155 0;
#P connect 12 2 29 0;
#P connect 12 2 116 0;
#P connect 168 1 170 0;
#P connect 38 0 15 2;
#P hidden connect 162 2 177 0;
#P connect 13 0 30 0;
#P connect 186 0 187 0;
#P connect 187 0 50 0;
#P connect 50 0 103 0;
#P connect 103 0 104 0;
#P connect 13 0 117 0;
#P fasten 162 2 165 0 547 259 560 259;
#P connect 165 0 166 0;
#P connect 166 0 154 0;
#P connect 50 0 127 0;
#P connect 39 0 16 0;
#P connect 16 0 53 0;
#P connect 13 1 31 0;
#P connect 165 1 167 0;
#P connect 13 1 118 0;
#P fasten 16 0 139 0 570 477 603 477;
#P connect 40 0 16 1;
#P hidden connect 162 3 178 0;
#P fasten 162 3 164 0 602 259 623 259;
#P connect 164 0 163 0;
#P connect 13 2 32 0;
#P connect 13 2 119 0;
#P connect 41 0 16 2;
#P connect 70 0 51 0;
#P connect 51 0 105 0;
#P connect 105 0 106 0;
#P connect 51 0 128 0;
#P connect 14 0 33 0;
#P fasten 162 4 156 0 657 259 669 259;
#P connect 156 0 157 0;
#P hidden connect 162 4 179 0;
#P connect 14 0 120 0;
#P connect 42 0 17 0;
#P connect 17 0 54 0;
#P connect 14 1 34 0;
#P connect 162 5 159 0;
#P connect 159 0 158 0;
#P connect 14 1 121 0;
#P fasten 17 0 140 0 682 477 715 477;
#P connect 43 0 17 1;
#P hidden connect 162 5 180 0;
#P connect 71 0 48 0;
#P connect 48 0 107 0;
#P connect 107 0 108 0;
#P connect 14 2 35 0;
#P connect 14 2 122 0;
#P connect 44 0 17 2;
#P connect 48 0 129 0;
#P connect 162 6 161 0;
#P connect 161 0 160 0;
#P connect 45 0 18 0;
#P connect 18 0 55 0;
#P hidden connect 125 0 4 0;
#P fasten 18 0 141 0 794 477 827 477;
#P connect 46 0 18 1;
#P connect 123 0 126 0;
#P connect 123 0 124 0;
#P connect 124 0 125 0;
#P connect 47 0 18 2;
#P pop;
