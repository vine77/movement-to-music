/*****************************************************************************
 * receiver_linked.c
 * Lab 6: Final Project
 * ECE 476: Digital Systems Design Using Microcontrollers
 * Cornell University
 * April 2007
 * Andrew Godbehere (abg34) and Nathan Ward (njw23)
 ****************************************************************************/


/****************************************************************************/
#include <mega644.h>
#include <at86rf230.h>
#include <midi.h>

#define SAMPLE_TIMEOUT 15

unsigned char sample_timer;

/****************************************************************************/
interrupt [TIM0_COMPA] void ms_timer(void)  {
  if (sample_timer > 0) sample_timer--;
}

/****************************************************************************/
void sample(void) {
  unsigned char delay;
  RF_rx_to_tx();                           //get radio ready to tx
  tx_frame_length = 1;
  transmit_frame[0] = DATA_REQ;
  RF_download_frame();                     //get data ready for tx
  RF_transmit_frame();                     //tx
  RF_wait_for_transmit();                  //returns after tx complete
  RF_tx_to_rx();                           //get ready to rx
  RF_clear_IRQ();
  delay_us(100);
  delay = RF_receiver_listen_timeout(40);  //listen for 10ms  
  if (delay != 0)  {                       //we have received something
    PORTD.7 = ~PORTD.7;
    RF_upload_frame();
    send_midi(1,receive_frame[0]);
    send_midi(2,receive_frame[1]);
    send_midi(3,receive_frame[2]);
    send_midi(4,receive_frame[3]);
    send_midi(5,receive_frame[4]);
    send_midi(6,receive_frame[5]);
    send_midi(7,receive_frame[6]);
    send_midi(8,receive_frame[7]);
    send_midi(9,receive_frame[8]);
    send_midi(10,receive_frame[9]);
    send_midi(11,receive_frame[10]);
    send_midi(12,receive_frame[11]);
    send_midi(13,(LQI>>1));
  }
}

/****************************************************************************/
void initialize(void) {
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
  TIMSK0 = 0b00000010;  //Interrupt on compare match A

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
  }

}

/****************************************************************************/