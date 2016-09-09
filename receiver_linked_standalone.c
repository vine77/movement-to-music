/*****************************************************************************
 * receiver_linked_standalone.c
 * Lab 6: Final Project
 * ECE 476: Digital Systems Design Using Microcontrollers
 * Cornell University
 * April 2007
 * Andrew Godbehere (abg34) and Nathan Ward (njw23)
 ****************************************************************************/


//Base-station with on-board motion analysis
//Sends MIDI Note On/Off messages to synth

/****************************************************************************/
#include <mega644.h>
#include <at86rf230.h>
#include <midi.h>

#define SAMPLE_TIMEOUT 20
#define CHORD_TIMEOUT 15

//sensor 1 = left foot, sensor 2 = right foot
//sensor 3 = left hand, sensor 4 = right hand

#define LF_X 0   //left foot
#define LF_Y 1
#define LF_Z 2
#define RF_X 3   //right foot
#define RF_Y 4
#define RF_Z 5
#define LH_X 6   //left hand
#define LH_Y 7
#define LH_Z 8
#define RH_X 9   //right hand
#define RH_Y 10
#define RH_Z 11

#define STOMP_THRESH 75
#define MOVE_THRESH_LOW   20
#define STOP_THRESH_LOW  65
#define MOVE_THRESH_HIGH  107
#define STOP_THRESH_HIGH 70
#define JERK_THRESH_POS 50
#define JERK_THRESH_NEG -50

#define DEBOUNCE_TIME 150

unsigned char sample_timer, note_timer, chord_timer, debounce_timer, 
    Lstomp_timer,Rstomp_timer;

unsigned char RF,LF,RH,LH;
unsigned char Lstomp,Rstomp;
unsigned char note_queue[4];
unsigned long note_duration[4];
unsigned char note_index;
signed char changechord;
unsigned char chord;
unsigned char sampling;
signed char third;
unsigned char prev_note;

unsigned char prev_RH;
signed char RH_da;
unsigned char calibration;

//If previous is greater than current by a large amount, we've stomped. After 
//that, find max value of the change in acceleration. Once max value has been 
//found, after change in acceleration has fallen below second threshold, we 
//have found note duration.

/****************************************************************************/
void note_increment(void)  {
  if (note_index == 3)
    note_index = 0;
  else note_index++;
}

/****************************************************************************/
void notes_off(void)  {
  unsigned char i;
  for (i=0;i<4;i++)  {
    if ((note_duration[i] == 0) && (note_queue[i] != 0))  {
      send_allnotesoff();
      note_queue[i] = 0;
    }  
  }
}

/****************************************************************************/
void play_chord(unsigned long duration)  {
//power chords: root, fifth
//circle of fifths: C,G,D,A,E,B,Fs,Cs,Gs,Ds,As,F
  if ((chord >= 0) && (chord <= 10))  {   //C
    send_noteon(C4,125,1);
    send_noteon(G4,125,1);
    send_noteon(C4+third,125,1);
    note_queue[0] = C4;
    note_queue[1] = G4;    
    note_queue[2] = C4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 11) && (chord <= 21))  {  //G
    send_noteon(G4,125,1);
    send_noteon(D4,125,1);
    send_noteon(G4+third,125,1);
    note_queue[0] = G4;
    note_queue[1] = D4;
    note_queue[2] = G4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 22) && (chord <= 32))  {  //D
    send_noteon(D4,125,1);
    send_noteon(A4,125,1);
    send_noteon(D4+third,125,1);
    note_queue[0] = D4;
    note_queue[1] = A4;     
    note_queue[2] = D4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 33) && (chord <= 42))  {  //A
    send_noteon(A4,125,1);
    send_noteon(E4,125,1);
    send_noteon(A4+third,125,1);
    note_queue[0] = A4;
    note_queue[1] = E4;       
    note_queue[2] = A4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 43) && (chord <= 53))  {  //E
    send_noteon(E4,125,1);
    send_noteon(B4,125,1);
    send_noteon(E4+third,125,1);
    note_queue[0] = E4;
    note_queue[1] = B4;        
    note_queue[2] = E4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;    
  }
  else if ((chord >= 54) && (chord <= 64))  {  //B
    send_noteon(B4,125,1);
    send_noteon(Fs4,125,1);
    send_noteon(B4+third,125,1);
    note_queue[0] = B4;
    note_queue[1] = Fs4;      
    note_queue[2] = B4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 65) && (chord <= 74))  {  //Fs
    send_noteon(Fs4,125,1);
    send_noteon(Cs4,125,1);
    send_noteon(Fs4+third,125,1);
    note_queue[0] = Fs4;
    note_queue[1] = Cs4;       
    note_queue[2] = Fs4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 75) && (chord <= 85))  {  //Cs
    send_noteon(Cs4,125,1);
    send_noteon(Gs4,125,1);
    send_noteon(Cs4+third,125,1);
    note_queue[0] = Cs4;
    note_queue[1] = Gs4;        
    note_queue[2] = Cs4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 86) && (chord <= 96))  {   //Gs
    send_noteon(Gs4,125,1);
    send_noteon(Ds4,125,1);
    send_noteon(Gs4+third,125,1);
    note_queue[0] = Gs4;
    note_queue[1] = Ds4;        
    note_queue[2] = Gs4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 97) && (chord <= 106))  {   //Ds
    send_noteon(Ds4,125,1);
    send_noteon(As4,125,1);
    send_noteon(Ds4+third,125,1);
    note_queue[0] = Ds4;
    note_queue[1] = As4;        
    note_queue[2] = Ds4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  else if ((chord >= 107) && (chord <= 117))  {  //As
    send_noteon(As4,125,1);
    send_noteon(F4,125,1);   
    send_noteon(As4+third,125,1);
    note_queue[0] = As4;
    note_queue[1] = F4;        
    note_queue[2] = As4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
  
  else {        //F
    send_noteon(F4,125,1);
    send_noteon(C4,125,1); 
    send_noteon(F4+third,125,1);
    note_queue[0] = F4;
    note_queue[1] = C4;       
    note_queue[2] = F4+third;
    note_duration[0] = duration;
    note_duration[1] = duration;
    note_duration[2] = duration;
  }
}

/****************************************************************************/
interrupt [TIM0_COMPA] void ms_timer(void)  {
  unsigned char i;
  if (sample_timer > 0) sample_timer--;
  if (note_timer > 0) note_timer--;
  if (sampling == 0)  {
    for (i=0;i<4;i++)  {
      if (note_duration[i] > 0) note_duration[i]--;
    }
    if (Lstomp > 0) Lstomp--;
    if (Rstomp > 0) Rstomp--;
  } 
  if (chord_timer > 0) chord_timer--;
  if (debounce_timer > 0) debounce_timer--;
  if (Lstomp_timer > 0) Lstomp_timer--;
  if (Rstomp_timer > 0) Rstomp_timer--;
}

/****************************************************************************/
void sample(void) {
  unsigned char delay;
  sampling = 1;
  RF_rx_to_tx();
  tx_frame_length = 1;
  transmit_frame[0] = DATA_REQ;
  RF_download_frame();
  RF_transmit_frame();
  RF_wait_for_transmit();
  RF_tx_to_rx();
  RF_clear_IRQ();
  delay_us(100);
  delay = RF_receiver_listen_timeout(80);  //listen for 20ms
  if (delay != 0)  {  //then we have received something
    PORTD.7 = ~PORTD.7;
    RF_upload_frame();
    RH = receive_frame[RH_X];
    LH = receive_frame[LH_X];
    RF = receive_frame[RF_Y];
    LF = receive_frame[LF_Y];            
    if (calibration == 0)  {
      prev_RH = RH;
      calibration = 1;
    }
    else if (LQI > 30)  {   
      //negative, going left, positive, going right
      RH_da = ((signed char)prev_RH) - ((signed char)RH);
      if ((changechord == 0) && (RH < MOVE_THRESH_LOW) && 
          (RH_da > ((signed char)JERK_THRESH_POS)))  {
        //lateral sweep started when jerk & acceleration both above threshold
        changechord = -1;
        debounce_timer = DEBOUNCE_TIME;
      }                    
      else if ((changechord == 0) && (RH > MOVE_THRESH_HIGH) && 
          (RH_da < ((signed char)JERK_THRESH_NEG)))  {
        //lateral sweep started
        changechord = 1;
        debounce_timer = DEBOUNCE_TIME;
      } 
      else if ((changechord == 1) && (debounce_timer == 0) && 
          (RH_da>((signed char)-15)) && (RH_da<((signed char)15))) {
        //lateral sweep ends after debounce timeout & jerk below threshold
        changechord = 0;                 
      }                 
      else if ((changechord == -1) && (debounce_timer == 0) && 
          (RH_da>((signed char)-15)) && (RH_da<((signed char)15))) {
        //lateral sweep ends
        changechord = 0;              
      }
      if ((Rstomp_timer == 0) && (RF > STOMP_THRESH))  {
        //stomp, play chord
        Rstomp = 1;
        Rstomp_timer = DEBOUNCE_TIME;
      }                        
      if ((Lstomp_timer == 0) && (LF > STOMP_THRESH))  {
        //stomp, set up note to add to chord
        Lstomp_timer = DEBOUNCE_TIME;
        third = LH>>4;
      }   
      if (Rstomp == 1)  {
        send_allnotesoff();
        play_chord(((unsigned long)receive_frame[RF_X])<<3);
        Rstomp = 0;
      }                 
    }

  }
  sampling = 0;

}

/****************************************************************************/
void initialize(void) {
  unsigned char i;
  DDRD.7 = 1;
  DDRA = 0xFF;
  PORTA = 0;
  init_midi();          //Initialize MIDI (USART)
  init_spi();
  RF_init_spi();        //Initialize transceiver SPI
  set_transceiver_clock();
  RF_init_receiver();   //Get transceiver in proper mode
  PORTD.7 = 0;
  sample_timer = SAMPLE_TIMEOUT;
  TCCR0A = 0b00000010;  //OC0A & OC0B disconnected, WGM set up for CTC mode
  TCCR0B = 0b00000011;  //Timer set up to osc/64... count to 125 for 1 ms
  OCR0A = 125;
  TIMSK0 = 0b00000010;  //Interrupt on compare match 
  Lstomp = 0;
  Rstomp = 0;
  note_index = 0;   
  changechord = 0;
  chord = 85;
  chord_timer = 0;
  rev_note = 0;  
  calibration = 0;
  debounce_timer = 0;
  third = 3;
  Lstomp_timer = 0;   
  Rstomp_timer = 0;
  for (i=0;i<4;i++)  {
    note_queue[i] = 0;
    note_duration[i] = 0; 
  }                  
  note_timer = 5;
  //Enable interrupts
  #asm
    sei
  #endasm
}

/****************************************************************************/
void main(void)  {
  initialize();
    
  while(1)  {
    if (sample_timer == 0)  {
      sample_timer = SAMPLE_TIMEOUT;
      sample();
    }
    if (note_timer == 0)  {
      notes_off();
      note_timer = 10;
    }
    if (chord_timer == 0)  {
      if ((chord == 0) && (changechord < (signed char)0))
        chord = 127;
      else  //adjust chord to be played if lateral sweep is going on
        chord = (unsigned char)((signed char)chord+(signed char)changechord);
      if (chord > 127)
        chord = 0;
      chord_timer = CHORD_TIMEOUT;
    }  
  }

}

/****************************************************************************/