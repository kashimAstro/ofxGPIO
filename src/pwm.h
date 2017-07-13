#ifndef RPIPWM1_H
    #define PRIPWM1_H
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
/***********************************************************************
 * Author: Hussam al-Hertani (Hertaville.com)
 * Others are free to modify and use this code as they see fit so long as they
 * give credit to the author.
 * 
 * The author is not liable for any kind of damage caused by this software. 
 * 
 * Acknowledgements: This 'C++' class is based on 'C' code available from :
 * - code from http://elinux.org/RPi_Low-level_peripherals 
 * - http://www.raspberrypi.org/phpBB3/viewtopic.php?t=8467&p=124620 for PWM initialization
 * - frank's code...http://www.frank-buss.de/raspberrypi/pwm.c
 * - Gertboard's C source code 
 * 
 * The rpiPWM1 class provides a direct memory mapped (register-based)
 * interface to the PWM1 hardware on the Raspberry Pi's BCM2835 SOC.
 * The BCM2835 SOC was two PWM subsystems, PWM1 & PWM2. This code will 
 * enable access to the PWM1 subsystem which outputs the PWM signal on
 * GPIO18 (ALT5). 
 * 
 * The class enables setting the Frequency (Max 19.2MHz), PWM resolution(4095),
 * DutyCycle and PWM Mode to be used. The Duty Cycle can be set as a 
 * percentage (setDutyCycle() or setDutyCycleForce()) or as a  function 
 * of the PWM Resoultion (setDutyCycleCount())
 * 
 * Two PWM modes exist: 
 *  - MSMODE - This is the traditional PWM Mode i.e. if PWM Resolution 
 *             (counts) is 1024 and the dutyCycle (Pulse on time) is 512 (in counts or 50%)
 *             then the waveform would look like:
 *             |||||||||||||||||_________________
 *             MSMODE is ideal for servos and other applications that 
 *             require classical PWM waveforms
 * - PWMMODE - Is a slightly modified version of the traditional PWM Mode 
 *             described above. The duty cycle or ON time is still unchanged
 *             within the period but is distributed across the entire period instead
 *             on being concentrated in the first part of the period..i.e.if PWM Resolution 
 *             (counts) is 1024 and the dutyCycle (Pulse on time) is 512 (in counts or 50%)
 *             then the waveform would look like:     
 *             |_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_|_
 *             This mode is ideal if you want to pass the signal through 
 *             a low pass filter to obtain an analog signal equivalent to the . The even 
 *             distibution of the ON time through the entire period 
 *             significantly reduces ripple caused by using a simple RC
 *             low pass filter     
 *
 * When setting the frequency via the constructor or 'setFrequency' method, one is strictly
 * requesting a particular frequency. The code will do its best to get as close as possible to 
 * the requested frequency but it is likely to not create a PWM at the exact requested Frequency.
 * As an example say that we want to create a PWM waveform with a resolution of 256 counts (8-bit)
 * and a frequency of 8KHz....We get the divisor using the following algorithm
 *
 * Waveform  period = 1 / 8KHz = 0.125ms
 * Duration of a single count = period/256 = 0.125ms / 256 = 0.488us
 * Frequency of a single count = 1 / Duration of a single count = 1 / 0.488us = 2.048MHz
 * Divisor value = floor (PWM Clock Frequency / Frequency of a single count) = floor (19.2MHz / 2.048MHz) = floor(9.375) = 9
 *
 * With a Divisor of 9 Actual Waveform Frequency = 1/((1/(19.2MHz/9))*256) = 8.333 KHz
 *
 * The actual Frequency will generally deviate further from the desired frequency as the count value (PWM resolution)
 * increases i.e. As an example say that we want to create a PWM waveform with a resolution of 1024 counts (10-bit)
 * and the same frequency as the above example:
 *
 * Waveform  period = 1 / 8KHz = 0.125ms
 * Duration of a single count = period/1024 = 0.125ms / 1024 = 122.070ns
 * Frequency of a single count = 1 / Duration of a single count = 1 / 122.070ns = 8.192MHz
 * Divisor value = floor (PWM Clock Frequency / Frequency of a single count) 
 *               = floor (19.2MHz / 8.192MHz) = floor(2.34) = 2
 *
 * With a Divisor of 2, Actual Waveform Frequency = 1/((1/(19.2MHz/2))*1024) = 9.375KHz
 * 
 * DIVISOR MUST BE AT LEAST 2....SO PICK YOUR COUNT AND DESIRED FREQUENCY VALUES CAREFULLY!!!!! 
 * i.e MAXIMUM FREQUENCY FOR 10-BIT RESOLUTION (COUNT=1024) IS 9.375KHz
 *  &  MAXIMUM FREQUENCY FOR 8-BIT RESOLUTION (COUNT=256) IS 37.5KHz
 *
 * WARNING:    The RPI uses the PWM1 subsystem to produce audio. As such
 *             please refrain from playing audio on the RPI while this code 
 *             is running.
 * *********************************************************************/
class rpiPWM1 {

public:
  rpiPWM1();
  // default constructor configures GPIO18 for PWM and Frequency 1000Hz,
  // PWM resolution (counts) 256, Duty Cycle 50% and PWM mode is 'PWMMODE'
  rpiPWM1(double Hz, unsigned int cnts, double duty,  int m);
  //overloaded constructor..allows user to set initial values for Frequency,
  //PWM resolution, Duty Cycle and PWM mode.
  ~rpiPWM1();
  // Destructor....safely releases all mapped memory and puts all used peripherals
  // (PWM clock, PWM peripheral and GPIO peripheral in their initial states
  unsigned int setFrequency(const double &hz);
  // Sets Frequency and reinitializes PWM peripheral
  unsigned int setCounts(const unsigned int &cnts);
  // Sets PWM resolution (counts) and reinitializes PWM peripheral
  unsigned int setDutyCycle(const double &duty);
  // Sets Duty Cycle as a Percentage (Fast)
  unsigned int setDutyCycleCount(const unsigned int &cnts );
  // Sets Duty Cycle as a count value (Fast) i.e. if counts is 1024
  // and 'duty' is set to 512, a 50% duty cycle is achieved
  unsigned int setDutyCycleForce(const double &duty, const  int &m);
  // disables PWM peripheral first,
  //Sets Duty Cycle as a Percentage and PWM mode...
  // then enables PWM peripheral
  unsigned int setMode(const  int &m);
  // sets PWM mode...calls 'setDutyCycleForce()'
  
  
  double getFrequency() const;
  // returns current Frequency of PWM waveform
  double getDutyCycle() const;
  // returns current DutyCycle (as a %) of PWM waveform
  int getCounts() const;
  // returns PWM resolution 
  int getDivisor() const;
  //returns Divisor value used to set the period per count
  //as a function of the default PWM clock Frequency of 19.2MHz
  int getMode() const;
  //returns (1) if current PWM mode is 'PWMMODE' or (2) if current PWM mode
  //is 'MSMODE'
  
  //Public constants
  static const int PWMMODE = 1;
  static const int MSMODE = 2;
  //Two PWM modes
  static const int ERRFREQ = 1;
  static const int ERRCOUNT = 2;
  static const int ERRDUTY = 3;
  static const int ERRMODE = 4;
  //Error Codes
  
private:
  //Private constants
  static const int BCM2708_PERI_BASE = 0x20000000;
  static const int PWM_BASE = (BCM2708_PERI_BASE + 0x20C000); /* PWM controller */
  static const int CLOCK_BASE = (BCM2708_PERI_BASE + 0x101000); /* Clock controller */
  static const int GPIO_BASE = (BCM2708_PERI_BASE + 0x200000); /* GPIO controller */
  //Base register addresses
  static const int PWM_CTL = 0;
  static const int PWM_RNG1 = 4;
  static const int PWM_DAT1 = 5;
  static const int PWMCLK_CNTL= 40;
  static const int PWMCLK_DIV = 41;
  // Register addresses offsets divided by 4 (register addresses are word (32-bit) aligned 
  static const int BLOCK_SIZE = 4096;
  // Block size.....every time mmap() is called a 4KB 
  //section of real physical memory is mapped into the memory of
  //the process

  
  volatile unsigned *mapRegAddr(unsigned long baseAddr);
  // this function is used to map physical memory 
  void configPWM1Pin();
  //this function sets GPIO18 to the alternat function 5 (ALT5)
  // to enable the pin to output the PWM waveforms generated by PWM1
  void configPWM1();
  //This function is responsible for the global configuration and initialixation
  //of the the PWM1 peripheral
  
  double frequency; // PWM frequency
  double dutyCycle; //PWM duty Cycle (%)
  unsigned int counts; // PWM resolution
  unsigned int divisor; // divisor value
  int mode;  // PWM mode
  volatile unsigned *clk, *pwm, *gpio; // pointers to the memory mapped sections 
  //of our process memory 
  
};
#endif
