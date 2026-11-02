after successfull compile & upload to flash within platform IO and usage of TTL based 3v3 UART to USB adapter one should then
select the monitor option as see the MCU being alive and providing real status info.
It is possible in the monitor to hit nter on the keyboard and then paste data, this can consist out of 3 small json data parts
being the channel polynome info, the channel correction data and the channel offset info.

without any upfront measurements one can load follow data for polynome
"A_1": {"value": ["1.701847", "-2.164132", "0.413865", "-0.018022", "0.0"]},
"B_1": {"value": ["1.713079", "-2.173214", "0.415925", "-0.018165", "0.0"]},
