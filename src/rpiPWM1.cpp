#include "rpiPWM1.h"

//Need to do this to be able to access these constants
//Private constants
const int rpiPWM1::BCM2708_PERI_BASE;
const int rpiPWM1::PWM_BASE;/* PWM controller */
const int rpiPWM1::CLOCK_BASE; /* Clock controller */
const int rpiPWM1::GPIO_BASE; /* GPIO controller */
const int rpiPWM1::PWM_CTL ;
const int rpiPWM1::PWM_RNG1;
const int rpiPWM1::PWM_DAT1;
const int rpiPWM1::PWMCLK_CNTL;
const int rpiPWM1::PWMCLK_DIV;
const int rpiPWM1::BLOCK_SIZE;
//Public constants
const int rpiPWM1::PWMMODE;
const int rpiPWM1::MSMODE;
const int rpiPWM1::ERRFREQ;
const int rpiPWM1::ERRCOUNT;
const int rpiPWM1::ERRDUTY;
const int rpiPWM1::ERRMODE;


/***********************************************************************
 * rpiPWM1::rpiPWM1()
 * This is the Default constructor. First, it mmaps the registers in 
 * Physical memory responsible for configuring GPIO, PWM and the PWM clock.
 * It then sets the frequency to 1KHz, PWM resolution to 256, duty 
 * cycle to 50% & pwm mode to 'PWMMODE'
 * It then calls configPWM1Pin() to configure GPIO18 to ALT5 to allow it to
 * output PWM1 waveforms. 
 * Finally  configPWM1() is called to configure the PWM1 peripheral
 ***********************************************************************/
rpiPWM1::rpiPWM1()
{
  this->clk = mapRegAddr(CLOCK_BASE);// map PWM clock registers into memory
  this->pwm = mapRegAddr(PWM_BASE); //map PWM registers into memory
  this->gpio = mapRegAddr(GPIO_BASE);// map GPIO registers into memory 
  this->frequency = 1000.0; // set frequency
  this->counts = 256; //set PWM resolution
  this->dutyCycle = 50.0; //set duty cycle
  this->mode = PWMMODE; // set pwm mode
  configPWM1Pin(); //configure GPIO18 to ALT15 (PWM output)
  configPWM1();   // configure PWM1
}

/***********************************************************************
 * rpiPWM1::rpiPWM1(double Hz, unsigned int cnts, double duty, unsigned int m)
 * This is the overloaded constructor. First, it mmaps the registers in 
 * Physical memory responsible for configuring GPIO, PWM and the PWM clock.
 * It then sets the frequency, PWM resolution, duty cycle & pwm mode as 
 * per the parameters provided.
 * 
 * It then calls configPWM1Pin() to configure GPIO18 to ALT5 to allow it to
 * output PWM1 waveforms. 
 * Finally  configPWM1() is called to configure the PWM1 peripheral
 * Parameters: - Hz (double) - Frequency
 *             - cnts (unsigned int) - PWM resolution (counts)
 *             - duty (double) - Duty Cycle as a percentage
 *             - m     (int) - PWM mode (can be either 1 for PWMMODE (rpiPWM1::PWMMODE) 
 *               or 2 for MSMODE (rpiPWM1::MSMODE) 
 ***********************************************************************/
rpiPWM1::rpiPWM1(double Hz, unsigned int cnts, double duty, int m)
{
  this->clk = mapRegAddr(CLOCK_BASE);
  this->gpio = mapRegAddr(GPIO_BASE);
  this->pwm = mapRegAddr(PWM_BASE);
  
   if( (cnts < 0) || (cnts > UINT_MAX) ) {
   printf("counts value must be between 0-%d\n",UINT_MAX);
   exit(1);
  }
  
  if ((Hz < 1e-5) || (Hz > 19200000.0f)){
    printf("frequency value must be between 0-19200000\n");
    exit(1);
  }
  
  if( (duty < 1e-5) || (duty> 99.99999) ) {
    printf("dutyCycle value must be between 0-99.99999\n");
    exit(1);
  }
  
  if( (m != PWMMODE) && (m != MSMODE) ) {
    printf("mode must be either PWMMODE(1) or MSMODE(2)\n");
    exit(1);
  }
  
  this->frequency = Hz;
  this->counts = cnts;
  this->dutyCycle = duty;
  this->mode = m;
  configPWM1Pin();
  configPWM1();  
}

/***********************************************************************
 * rpiPWM1::~rpiPWM1()
 * Destructor - Puts all Peripheral registers in their original (reset state)
 * and then unmaps the portions of memory containing to register addresses
 * for the PWM clock, PWM and GPIO peripherals
 ***********************************************************************/
rpiPWM1::~rpiPWM1(){


	//lets put the PWM peripheral registers in their original state   
	*(pwm + PWM_CTL) = 0;
	*(pwm + PWM_RNG1) = 0x20;
	*(pwm + PWM_DAT1) = 0;
    // unmap the memory block containing PWM registers
    if(munmap((void*)pwm, BLOCK_SIZE) < 0){
		perror("munmap (pwm) failed");
		exit(1);
	}
	//lets put the PWM Clock peripheral registers in their original state  
    //kill PWM clock
    *(clk + PWMCLK_CNTL) = 0x5A000000 | (1 << 5);
    usleep(10);

    // wait until busy flag is set
    while ( (*(clk + PWMCLK_CNTL)) & 0x00000080){}

    //reset divisor
    *(clk + PWMCLK_DIV) = 0x5A000000;
    usleep(10);

    // source=osc and enable clock
    *(clk + PWMCLK_CNTL) = 0x5A000011;

    // unmap the memory block containing PWM Clock registers
    if(munmap((void*)clk, BLOCK_SIZE) < 0){
		perror("munmap (clk) failed");
		exit(1);
	}
  
   //lets put the GPIO peripheral registers in their original state
   //first put it in input mode (default)
   //taken from #define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
   *(gpio+1) &= ~(7 << 24);
   //then munmap
    if(munmap((void*)gpio, BLOCK_SIZE) < 0){
		perror("munmap (gpio) failed");
		exit(1);
	}
}

/***********************************************************************
 * unsigned int rpiPWM1::setFrequency(const double &hz)
 * This function sets the PWM frequency and then reinitializes the PWM1
 * peripheral to update the frequency. The function performs a check to 
 * ensure that the PWM frequency is between 0 & 19.2MHz
 * Parameters: hz (double) - Frequency in Hz
 * Return Value: 0 if successful or rpiPWM1::ERRFREQ if frequency 
 *               parameter is invalid 
 ***********************************************************************/
 unsigned int rpiPWM1::setFrequency(const double &hz){
  unsigned int retVal = 0;
  if (hz < 1e-5 || hz > 19200000.0f){ // make sure that Frequency is valid 
	retVal = ERRFREQ; //if not return error code 
  }
  else{
	this->frequency = hz;
	configPWM1();
  }
  return retVal; // return 0 for success.....
}


/***********************************************************************
 * unsigned int rpiPWM1::setCounts(const int &cnts)
 * This function sets the PWM resolution and then reinitializes the PWM1
 * peripheral to update the PWM resolution (counts). The function performs a check to 
 * ensure that the PWM resolution is between 0 &  UINT_MAX (its a 32-bit register)
 * Parameters: cnts (unsigned int) - counts
 * Return Value: 0 if successful or rpiPWM1::ERRCOUNT if count value is invalid
 ***********************************************************************/
unsigned int rpiPWM1::setCounts(const unsigned int &cnts){
	unsigned int retVal = 0;
   
	if( (cnts < 0) || (cnts > UINT_MAX) ) {
		retVal = ERRCOUNT;
	}
  else{
    this->counts = cnts;
    configPWM1();    
  }
  return retVal;
}

/***********************************************************************
 * unsigned int rpiPWM1::setDutyCycle(const double &duty)
 * This function sets the PWM DutyCycle while the PWM peripheral is running.
 * The function performs a check to ensure that the PWM Duty Cycle is between 
 * 0 & 99.99999 %
 * Parameters: duty (double) - Duty Cycle in %
 * Return Value: 0 if successful or rpiPWM1::ERRDUTY if Duty cycle is invalid
 ****************************************************************************/
unsigned int rpiPWM1::setDutyCycle(const double &duty){
	unsigned int bitCount = 0;
	unsigned int retVal = 0;
   
	if( (duty < 1e-5) || (duty > 99.99999) ) {
		retVal = ERRDUTY;
	}
  else {
		this->dutyCycle = duty;
		bitCount = (int) ((this->dutyCycle/100.0) * this->counts);
		*(pwm + PWM_DAT1) = bitCount;  
	}
	
	return retVal;
}

/***********************************************************************
 * unsigned int rpiPWM1::setDutyCycleForce(const double &duty, unsigned int &m)
 * This function firsts stops the PWM1 peripheral, sets the PWM DutyCycle 
 * and the PWM mode and then re-enables the PWM1 peripheral in the new mode
 * The function performs a check to ensure that the PWM Duty Cycle is between 
 * 0 & 99.99999 % and that an appropriate mode is selected.
 *
 * Parameters: duty (double) - Duty Cycle in %
 *             m (int) - pwm mode (rpiPWM1::PWMMODE or rpiPWM1::MSMODE)
 * Return Value: 0 if successful or rpiPWM1::ERRDUTY if Duty cycle is invalid 
 *******************************************************************************/
unsigned int rpiPWM1::setDutyCycleForce(const double &duty, const int &m){
	int retVal = 0;
	if( (m != PWMMODE) && (m != MSMODE) ) {
		retVal = ERRMODE;
	}
	else if( (duty < 1e-5) || (duty > 99.99999) ) {
		retVal = ERRDUTY;
	}
	else{
		this->mode = m;
		this->dutyCycle = duty;
		// disable PWM & start from a clean slate
		*(pwm + PWM_CTL) = 0;
		// needs some time until the PWM module gets disabled, without the delay the PWM module crashs
		usleep(10); 
		// set the number of counts that constitute a period 
		*(pwm + PWM_RNG1) = this->counts;
		//set  duty cycle
		*(pwm + PWM_DAT1) = (int) ((this->dutyCycle/100.0) * this->counts);
		// start PWM1 in
		if(this->mode == PWMMODE) //PWM mode
			*(pwm + PWM_CTL) |= (1 << 0);
		else // M/S Mode
			*(pwm + PWM_CTL) |= ( (1 << 7) | (1 << 0) );  
		}
	return retVal;
}

/***********************************************************************
 * unsigned int rpiPWM1::setDutyCycleCount(unsigned int &dutyCycleCnts )
 * This function sets the PWM DutyCycle as a function of PWM resolution, 
 * while the PWM peripheral is running. The function performs a check to 
 * ensure that the PWM Duty Cycle count value is between 0 and count
 * Parameters: dutyCycleCnts (unsigned int) - Duty Cycle in counts
 * Return Value:0 if successful or rpiPWM1::ERRDUTY if Duty cycle is invalid 
 ***********************************************************************/
unsigned int rpiPWM1::setDutyCycleCount(const unsigned int &dutyCycleCnts ){
   unsigned int retVal = 0;
   if( (dutyCycleCnts < 0) || ( dutyCycleCnts > this->counts )) {
    retVal = ERRDUTY;
	}
	else{
		this->dutyCycle = ((dutyCycleCnts * 1.0)/ this->counts) * 100.0;
		*(pwm + PWM_DAT1) = dutyCycleCnts;
	}
	return retVal;  
}

/***********************************************************************
 * unsigned int rpiPWM1::setMode(unsigned int &m)
 * This function sets the PWM mode. The function performs a check to 
 * ensure that a valid PWM mode is requested.
 * Parameters: m (int) - pwm mode (rpiPWM1::PWMMODE or rpiPWM1::MSMODE)
 * Return Value: 0 if successful or rpiPWM1::ERRMODE if MODE is invalid 
 ********************************************************************************/
unsigned int rpiPWM1::setMode(const int &m){
	unsigned int retVal = 0;
	if( (m != PWMMODE) && (m != MSMODE) ) {
		retVal = ERRMODE;
	}
	else{
		this->mode = m;
		setDutyCycleForce(this->dutyCycle, this->mode);
	 }
	 
 return retVal;
 }
  
  
/***********************************************************************
 *These are a bunch of 'getter' functions that enable the user
 * to access the PWM frequency, resolution, duty cycle and mode as well
 * as the PWM clock divisor value.
 *********************************************************************/
 double rpiPWM1::getFrequency() const{ return this->frequency;}
 int rpiPWM1::getCounts() const { return this->counts;}
 int rpiPWM1::getDivisor() const {return this->divisor;}
 double  rpiPWM1::getDutyCycle() const {return this->dutyCycle;}
 int rpiPWM1::getMode() const{return this->mode;}

/***********************************************************************
 *	volatile unsigned *rpiPWM1::mapRegAddr(unsigned long baseAddr)
 * This function maps a block (4KB) of physical memory into the memory of 
 * the calling process. It enables a user space process to access registers
 * in physical memory directly without having to interact with in kernel side 
 * code i.e. device drivers
 * Parameter - baseAddr (unsigned long) - this is the base address of a 4KB
 *             block of physical memory that will be mapped into the user
 *             space process memory. 
 * Return Value - mapped pointer in process memory 
 ***********************************************************************/ 
volatile unsigned *rpiPWM1::mapRegAddr(unsigned long baseAddr){
  int mem_fd = 0;
  void *regAddrMap = MAP_FAILED;

  /* open /dev/mem.....need to run program as root i.e. use sudo or su */
  if (!mem_fd) {
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
     perror("can't open /dev/mem");
      exit (1);
    }
  }
  
   /* mmap IO */
  regAddrMap = mmap(
      NULL,             //Any adddress in our space will do
      BLOCK_SIZE,       //Map length
      PROT_READ|PROT_WRITE|PROT_EXEC,// Enable reading & writting to mapped memory
      MAP_SHARED|MAP_LOCKED,       //Shared with other processes
      mem_fd,           //File to map
      baseAddr         //Offset to base address
  );
    
  if (regAddrMap == MAP_FAILED) {
	  perror("mmap error");
	  close(mem_fd);
	  exit (1);
  }
  
  if(close(mem_fd) < 0){ //No need to keep mem_fd open after mmap
                         //i.e. we can close /dev/mem
	perror("couldn't close /dev/mem file descriptor");
    exit(1);
	}	
  return (volatile unsigned *)regAddrMap;
}


/***********************************************************************
 * void rpiPWM1::configPWM1Pin()
 * This function is responsible for putting GPIO18 in PWM mode by setting 
 * its alternate function to ALT5. It firsts make the GPIO an input 
 * (default state) and then switches to alternate function 5 (PWM mode)
 ***********************************************************************/
void rpiPWM1::configPWM1Pin()
{
  
  /*GPIO 18 in ALT5 mode for PWM0 */
  // Let's first set pin 18 to input
  //taken from #define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
  *(gpio+1) &= ~(7 << 24);
  //then set it to ALT5 function PWM0
  //taken from #define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))
  *(gpio+1) |= (2<<24);
  
}


/***********************************************************************
 * void  rpiPWM1::configPWM1()
 * This function configures the PWM1 peripheral. 
 * - It stops the PWM clock
 * - Calculates an appropriate divisor value based on PWM Freq and resolution
 * - Writes this divisor value to the PWM clock
 * - Enables the PWM clock
 * - Disables the PWM peripheral
 * - Writes the PWM resolution and Duty Cycle to the appropriate registers
 * - Enables the PWM peripheral in the requested mode
 * *********************************************************************/
void  rpiPWM1::configPWM1(){
  
  double period;
  double countDuration;
  
  // stop clock and waiting for busy flag doesn't work, so kill clock
  *(clk + PWMCLK_CNTL) = 0x5A000000 | (1 << 5);
  usleep(10);  
  
  // wait until busy flag is set 
  while ( (*(clk + PWMCLK_CNTL)) & 0x00000080){}   
  
  //calculate divisor value for PWM1 clock...base frequency is 19.2MHz
  period = 1.0/this->frequency;
  countDuration = period/(counts*1.0f);
  this->divisor = (int)(19200000.0f / (1.0/countDuration));
  
  if( this->divisor < 0 || this->divisor > 4095 ) {
    printf("divisor value must be between 0-4095\n");
    exit(-1);
  }
  
  //set divisor
  *(clk + PWMCLK_DIV) = 0x5A000000 | (this->divisor << 12);
  
  // source=osc and enable clock
  *(clk + PWMCLK_CNTL) = 0x5A000011;
  
  // disable PWM & start from a clean slate
  *(pwm + PWM_CTL) = 0;
  
  // needs some time until the PWM module gets disabled, without the delay the PWM module crashs
  usleep(10); 
  
  // set the number of counts that constitute a period with 0 for 20 milliseconds = 320 bits
  *(pwm + PWM_RNG1) = this->counts; usleep(10);

   //set  duty cycle
  *(pwm + PWM_DAT1) = (int) ((this->dutyCycle/100.0) * this->counts); usleep(10);
  
  
  // start PWM1 in
  if(this->mode == PWMMODE) //PWM mode 
	*(pwm + PWM_CTL) |= (1 << 0); 
   else // M/S Mode
	*(pwm + PWM_CTL) |= ( (1 << 7) | (1 << 0) ); 
}
  
