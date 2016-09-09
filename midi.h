/*****************************************************************************
 * midi.h
 * Lab 6: Final Project
 * ECE 476: Digital Systems Design Using Microcontrollers
 * Cornell University
 * April 2007
 * Andrew Godbehere (abg34) and Nathan Ward (njw23)
 ****************************************************************************/


/****************************************************************************/
#include <stdio.h>  //putchar

//MIDI op codes
#define NOTE_OFF 0b1000
#define NOTE_ON 0b1001
#define CONTROL_CHANGE 0b1011
#define CHANNEL_MODE 0b1011

//Note numbers
//Octave   Note Numbers
//         C  C#   D  D#   E   F  F#   G  G#   A  A#   B
//-1       0   1   2   3   4   5   6   7   8   9  10  11
//0       12  13  14  15  16  17  18  19  20  21  22  23
//1       24  25  26  27  28  29  30  31  32  33  34  35
//2       36  37  38  39  40  41  42  43  44  45  46  47
//3       48  49  50  51  52  53  54  55  56  57  58  59
//4       60  61  62  63  64  65  66  67  68  69  70  71
//5       72  73  74  75  76  77  78  79  80  81  82  83
//6       84  85  86  87  88  89  90  91  92  93  94  95
//7       96  97  98  99 100 101 102 103 104 105 106 107
//8      108 109 110 111 112 113 114 115 116 117 118 119
//9      120 121 122 123 124 125 126 127
#define Cn1  0
#define Csn1 1
#define Dn1  2
#define Dsn1 3
#define En1  4
#define Fn1  5
#define Fsn1 6
#define Gn1  7
#define Gsn1 8
#define An1  9
#define Asn1 10
#define Bn1  11
#define C0   12
#define Cs0  13
#define D0   14
#define Ds0  15
#define E0   16
#define F0   17
#define Fs0  18
#define G0   19
#define Gs0  20
#define A0   21
#define As0  22
#define B0   23
#define C1   24
#define Cs1  25
#define D1   26
#define Ds1  27
#define E1   28
#define F1   29
#define Fs1  30
#define G1   31
#define Gs1  32
#define A1   33
#define As1  34
#define B1   35
#define C2   36
#define Cs2  37
#define D2   38
#define Ds2  39
#define E2   40
#define F2   41
#define Fs2  42
#define G2   43
#define Gs2  44
#define A2   45
#define As2  46
#define B2   47
#define C3   48
#define Cs3  49
#define D3   50
#define Ds3  51
#define E3   52
#define F3   53
#define Fs3  54
#define G3   55
#define Gs3  56
#define A3   57
#define As3  58
#define B3   59
#define C4   60  //Middle C
#define Cs4  61
#define D4   62
#define Ds4  63
#define E4   64
#define F4   65
#define Fs4  66
#define G4   67
#define Gs4  68
#define A4   69
#define As4  70
#define B4   71
#define C5   72
#define Cs5  73
#define D5   74
#define Ds5  75
#define E5   76
#define F5   77
#define Fs5  78
#define G5   79
#define Gs5  80
#define A5   81
#define As5  82
#define B5   83
#define C6   84
#define Cs6  85
#define D6   86
#define Ds6  87
#define E6   88
#define F6   89
#define Fs6  90
#define G6   91
#define Gs6  92
#define A6   93
#define As6  94
#define B6   95
#define C7   96
#define Cs7  97
#define D7   98
#define Ds7  99
#define E7  100
#define F7  101
#define Fs7 102
#define G7  103
#define Gs7 104
#define A7  105
#define As7 106
#define B7  107
#define C8  108
#define Cs8 109
#define D8  110
#define Ds8 111
#define E8  112
#define F8  113
#define Fs8 114
#define G8  115
#define Gs8 116
#define A8  117
#define As8 118
#define B8  119
#define C9  120
#define Cs9 121
#define D9  122
#define Ds9 123
#define E9  124
#define F9  125
#define Fs9 126
#define G9  127


/****************************************************************************/
void init_midi(void) {
  //SET UP UART
  //Set USART Control and Status Register A (UCSRA)
  UCSR0A = 0b00000000;  //U2X=0
  //Set USART Control and Status Register B (UCSRB)
  UCSR0B = 0b00001000;  //Enable USART transmitter
  //Set USART Control and Status Register C (UCSRC)
  UCSR0C = 0b00000110;  //Asynchronous operation with 8-bit frames
  //Set USART Baud Rate Register (UBRR)
  //UBRR = fosc/(16*BAUD) - 1 = 8MHz/(16*31.25kBaud) - 1 = 15
  UBRR0H = 0; 
  UBRR0L = 15;  //MIDI is 31.25 kBaud
}

/****************************************************************************/
unsigned char status_byte(unsigned char opcode, unsigned char channel) {
  //Upper 4 bits: opcode to designate the type of message
  //Lower 4 bits: MIDI channel number
  if (channel>=1 && channel<=16) return ((opcode<<4) | (channel-1));
  else return 0xBF;
}

/****************************************************************************/
//Send a MIDI Control Change message containing one sensor value
void send_midi(unsigned char controller_number, 
    unsigned char controller_value) { 
  //MIDI spec for "Control Change" messages sends three bytes: 
  // 1) status byte: opcode/channel number
  // 2) first data byte: controller number
  // 3) second data byte: controller value
  putchar(status_byte(CONTROL_CHANGE, 1));  //Channel 1
  putchar(controller_number&0x7F);          //Controller number
  putchar(controller_value&0x7F);           //7 bits (0-127)
}

/****************************************************************************/
void send_allnotesoff(void) {
  //"All Notes Off" Channel Mode Message
  //Same as the Control Change, but implements Mode control and special 
  //message by using reserved controller numbers 120-127
  putchar(status_byte(CHANNEL_MODE, 1));    //Channel 1
  putchar(123);
  putchar(0);
  putchar(status_byte(CHANNEL_MODE, 2));    //Channel 2
  putchar(123);
  putchar(0);
  putchar(status_byte(CHANNEL_MODE, 3));    //Channel 3
  putchar(123);
  putchar(0);
}

/****************************************************************************/
void send_noteon(unsigned char note, unsigned char velocity, 
    unsigned char midi_chan) {
  //MIDI spec for "Note On" event sent when a note is depressed (start)
  //sends three bytes: 
  // 1) status byte: opcode/channel number
  // 2) first data byte: the key (note) number
  // 3) second data byte: the velocity
  //midi_chan must be between 1 and 3
  putchar(status_byte(NOTE_ON, midi_chan)); //Channel midi_chan
  putchar(note&0x7F);                       //7 bits (0-127)
  putchar(velocity&0x7F);                   //7 bits (0-127)
}

/****************************************************************************/
void send_noteoff(unsigned char note, unsigned char velocity, 
    unsigned char midi_chan) {
  //MIDI spec for "Note Off" event sent when a note is released (ended)
  //sends three bytes: 
  // 1) status byte: opcode/channel number
  // 2) first data byte: the key (note) number
  // 3) second data byte: the velocity
  putchar(status_byte(NOTE_OFF, midi_chan)); //Channel midi_chan
  putchar(note&0x7F);                       //7 bits (0-127)
  putchar(velocity&0x7F);                   //7 bits (0-127)
}

/****************************************************************************/