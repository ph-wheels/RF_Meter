after successfull compile & upload to flash within platform IO and usage of TTL based 3v3 UART to USB adapter one should then
select the monitor option as see the MCU being alive and providing real status info.
It is possible in the monitor to hit nter on the keyboard and then paste data, this can consist out of 3 small json data parts
being the channel polynome info, the channel correction data and the channel offset info.

without any upfront measurements one can load follow data for polynome

{
  "A_1": {"value": ["1.701847", "-2.164132", "0.413865", "-0.018022", "0.0"]},
  "A_2": {"value": ["-8.68609", "3.055452", "-0.509633", "3.40915e-2", "0.0"]},
  "A_3": {"value": ["-4.3087", "-0.165833", "0.198509", "-2.626658e-2", "1.301894e-3"]},

  "B_1": {"value": ["1.69182", "-2.162672", "0.414189", "-0.01807", "0.0"]},
  "B_2": {"value": ["-8.690836", "3.055452", "-0.509633", "3.40915e-2", "0.0"]},
  "B_3": {"value": ["-4.314696", "-0.165833", "0.198509", "-2.626658e-2", "1.301894e-3"]},
  
  "C_1": {"value": ["-2.83441", "-8.20502e-2", "8.21667e-02", "0.0", "0.0"]},
  "C_2": {"value": ["-8.690836", "3.055452", "-0.509633", "3.40915e-2", "0.0"]},
  "C_3": {"value": ["-4.314696", "-0.165833", "0.198509", "-2.626658e-2", "1.301894e-3"]}
}

correction data:

Zero_Offset data:


