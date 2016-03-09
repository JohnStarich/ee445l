# Lab 5: Music Player and Audio Amp

## Objectives

See [Requirements.md](Requirements.md)

## Hardware Design

See [lab5.sch](lab5.sch)

## Software Design

We followed the design spec from the lab manual's figure 5.8 and 5.9, copied below:

![Figure 5.8](figure5.8.png)

![Figure 5.9](figure5.9.png)

## Measurement Data

Our reference voltage is set to 1.25V.

The resolution we calculated is 0.457 mV per increment value of our DAC. We found this using the equation: `(31mV - (-17mV)) / (105 - 0) = 0.457mV`

Our maximum DAC value is 5470, by the following equation: `(2 * 1.25) V / 0.457 mV/DAC = 5470 DAC`

The precision of our DAC is 4096. For a theoretical voltage for a DAC value of 1500, we got 1.465V using the equation: `(1500 * 2 * 2) / 4096 = 1.465V`

The actual voltage for a DAC output of 1500 is 1.83V.

Going by this calculation, our accuracy is 75.09%, via the equation: `1 - (1.83V - 1.465V) / 1.465V = 0.7509 = 75.09%`

Here are 8 DAC output measurements:

![DAC Output Measurement 1](dac1.png)

DAC Output Voltage for 2000: 2.44V

![DAC Output Measurement 2](dac2.png)

DAC Output Voltage for 1750: 2.12V

![DAC Output Measurement 3](dac3.png)

DAC Output Voltage for 1500: 1.80V

![DAC Output Measurement 4](dac4.png)

DAC Output Voltage for 1250: 1.56V

![DAC Output Measurement 5](dac5.png)

DAC Output Voltage for 1000: 1.24V

![DAC Output Measurement 6](dac6.png)

DAC Output Voltage for 750: 0.92V

![DAC Output Measurement 7](dac7.png)

DAC Output Voltage for 500: 0.60V

![DAC Output Measurement 8](dac8.png)

DAC Output Voltage for 250: 0.36V

After measuring the time domain and frequency domain of our system at 425Hz, we captured the following output:

![Speaker time domain](time_domain.png)

Time domain at 425Hz

![Speaker frequency domain](frequency_domain.png)

Frequency domain at 425Hz

![Speaker noise](noise.png)

Speaker noise

Given the above output, we calculate our SNR to be 26.4dB according to this formula: `SNR = signal - noise = (-25.6dB) - (-52.0dB) = 26.4dB`

The maximum time required to execute our periodic interrupt service routine is 1 microsecond and the time between our ISR calls is about 40 microseconds. Therefore the ratio of time spent in the ISR versus the main program is `1/40 = 0.025 = 2.5%`.

![ISR max execution time](isr_max_time.png)

ISR max execution time = 1 microsecond

![ISR to ISR execution time](isr_to_isr_delta.png)

ISR to ISR time delta = 40 microseconds

We measured our current usage for our board set up to run at about 75mA without the music playing and about 96mA with it playing.

## Analysis and Discussion

1. Three possible errors on a DAC could include the following:
    - noise produced at the same frequencies as the output frequencies
    - bad resistor choices for producing the DAC increments
    - the operational amplifier could produce noise or other artifacts in the output
2. With SPH and SPO set to 0, the data available interval is 25ns. The data required interval depends on both setup time and hold time, so 13ns in total. Given that our clock speed was set to 16MHz, our clock period interval was 62.5ns. Since the smallest clock low width is 25ns, then the shortest SSI period must be `62.5 + 25 = 87.5ns`. This corresponds to a max SSI clock of 11.428MHz. We used an SSI clock of 8MHz, below that maximum.
3. Frequency range of a spectrum analyzer is determined by dividing the sampling frequency by 2 (Nyquist thm.)
4. We did not drive the speaker directly from the DAC because the current required for any decent volume is too high for the board's GPIO pins to supply. The opamp (TPA731) helps take care of the current problem by providing a current gain but a voltage decrease.
