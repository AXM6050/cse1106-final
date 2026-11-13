DESIGN IDEA: 

The input for the following code is taken fom the user.
It is entered at the terminAl and takes in as many entries as the user likes to a maximum total of 10 entries.
We currently have the led.c file that lights up the led.
To make it work according to our requirements we have initialized the PIN and got it ready at the start of the code.
Next to decide whether it should be turned on or off (indicating WARNING or NORMAL), we have put it in a for() loop.
The for() loop contains the conditions to check if user entered value is above or below max and minimum temperature respectively.
The maximum and minimum are defined at the top of the code so that changes to temperature range can be made easily according to any new client requirements.
Finally, once all values are entered, the average is calculated and all values are saved to an external file named "classroom_temperature_log".

