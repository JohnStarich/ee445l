# Lab 1: Fixed-point Output

## Objectives

In this lab we are becoming familiar with our microcontroller, the TI TM4C123. Specifically we will be learning how to work with fixed point operations as well as our display, the ST7735.

The primary objectives are to display fixed-point decimal numbers, unsigned binary fixed-point numbers, and plot two shapes on the screen.


## Analysis and Discussion

In a call graph representing our system, we would do well to minimize the number of arrows in order to keep our system as close to real-time as we can.

When dealing with fixed-point numbers, it is important that the decimal be in a fixed position, both numerically and on the physical display. If the decimal moves numerically, the meaning of the number has changed. If its position changes on the display we may not know where to move the cursor to write the next number to the display.

Fixed-point computations are best used when the resolution is known ahead of time and we want to keep the calculations nice and fast. Floating point numbers, on the other hand, take slightly longer on our board. After many floating point operations the delay will become noticeable. It is useful, however, when the resolution is not known ahead of time.

When choosing the kind of fixed-point we need to use, we have a choice between decimal and binary fixed-point. We prefer decimal fixed-point when we're displaying for a human to read, but we prefer binary fixed-point when we still need to run some calculations on the data. We've found it is easier to output the decimal fixed-point numbers to a display than the binary fixed-point numbers.

As an example of a fixed-point application, we could use a 1 foot ruler. A typical ruler has a resolution of 1 millimeter, so we cannot clearly measure any decimal point smaller than that. So whenever we measure something (say, the length of someone's shoe) using said ruler, we would log the number down to the millimeter. So the format would look like 15.3 cm if we displayed it in centimeters.

We are able to use floating operations on the ARM Cortex M4, but the performance cost is significant.


