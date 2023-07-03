/*
 * constants.h
 *
 *  Created on: Jul 1, 2023
 *      Author: adinor
 */

#ifndef INC_CONSTANTS_H_
#define INC_CONSTANTS_H_

/******************************************************************************
* Constants
*******************************************************************************/
/**
  Constants: I/O Pin Levels

  LOW           - Reserved word representing the logical value 0 (OFF, 0 volts).
  HIGH          - Reserved word representing the logical value 1 (ON, 5 volts).
  ACTIVE_LOW    - Reserved word representing the logical value 0 (OFF, 0 volts).
  INACTIVE_HIGH - Reserved word representing the logical value 1 (ON, 5 volts).
  INACTIVE_LOW  - Reserved word representing the logical value 0 (OFF, 0 volts).
  ACTIVE_HIGH   - Reserved word representing the logical value 1 (ON, 5 volts).
*/
#define LOW           0x0
#define HIGH          0x1
#define ACTIVE_LOW    0x0
#define INACTIVE_HIGH 0x1
#define INACTIVE_LOW  0x0
#define ACTIVE_HIGH   0x1

/**
  Constants: I/O Pin Levels
  DISABLED      - Reserved word for representing the logical value 0 (OFF, 0 volts).
  ENABLED       - Reserved word for representing the logical value 1 (ON, 5 volts).
*/
#define DISABLED          0
#define ENABLED           1

/**
  Constants: I/O Pin Levels
  FALSE         - Reserved word for representing the logical value 0 (OFF, 0 volts).
  TRUE          - Reserved word for representing the logical value 1 (ON, 5 volts).
*/
#define FALSE             0
#define TRUE              1

/**
  Constants: ON/OFF States
  OFF         - Reserved word for representing the logical value 0 (OFF, 0 volts).
  ON          - Reserved word for representing the logical value 1 (ON, 5 volts).
*/
#define OFF           0
#define ON            1

/**
 * Defines the idle mode behavior of peripherals
 */
enum Peripheral_IdleEnum
{
	CONTINUE,			/**< Continue operation in Idle mode */
	DISCONTINUE 		/**< Halt operation in Idle mode */
};

/**
  Constants: I/O Pin Modes

  INPUT  - Reserved word representing the mode of an I/O pin or an I/O port as an input.
  OUTPUT - Reserved word representing the mode of an I/O pin or an I/O port as an output.
*/
#ifndef INPUT
	#define INPUT   1
#endif
#ifndef OUTPUT
	#define OUTPUT  0
#endif

/**
  Constants: Toggle
  Is used to define the toggle state for the LEDs.
*/
#define TOGGLE		3

/**
  Constants: Zero
  Used to define a constant value of zero.
*/
#define ZERO              0

/*
 * Define NULL pointer value.
 */
#ifndef NULL
	#define NULL  (void *) 0
#endif

/**
  Constants: null
  Is used to define both null and NULL keywords.
*/
#define null  NULL

/**
  Constants: Number Base
  DEC   - defines the base 10 decimal numbering system.
  HEX   - defines the base 16 hexadecimal numbering system.
  OCT   - defines the base 8 octal numbering system.
  BIN   - defines the base 2 binary numbering system
*/
#define DEC 10
#define HEX 16
#define OCT 8
#define BIN 2

/**
  Constants: Engineering Constants
  PI         - 3.1415927
  TWO_PI     - 6.2831854
  HALF_PI    - 1.57079
  EPSILON    - 0.0001
  DEG_TO_RAD - 0.01745329
  RAD_TO_DEG - 57.2957786
*/
#define PI         (3.1415927)
#define TWO_PI     (6.2831854)
#define HALF_PI    (1.57079)
#define EPSILON    (0.0001)
#define DEG_TO_RAD (0.01745329)
#define RAD_TO_DEG (57.2957786)

/**
  Constants: WPINx
  Pin x shift.
*/
#define WPIN0 (1UL<<0)
#define WPIN1 (1UL<<1)
#define WPIN2 (1UL<<2)
#define WPIN3 (1UL<<3)
#define WPIN4 (1UL<<4)
#define WPIN5 (1UL<<5)
#define WPIN6 (1UL<<6)
#define WPIN7 (1UL<<7)
#define WPIN8 (1UL<<8)
#define WPIN9 (1UL<<9)
#define WPIN10 (1UL<<10)
#define WPIN11 (1UL<<11)
#define WPIN12 (1UL<<12)
#define WPIN13 (1UL<<13)
#define WPIN14 (1UL<<14)
#define WPIN15 (1UL<<15)
#define WPIN16 (1UL<<16)
#define WPIN17 (1UL<<17)
#define WPIN18 (1UL<<18)
#define WPIN19 (1UL<<19)
#define WPIN20 (1UL<<20)
#define WPIN21 (1UL<<21)
#define WPIN22 (1UL<<22)
#define WPIN23 (1UL<<23)
#define WPIN24 (1UL<<24)
#define WPIN25 (1UL<<25)
#define WPIN26 (1UL<<26)
#define WPIN27 (1UL<<27)
#define WPIN28 (1UL<<28)
#define WPIN29 (1UL<<29)
#define WPIN30 (1UL<<30)
#define WPIN31 (1UL<<31)

/**
  Constants: REGBITx
  Bit x shift.
*/
#define REGBIT0 (1UL<<0)
#define REGBIT1 (1UL<<1)
#define REGBIT2 (1UL<<2)
#define REGBIT3 (1UL<<3)
#define REGBIT4 (1UL<<4)
#define REGBIT5 (1UL<<5)
#define REGBIT6 (1UL<<6)
#define REGBIT7 (1UL<<7)
#define REGBIT8 (1UL<<8)
#define REGBIT9 (1UL<<9)
#define REGBIT10 (1UL<<10)
#define REGBIT11 (1UL<<11)
#define REGBIT12 (1UL<<12)
#define REGBIT13 (1UL<<13)
#define REGBIT14 (1UL<<14)
#define REGBIT15 (1UL<<15)
#define REGBIT16 (1UL<<16)
#define REGBIT17 (1UL<<17)
#define REGBIT18 (1UL<<18)
#define REGBIT19 (1UL<<19)
#define REGBIT20 (1UL<<20)
#define REGBIT21 (1UL<<21)
#define REGBIT22 (1UL<<22)
#define REGBIT23 (1UL<<23)
#define REGBIT24 (1UL<<24)
#define REGBIT25 (1UL<<25)
#define REGBIT26 (1UL<<26)
#define REGBIT27 (1UL<<27)
#define REGBIT28 (1UL<<28)
#define REGBIT29 (1UL<<29)
#define REGBIT30 (1UL<<30)
#define REGBIT31 (1UL<<31)

/**
  Constants: WPORTA
  Map WPORTx to PORTx
*/
#define WPORTA PORTA
#define WPORTB PORTB
#define WPORTC PORTC
#define WPORTD PORTD
#define WPORTE PORTE
#define WPORTF PORTF
#define WPORTG PORTG

/**
  Constants: WPINA
  Maps WPINx to a pin.
*/
#define WPINA PINA
#define WPINB PINB
#define WPINC PINC
#define WPIND PIND
#define WPINE PINE
#define WPINF PINF
#define WPING PING

/**
  Constants: WDDRX
  Maps WDDRx to data direction port DDRX
*/
#define WDDRA DDRA
#define WDDRB DDRB
#define WDDRC DDRC
#define WDDRD DDRD
#define WDDRE DDRE
#define WDDRF DDRF
#define WDDRG DDRG

#if 0
/**
  Constants: BITX
  Access BITX bit in a 16 bit number.
  */
#define BIT0   0x01
#define BIT1   0x02
#define BIT2   0x04
#define BIT3   0x08
#define BIT4   0x10
#define BIT5   0x20
#define BIT6   0x40
#define BIT7   0x80

/**
  Constants: BITXY
  Access BITXY bit in a 16 bit number.
  */
#define BIT00   0x0001
#define BIT01   0x0002
#define BIT02   0x0004
#define BIT03   0x0008
#define BIT04   0x0010
#define BIT05   0x0020
#define BIT06   0x0040
#define BIT07   0x0080
#define BIT08   0x0100
#define BIT09   0x0200
#define BIT10   0x0400
#define BIT11   0x0800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000

#endif

//Constants: Byte Numbering
//Used to represent number of bytes.  ONE_BYTE, TWO_BYTES, ... NINE_BYTES
#define ONE_BYTES        1
#define TWO_BYTES        2
#define THREE_BYTES      3
#define FOUR_BYTES       4
#define FIVE_BYTES       5
#define SIX_BYTES        6
#define SEVEN_BYTES      7
#define EIGHT_BYTES      8
#define NINE_BYTES       9

//Bit shifting
#define IOPORT_BIT_15                       (1 << 15)
#define IOPORT_BIT_14                       (1 << 14)
#define IOPORT_BIT_13                       (1 << 13)
#define IOPORT_BIT_12                       (1 << 12)
#define IOPORT_BIT_11                       (1 << 11)
#define IOPORT_BIT_10                       (1 << 10)
#define IOPORT_BIT_9                        (1 << 9)
#define IOPORT_BIT_8                        (1 << 8)
#define IOPORT_BIT_7                        (1 << 7)
#define IOPORT_BIT_6                        (1 << 6)
#define IOPORT_BIT_5                        (1 << 5)
#define IOPORT_BIT_4                        (1 << 4)
#define IOPORT_BIT_3                        (1 << 3)
#define IOPORT_BIT_2                        (1 << 2)
#define IOPORT_BIT_1                        (1 << 1)
#define IOPORT_BIT_0                        (1 << 0)

/**
  Constants: Percentages
  General percent constants.

    PERCENT_0     - 0,   0%
    PERCENT_100   - 100, 100%
*/
#define PERCENT_0       0
#define PERCENT_100     100

/**
  Constants: CLOCK_DIVIDEBY_X
  Clock Prescaler Values.

   CLOCK_DIVIDEBY_1                  1
   CLOCK_DIVIDEBY_2                  2
   CLOCK_DIVIDEBY_4                  4
   CLOCK_DIVIDEBY_8                  8
   CLOCK_DIVIDEBY_16                 16
   CLOCK_DIVIDEBY_32                 32
   CLOCK_DIVIDEBY_64                 64
   CLOCK_DIVIDEBY_128                128
   CLOCK_DIVIDEBY_256                256
*/
#define CLOCK_DIVIDEBY_1                  1
#define CLOCK_DIVIDEBY_2                  2
#define CLOCK_DIVIDEBY_4                  4
#define CLOCK_DIVIDEBY_8                  8
#define CLOCK_DIVIDEBY_16                 16
#define CLOCK_DIVIDEBY_32                 32
#define CLOCK_DIVIDEBY_64                 64
#define CLOCK_DIVIDEBY_128                128
#define CLOCK_DIVIDEBY_256                256

/**
 Constants: ClOCK_X_MHZ
 Defines the unsigned long value of the clock frequency.

 CLOCK_1_MHZ                    1000000UL
 CLOCK_2_MHZ                    2000000UL
 CLOCK_4_MHZ                    4000000UL
 CLOCK_8_MHZ                    8000000UL
 CLOCK_16_MHZ                   16000000UL
 CLOCK_24_MHZ                   24000000UL
 CLOCK_32_MHZ                   32000000UL
 CLOCK_40_MHZ                   40000000UL
 CLOCK_48_MHZ                   48000000UL
*/
#define CLOCK_1_MHZ                     1000000UL
#define CLOCK_2_MHZ                     2000000UL
#define CLOCK_4_MHZ                     4000000UL
#define CLOCK_8_MHZ                     8000000UL
#define CLOCK_16_MHZ                    16000000UL
#define CLOCK_24_MHZ                    24000000UL
#define CLOCK_32_MHZ                    32000000UL
#define CLOCK_40_MHZ                    40000000UL
#define CLOCK_48_MHZ                    48000000UL

/**
 Constants: ClOCK_X_MHZ
 Defines the unsigned long value of the clock frequency.
*/
#define CLOCK_PERIOD_NS_1_MHZ           1000UL
#define CLOCK_PERIOD_NS_2_MHZ           500UL
#define CLOCK_PERIOD_NS_4_MHZ           250UL
#define CLOCK_PERIOD_NS_8_MHZ           125UL
#define CLOCK_PERIOD_NS_16_MHZ          62UL
#define CLOCK_PERIOD_NS_24_MHZ          42UL
#define CLOCK_PERIOD_NS_32_MHZ          31UL
#define CLOCK_PERIOD_NS_40_MHZ          25UL
#define CLOCK_PERIOD_NS_48_MHZ          21UL

#define CLEAR_FLAG_POS                  TRUE
#define CLEAR_FLAG_NUL                  FALSE
/******************************************************************************
* Macros
*******************************************************************************/
// undefine stdlib's abs if encountered
#ifdef abs
#undef abs
#endif
/**
  Macro: Abs
    Returns the absolute value of a number.

  Parameters:
    n  - the number

  Returns:
    n  - if is greater than or equal to 0
    -n - if x is less than zero

  Example:

  : // Take the absolute value of the number
  : abs = Abs(num);
*/
#define Abs(x)       ((x)>0?(x):-(x))

/**
  Macro: Constrain
    Constrains a number to be within a range.

  Parameters:
    amt  - the number to constrain, all data types
    low  - the lower end of the range, all data types
    high - the upper end of the range, all data types

  Returns:
    amt  - if amt is between a and b
    low  - if amt is less than low
    high - if amt is greater than high

  Example:

  : // limits range of sensor values to between 10 and 150
  : sensVal = Constrain(sensVal, 10, 150);

  Related:
    <Min> <Max>
*/
#define Constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

/**
  Macro: Degrees
  This macro converts radians to degrees.
*/
#define Degrees(rad) ((rad)*RAD_TO_DEG)

/**
  Macro: Max
    Returns the larger of two numbers.

  Parameters:
    a - the first number, any data types
    b - the second number, any data types

  Returns:
    The larger of the two numbers.

  Example:

  Related:
    <Min> <Constrain>
*/
#define Max(a,b)     ((a)>(b)?(a):(b))

/**
  Macro: Min
    Returns the smaller of two numbers.

  Parameters:
    a - the first number, any data types
    b - the second number, any data types

  Returns:
    The smaller of the two numbers.

  Example:

  Related:
    <Max>, <Constrain>
*/
#define Min(a,b)     ((a)<(b)?(a):(b))

/**
  Macro: Round
  This macro rounds a float to a integer.
*/
#define Round(x)     ((x)>=0?(long)((x)+0.5):(long)((x)-0.5))

/**
  Macro: Radians
  This macro converts degrees to radians.
*/
#define Radians(deg) ((deg)*DEG_TO_RAD)

/**
  Macro: Sq
    Returns the square a number.
*/
#define Sq(x)        ((x)*(x))


/**
  Macro: Bit Manipulation
   bit(x)         - access bit
   setBits(x)     - set the specified bit
   clearBits(x,y) - clears the bit
   bitRead(x,y)   - read a bit
   bitWrite(x,y)  - write a bit
   lowByte(x)     - access lower byte
   highByte(x)    - access the top byte of a 16 bit number
*/
#define bit(x) (1<<(x))
#define setBits(x, y) ((x)|=(y))
#define clearBits(x, y) ((x)&=(~(y)))
#define bitRead(x,y) (((x)>>(y)) & 1)
#define bitWrite(x, y, v) ((v) ? bitSet((x), (y)) : bitClear((x), (y)))
#define lowByte(x) ((x) & 0x00ff)
#define highByte(x) ((x)>>8)


/******************************************************************************
* Enumeration Declarations
*******************************************************************************/
/**
	Enum: Number of bits to shift
 */
typedef enum
{
  ZERO_BITS,
  ONE_BIT,
  TWO_BITS,
  THREE_BITS,
  FOUR_BITS,
  FIVE_BITS,
  SIX_BITS,
  SEVEN_BITS,
  EIGHT_BITS,
  NINE_BITS,
  TEN_BITS,
  ELEVEN_BITS,
  TWELVE_BITS,
  THIRTEEN_BITS,
  FOURTEEN_BITS,
  FIFTEEN_BITS,
  SIXTEEN_BITS,
  SEVENTEEN_BITS,
  EIGHTEEN_BITS,
  NINETEEN_BITS,
  TWENTY_BITS,
  TWENTYONE_BITS,
  TWENTYTWO_BITS,
  TWENTYTHREE_BITS,
  TWENTYFOUR_BITS,
  TWENTYFIVE_BITS,
  TWENTYSIX_BITS,
  TWENTYSEVEN_BITS,
  TWENTYEIGHT_BITS,
  TWENTYNINE_BITS,
  THIRTY_BITS,
  THIRTYONE_BITS,
  THIRTYTWO_BITS
}
BitShiftType;


#endif /* INC_CONSTANTS_H_ */
