after successfull compile & upload to flash within platform IO and usage of TTL based 3v3 UART to USB adapter one should then
select the monitor option as see the MCU being alive and providing real status info.
It is possible in the monitor to hit nter on the keyboard and then paste data, this can consist out of 3 small json data parts
being the channel polynome info, the channel correction data and the channel offset info, see the files rf_xxxxxxx.json

Upon upload you will get a verification message either succesfull or failed, additional to that upon startup of the application
you will get a table of the current NVS content. It's posible to overwrite current data by repeating the upload process using your
newly collected data.

to calculate the m_x_y value use correction for m_x_y = log10(Vac_target / Vac_measured)


