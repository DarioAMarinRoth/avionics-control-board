
#define MODE_4MHZ	4000000UL
#define MODE_16MHZ	16000000UL
/*
 * delay_us: realiza una espera de n microsegundos.
 */
inline void delay_us(int n)
{

	#if F_CPU == MODE_4MHZ

        /* 
        Para esperas de hasta 10us aproximadamente hay bastante error. 
        De ahi para arriba se vuelve mas preciso con menos error.
        */
		for (int i = 0; i < n; i++) {
  	        asm volatile ("nop" "\n\t");
        }

	#elif F_CPU == MODE_16MHZ
		if (us <= 40) {
    		while (us--) {
    			asm volatile(
					"nop" "\n\t"
        	      	"nop" "\n\t"
        	      	"nop" "\n\t"
        	      	"nop" "\n\t"
        	      	"nop" "\n\t"
        	      	"nop" "\n\t"
        	      	"nop" "\n\t");
  		    }
  			asm volatile(
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t"
				"nop" "\n\t");
  		} else {
    		while (us--) {
    			asm volatile(
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t"
					"nop" "\n\t");
  			}
  		}
	#endif
}

inline void delay_ms(int n)
{
	#if F_CPU == MODE_4MHZ

	for (int i = 0; i < n; i++) {
        delay_us(1000);
     }

	#elif F_CPU == MODE_16MHZ
		while (ms--) {
    		volatile int us = 1000;
    		while (us--) {
     		asm volatile(
				"nop" "\n\t"
				"nop" "\n\t");
    		}
  		}	
	#endif
}
