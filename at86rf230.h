/*****************************************************************************
 * at86rf230.h
 * Lab 6: Final Project
 * ECE 476: Digital Systems Design Using Microcontrollers
 * Cornell University
 * April 2007
 * Andrew Godbehere (abg34) and Nathan Ward (njw23)
 ****************************************************************************/


/****************************************************************************/
#ifndef _DELAY_INCLUDED_
    #include <delay.h>
#endif

#ifndef _AT86RF230_INCLUDED_
    #define _AT86RF230_INCLUDED_
#endif

#ifndef _SPI_INCLUDED_
    #include <spi.h>
#endif

/****************************************************************************/
//List of Transceiver Registers
#define TRX_STATUS       0x01
#define TRX_STATE        0x02
#define TRX_CTRL_0       0x03
#define PHY_TX_PWR       0x05
#define PHY_RSSI         0x06
#define PHY_ED_LEVEL     0x07
#define PHY_CC_CCA       0x08
#define CCA_THRES        0x09
#define IRQ_MASK         0x0E
#define IRQ_STATUS       0x0F
#define VREG_CTRL        0x10
#define BATMON           0x11
#define XOSC_CTRL        0x12
#define FTN_CTRL         0x18
#define PLL_CF           0x1A
#define PLL_DCU          0x1B
#define PART_NUM         0x1C
#define VERSION_NUM      0x1D
#define MAN_ID_0         0x1E
#define MAN_ID_1         0x1F
#define SHORT_ADDR_0     0x20
#define SHORT_ADDR_1     0x21
#define PAN_ID_0         0x22
#define PAN_ID_1         0x23
#define IEEE_ADDR_0      0x24
#define IEEE_ADDR_1      0x25
#define IEEE_ADDR_2      0x26
#define IEEE_ADDR_3      0x27
#define IEEE_ADDR_4      0x28
#define IEEE_ADDR_5      0x29
#define IEEE_ADDR_6      0x2A
#define IEEE_ADDR_7      0x2B
#define XAH_CTRL         0x2C
#define CSMA_SEED_0      0x2D
#define CSMA_SEED_1      0x2E

//List of Transceiver States
#define NOP              0x00
#define TX_START         0x02
#define FORCE_TRX_OFF    0x03
#define RX_ON            0x06
#define TRX_OFF          0x08
#define PLL_ON           0x09
#define RX_AACK_ON       0x22
#define TX_ARET_ON       0x25

//SPI data direction register (DDR)
#define DDR_SS   DDRB.4  //Slave Select
#define DDR_MOSI DDRB.5  //Master Out - Slave In
#define DDR_MISO DDRB.6  //Master In - Slave Out
#define DDR_SCLK DDRB.7  //SPI Clock
//SPI chip select (CS)
#define RF230_SEL        PORTC.3
#define DDR_RF230_SEL    DDRC.3
//GPIO (General purpose input output) interface
#define RF230_IRQ        PINC.0
#define DDR_RF230_IRQ    DDRC.0
#define RF230_SLP_TR     PORTC.1
#define DDR_RF230_SLP_TR DDRC.1
#define RF230_RESET      PORTC.2
#define DDR_RF230_RESET  DDRC.2

//IRQ status masks
#define IRQ_BAT_LOW      0x80  //Battery low signal
#define IRQ_TRX_UR       0x40  //FIFO underrun signal
#define IRQ_TRX_END      0x08  //End of frame (transmit and receive)
#define IRQ_RX_START     0x04  //Beginning of receive frame
#define IRQ_PLL_UNLOCK   0x02  //PLL goes from lock to unlock state
#define IRQ_PLL_LOCK     0x01  //PLL goes from unlock to lock state

//Protocol Commands
#define PING             0xA1  //See if there is a transmitter in range
#define DATA_REQ         0xA5  //Request data from transmitter

//energy detection threshold
#define ED_THRESH        0x10

/****************************************************************************/
//Function Prototypes
unsigned char RF_RX_channel_scan(void);
unsigned char RF_TX_channel_scan(void);
void init_spi(void);
void set_transceiver_clock(void);
void RF_init_spi(void);
unsigned char RF_read_register(unsigned char address);
void RF_write_register(unsigned char address, unsigned char data);
void RF_init_transmitter(void);
void RF_transmit_test(void);
void RF_init_receiver(void);
void RF_receive_test(void);
void RF_download_frame(void);
void RF_transmit_frame(void);
void RF_receiver_listen(void);
void RF_upload_frame(void);
unsigned char RF_update_IRQ_status(void);
unsigned char RF_transmit_done(void);
unsigned char RF_receiver_listen_timeout(unsigned char loop_count);
unsigned char RF_TX_channel_scan(void);
void RF_TX_sync(void);
void RF_tx_to_rx(void);
void RF_rx_to_tx(void);
void RF_RX_sync(void);

/****************************************************************************/
//Global Variables to use for interfacing
unsigned char transmit_frame[20];  //User code fills transmit_frame
unsigned char receive_frame[20];   //User code reads receive_frame
unsigned char LQI;                 //User may use LQI after receiving frame
unsigned char tx_frame_length;     //User can set frame length before transmit
unsigned char rx_frame_length;     //Read frame length while receiving
unsigned char curr_IRQ_status;

/****************************************************************************/
void RF_clear_IRQ(void)  {
  curr_IRQ_status = RF_read_register(IRQ_STATUS);
  curr_IRQ_status = 0;
}

/****************************************************************************/
//Function determines if channel is clear or not using CCA
//CCA = clear channel assessment
//channel parameter must be between 11 and 26
//Returns 0 if channel is busy and 1 if channel is clear
unsigned char RF_CCA(unsigned char channel)  {
  unsigned char status = 0;
  if ((channel < 11) || (channel > 26)) return 0;  //invalid input
  channel = (channel | 0b10000000); //Set bit 7 to 1 to start CCA check
  RF_write_register(PHY_CC_CCA,channel);
  delay_us(140);
  status = RF_read_register(TRX_STATUS);
  if ((status&0b01000000) != 0) return 1;  //channel is available
  else return 0;
}

/****************************************************************************/
//Function scans for clear channel using CCA. Sets channel to best option
//for reception. Need another function to transmit beacon frame over that 
//channel, listen for a response. This function returns 0 if there is no good 
//channel, or it returns the value of the channel with the strongest signal.
unsigned char RF_RX_channel_scan(void)  {
  unsigned char i = 0;
  unsigned char status;
  for (i=16;i<=26;i++)  {
    RF_write_register(PHY_CC_CCA,(0b10000000 | i));  
    //see if channel i is available
    do {
      status = RF_read_register(TRX_STATUS);
    } while((status&0b10000000) == 0);
    if ((status&0b01000000) == 0)  return i;  //return clear channel
  }
  for (i = 11; i<16; i++)  {
    RF_write_register(PHY_CC_CCA,(0b10000000 | i));  
    //see if channel i is available
    do {
      status = RF_read_register(TRX_STATUS);
    } while((status&0b10000000) == 0);
    if ((status&0b01000000) != 0)  return i;  //return clear channel
  }
  return 0;
}

/****************************************************************************/
//Function scans for channel with highest signal quality above a certain
//threshold, returns best channel. Need another function to listen for beacon 
//frame, respond with acknowledgement frame.
unsigned char RF_TX_channel_scan(void)  {
  unsigned char max_channel_strength = 0;
  unsigned char max_channel = 0;
  unsigned char curr_channel_strength;
  unsigned char i;

  for (i=11;i<=26;i++)  {
    RF_write_register(PHY_CC_CCA,i);  //change to specific channel
    delay_us(400);  //wait for channel change to complete
    RF_write_register(PHY_ED_LEVEL,0x00);  //start ED calculation
    delay_us(130);  //wait for conversion to complete
    curr_channel_strength = RF_read_register(PHY_ED_LEVEL);
    if ((curr_channel_strength > ED_THRESH) && 
        (curr_channel_strength > max_channel_strength))  {
      max_channel_strength = curr_channel_strength;
      max_channel = i;
    }
  }
  return max_channel;
}

/****************************************************************************/
void RF_TX_sync(void)  {
  unsigned char channel;
  while (1)  {   //keep searching until a receiver is found
    do  {
      //find best channel, if any available
      channel = RF_TX_channel_scan();
    } while(channel == 0);
    RF_write_register(PHY_CC_CCA,channel);  //switch to channel
    delay_us(200);
    RF_tx_to_rx();  //switch to reception mode
    delay_us(200);
    if (RF_receiver_listen_timeout(50) == 1)  break;  
    //wait for a short time for a frame to be received
  }
  RF_rx_to_tx();
  delay_us(200);
  tx_frame_length = 1;
  transmit_frame[0] = 0xAA;
  RF_download_frame();
  RF_transmit_frame();
}

/****************************************************************************/
void RF_RX_sync(void)  {
  unsigned char channel,i;
  do  {
    channel = RF_RX_channel_scan();
  } while(channel==0);
  RF_write_register(PHY_CC_CCA,channel);  //switch to channel
  delay_us(200);
  while (1)  {
    RF_rx_to_tx();  //switch to transmission mode
    delay_us(200);
    tx_frame_length = 10;
    for (i=0;i<10;i++)  {
      transmit_frame[i] = 0xAA;
    }
    RF_download_frame();
    RF_transmit_frame();
    RF_tx_to_rx();  //switch to reception mode
    delay_us(200);
    if (RF_receiver_listen_timeout(50) == 1) break;
  }
}

/****************************************************************************/
unsigned char RF_receiver_listen_timeout(unsigned char loop_count)  {
  do {
    if (RF230_IRQ != 0)  {
      curr_IRQ_status = RF_read_register(IRQ_STATUS);
    }
    delay_us(250);
    loop_count--;
  } while (((curr_IRQ_status & IRQ_TRX_END) == 0 )&&((loop_count) > 0));
  if ((curr_IRQ_status&IRQ_TRX_END) != 0) {
    curr_IRQ_status = 0;
    return (loop_count+1);
  }
  curr_IRQ_status = 0;
  return loop_count;
}

/****************************************************************************/
void init_spi(void) {
  //Set up SPI I/O data direction
  DDR_MOSI = 1;
  DDR_MISO = 0;
  DDR_SCLK = 1;
  DDR_SS = 1;  //SS must be configured as output to set MCU as SPI master
  PORTB.4 = 0;

  //Set up SPI Control Registers
  //Bit 7 - Interrupt Enable SPIE=0 -> no ISR
  //Bit 6 - SPI Enable SPE=1 -> enable spi
  //Bit 5 - Data Order DORD=0 -> msb first
  //Bit 4 - Master/Slave Select MSTR=1 ->MCU is SPI master
  //Bit 3 - Clock Polarity CPLO=0 (for the transceiver initially)
  //Bit 2 - Clock Phase CPHA=0 (for the transceiver initially)
  //Bits 1:0 - SPR1, SPR0: SPI Clock Rate Select 1 and 0
  //SPR1:SPR0=00 along with SPI2X=1 sets SCK to f_osc/2 = 8MHz/2 = 4MHz
  SPCR0 = 0b01010000;  //SPI Control Register
  SPSR0 = 1;           //SPI Status Register (SPI2X)

}

/****************************************************************************/
void set_transceiver_clock(void) {
  //Set the clock polarity and phase for the transceiver if other slaves
  //(with different clock settings) are also being used by the MCU
  SPCR0 = 0b01010000;
  SPSR0 = 1;
  //SPCR0 &= 0b11110111;  //Bit 3 – Clock Polarity CPLO=0
  //SPCR0 &= 0b11111011;  //Bit 2 – Clock Phase CPHA=0
}

/****************************************************************************/
void RF_init_spi(void) {
  //Set up GPIO data directions
  DDR_RF230_IRQ = 0;
  DDR_RF230_SLP_TR = 1;
  DDR_RF230_RESET = 1;
  DDR_RF230_SEL = 1;

  RF230_SEL = 1;  //Initialize chip select signal high
  RF230_RESET = 1;
  RF230_SLP_TR = 0;

}

/****************************************************************************/
//2 byte SPI transmit. Information in second byte is thrown away, just
//transmit junk data to receive byte.
unsigned char RF_read_register(unsigned char address) {
  unsigned char junk;
  RF230_SEL = 0;
  //Address should only be 6 bits. MSB should be 1, bit 6 should be 0.
  //Writing to SPDR0 starts transmission
  SPDR0 = 128 + (address & 0b00111111);
  while((SPSR0&0x80) == 0); //Wait for transfer to complete
  junk = SPDR0;
  //Start next transmission, transmit junk, get back data from register
  SPDR0 = 0x00;
  while((SPSR0&0x80) == 0); //Wait for transfer to complete
  RF230_SEL = 1;
  return SPDR0; //Return contents of register in transceiver
}

/****************************************************************************/
//2 byte SPI transmit. Information in second byte is data to write to register
void RF_write_register(unsigned char address, unsigned char data) {
  unsigned char junk;
  RF230_SEL = 0;
  //First 2 bits are 11, rest is address. Start transmitting command
  SPDR0 = 192 + (address & 0b00111111);
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  junk = SPDR0;
  SPDR0 = data;
  while ((SPSR0&0x80) == 0);  //Wait for transfer to complete
  RF230_SEL = 1;
}

/****************************************************************************/
//Initialize basic one-way transmitter
void RF_init_transmitter(void) {
  //RF_write_register(TRX_CTRL_0,
  //Should write to TRX_CTRL_0 register to set output current and
  //clockspeed settings.
  RF230_RESET = 0;
  #asm
    nop
    nop
    nop
    nop
    nop
  #endasm
  RF230_RESET = 1;
  RF_write_register(TRX_CTRL_0,0b01001000);
  delay_us(800);
  //enable ONLY the TRX_done interrupt
  RF_write_register(IRQ_MASK,0b00001000);
  delay_us(200);
  RF_write_register(PHY_TX_PWR,0);  //reduced power on transmit
  delay_us(200);
  RF_write_register(PHY_CC_CCA,11);  //channel 11
  delay_us(200);
  RF_write_register(TRX_STATE,FORCE_TRX_OFF);
  delay_us(1880);
  RF_write_register(TRX_STATE,PLL_ON);
  delay_us(200);
  RF_write_register(TRX_CTRL_0,0b01001000);
  delay_us(800);
  RF_write_register(TRX_STATE,FORCE_TRX_OFF);
  delay_us(1880);
  RF_write_register(TRX_STATE,PLL_ON);
  delay_us(200);
}

/****************************************************************************/
void RF_tx_to_rx(void)  {
  RF_write_register(TRX_STATE,FORCE_TRX_OFF);
  delay_us(1880);
  RF_write_register(TRX_STATE,RX_ON);
  delay_us(200);
}

/****************************************************************************/
void RF_rx_to_tx(void)  {
  RF_write_register(TRX_STATE,FORCE_TRX_OFF);
  delay_us(1880);
  RF_write_register(TRX_STATE,PLL_ON);
  delay_us(200);
}

/****************************************************************************/
//Transmit once per second... call this once every second
void RF_transmit_test(void) {
  unsigned char i;
  RF_write_register(TRX_STATE,PLL_ON);
  RF230_SEL = 0;
  SPDR0 = 0b01100000;  //Frame transmit mode
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  SPDR0 = 100;  //Frame length
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  for (i=0;i<100;i++) {
    SPDR0 = i;
    while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  }
  RF230_SEL = 1;

  RF230_SLP_TR = 1;  //Signal to transmit frame
  #asm
    nop
    nop
    nop
    nop
    nop
  #endasm
  RF230_SLP_TR = 0;
  do {  //Loop until end of transmit frame, when we break out of loop
    if (RF230_IRQ != 0) {
      //Get the status of the IRQ
      curr_IRQ_status = RF_read_register(IRQ_STATUS);
      PORTA = curr_IRQ_status;
    }
    //Loop until done done transmitting frame
  } while ((curr_IRQ_status & IRQ_TRX_END) == 0);

}

/****************************************************************************/
void RF_init_receiver(void) {
  RF230_RESET = 0;
  #asm
    nop
    nop
    nop
    nop
    nop
  #endasm
  RF230_RESET = 1;
  RF_write_register(TRX_CTRL_0,0b01001000);
  delay_us(800);
  //enable ONLY the TRX_done interrupt
  RF_write_register(IRQ_MASK,0b00001000);
  delay_us(200);
  RF_write_register(TRX_STATE,FORCE_TRX_OFF);
  delay_us(1880);
  RF_write_register(TRX_STATE,RX_ON);
  delay_us(200);
}

/****************************************************************************/
void RF_receive_test(void) {
  //Put transceiver in listen mode
  //Wait for IRQ indicating end of frame
  //Upload frame, digest
  //Done, start again immediately
  unsigned char length,LQI;
  unsigned char junk = 0;
  unsigned char frame[128];
  unsigned char index = 0;

  do {
    if (RF230_IRQ != 0)  {
      curr_IRQ_status = RF_read_register(IRQ_STATUS);
    }
    //Loop until done receiving frame, then we can start uploading
  } while ((curr_IRQ_status & IRQ_TRX_END) == 0);

  RF230_SEL = 0;
  SPDR0 = 0b00100000;  //Frame receive mode
  while((SPSR0&0x80)==0);  //Wait for frame transfer to complete
  SPDR0 = junk;  //Transmit a junk byte to receive a byte of frame
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  length = SPDR0;
  while (length>0)  {
    SPDR0 = junk;
    while((SPSR0&0x80) == 0);  //Wait for transfer to complete
    frame[index++]=SPDR0;  //Get byte of frame
    length--;
  }
  SPDR0 = junk;
  while((SPSR0&0x80) == 0);
  LQI = SPDR0;  //LQI is a byte between 0 (bad) and 255(excellent)
  PORTA = LQI;
  RF230_SEL = 1;
}

/****************************************************************************/
//Transceiver must be in appropriate state before calling this
void RF_download_frame(void) {
  unsigned char i;
  RF_write_register(TRX_STATE,PLL_ON);
  RF230_SEL = 0;
  SPDR0 = 0b01100000;  //Frame transmit mode
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  SPDR0 = tx_frame_length;  //Frame length
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  for (i=0;i<tx_frame_length;i++) {
    SPDR0 = transmit_frame[i];
    while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  }
  RF230_SEL = 1;
}

/****************************************************************************/
//Function must be called AFTER RF_download_frame() and when Transceiver is
//in PLL_ON state.
void RF_transmit_frame(void) {
  //TODO: First test to make sure transceiver is in proper state.
  RF230_SLP_TR = 1;   //Signal to transmit frame
  #asm
    nop
    nop
    nop
    nop
    nop
  #endasm
  RF230_SLP_TR = 0;
}

/****************************************************************************/
//Call this function when in Receiver mode. When this function returns, it is
//time to start receiving.
void RF_receiver_listen(void) {
  do {
    if (RF230_IRQ != 0)  {
      curr_IRQ_status = RF_read_register(IRQ_STATUS);
    }
    //if ((IRQ_status & IRQ_TRX_END) != 0) break;
    //Loop until done receiving frame, then we can start uploading
  } while ((curr_IRQ_status & IRQ_TRX_END) == 0);
  curr_IRQ_status = 0;
}

/****************************************************************************/
unsigned char RF_quick_listen(void)  {
  unsigned char returnval = 0;
  if (RF230_IRQ != 0) {
    curr_IRQ_status = RF_read_register(IRQ_STATUS);
    if ((curr_IRQ_status & IRQ_TRX_END) != 0) returnval = 1;
    else returnval = 0;
  }
  curr_IRQ_status = 0;
  return returnval;
}

/****************************************************************************/
void RF_upload_frame(void) {
  unsigned char i;
  RF230_SEL = 0;
  SPDR0 = 0b00100000;  //Frame receive mode
  while((SPSR0&0x80)==0);  //Wait for transfer to complete
  SPDR0 = 0x00;  //Transmit a junk byte to receive a byte of frame
  while((SPSR0&0x80) == 0);  //Wait for transfer to complete
  rx_frame_length = SPDR0;
  i = 0;
  while (i<rx_frame_length) {
    SPDR0 = 0x00;
    while((SPSR0&0x80) == 0);  //Wait for transfer to complete
    receive_frame[i++]=SPDR0;  //Get byte of frame
  }
  SPDR0 = 0x00;
  while((SPSR0&0x80) == 0);
  LQI = SPDR0;  //LQI is a byte between 0 (bad) and 255(excellent)
  RF230_SEL = 1;
}

/****************************************************************************/
unsigned char RF_update_IRQ_status(void) {
  if (RF230_IRQ == 1) {
    curr_IRQ_status = RF_read_register(IRQ_STATUS);
    return 1;
  }
  else return 0;
}

/****************************************************************************/
unsigned char RF_transmit_done(void)  {
  RF_update_IRQ_status();
  if ((curr_IRQ_status & IRQ_TRX_END) != 0) return 1;  
  //if transmit has completed, return 1.
  else return 0;
}

/****************************************************************************/
void RF_wait_for_transmit(void)  {
  do {  //Loop until end of transmit frame, when we break out of loop
    if (RF230_IRQ != 0) {
      //Get the status of the IRQ
      curr_IRQ_status = RF_read_register(IRQ_STATUS);
      //PORTA = curr_IRQ_status;
    }
  } while ((curr_IRQ_status & IRQ_TRX_END) == 0);
  curr_IRQ_status = 0;
}

/****************************************************************************/