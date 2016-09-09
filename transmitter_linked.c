/*****************************************************************************
 * transmitter_linked.c
 * Lab 6: Final Project
 * ECE 476: Digital Systems Design Using Microcontrollers
 * Cornell University
 * April 2007
 * Andrew Godbehere (abg34) and Nathan Ward (njw23)
 ****************************************************************************/


//This program will periodically take a sample from the accelerometers and 
//then listen for a short while for a command from the base station.

/****************************************************************************/
#include <mega644.h>
#include <spi.h>
#include <at86rf230.h>
#include <kxp74.h>

#define SAMPLE_TIMEOUT 10

unsigned char sample_timer;

/****************************************************************************/
interrupt [TIM0_COMPA] void ms_timer(void)  {  //Triggers once per ms
  if (sample_timer > 0) sample_timer--;
}

/****************************************************************************/
void sample(void)  {
  set_sensor_clock();  //Set clock phase & polarity for accelerometers
  tx_frame_length = 0;
  transmit_frame[tx_frame_length++] = get_sensor(1, CONVERT_XAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(1, CONVERT_YAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(1, CONVERT_ZAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(2, CONVERT_XAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(2, CONVERT_YAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(2, CONVERT_ZAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(3, CONVERT_XAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(3, CONVERT_YAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(3, CONVERT_ZAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(4, CONVERT_XAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(4, CONVERT_YAXIS);
  delay_us(1);
  transmit_frame[tx_frame_length++] = get_sensor(4, CONVERT_ZAXIS);
  delay_us(1);
  set_transceiver_clock();
  if (RF_quick_listen() == 1)  {
    RF_upload_frame();
    if (receive_frame[0] == DATA_REQ)  {
      PORTD.7 = ~PORTD.7;
      RF_rx_to_tx();
      RF_download_frame();
      RF_transmit_frame();
      RF_wait_for_transmit();
    }
  }
  receive_frame[0] = 0;
  RF_tx_to_rx();
}

/****************************************************************************/
void initialize(void) {
  DDRD = 0xFF;
  DDRA = 0xFF;
  PORTA = 0x00;
  PORTD.7 = 1;
  sample_timer = 0;

  init_spi();               //Initialize general SPI settings
  init_sensor_spi();        //Initialize accelerometer SPI
  set_sensor_clock();
  init_sensors();           //Get accelerometers in proper mode
  RF_init_spi();            //Initialize transceiver SPI
  delay_us(100);
  set_transceiver_clock();
  RF_init_transmitter();    //Get transceiver in proper mode
  //RF_tx_to_rx();  //transceiver should listen first

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
  delay_ms(2000);
  initialize();

  while(1)  {
    if (sample_timer == 0)  {
      sample_timer = SAMPLE_TIMEOUT;
      sample();
    }
  }

}

/****************************************************************************/