# Toyota-Radar-Spoofer
This project had a simple goal: ensure that Openpilot could read an external radar. This is merely a proof of concept that may be expanded upon in the future. This guide will show the reader how this can be achieved.
## HARDWARE REQUIREMENTS:

1. Arduino and CAN shield
	I used a MCP2515 CAN board which I soldered on a 16MHz crystal. 
2. Comma.ai Eon with Openpilot installed
3. Comma. ai Giraffe
	I used a Toyota Giraffe but it should work with a Honda one if you know the pinout
4. Comma.ai Panda
5. Toyota RAV4/Corolla Radar PN: 88210-07010
6: 12VDC power source with a fitting barrel connector for the Giraffe.

## CONNECTING:

### Arduino

I made up a little wiring harness for the Arduino to connect to the Giraffe through the fake ethernet port. The wiring follows Ethernet T-568B standard:

|PIN | COLOR | FUNCTION|
|----|-------|---------|
|1	 | OW		 | GND     |
|2	 | O		 | 12V     |
|3	 | GW		 | CAN1L   |
|4	 | B		 | N/A     |
|5	 | BW		 | N/A     |
|6	 | G		 | CAN1H   |
|7	 | BRW	 | CAN2H   |
|8	 | BR		 | CAN2L   |

CAN1H and CAN1L should be connected to the MCP2515 CAN H and L lines via Ethernet pins 3 and 6, respectively.

### Radar:

Below is a crude pinout I made for the Radar(Left) and the Giraffe female connector (Right):
￼    ￼

![alt text](https://github.com/wocsor/Toyota-Radar-Spoofer/blob/master/radar.png?raw=true)
![alt text](https://github.com/wocsor/Toyota-Radar-Spoofer/blob/master/Giraffe.png?raw=true) 



The pins connect as follows:

|RADAR PIN	| FUNCTION	| GIRAFFE PIN|
|-----------|-----------|------------|
|1	      	| 	VCC	    |		4        |
|2			    |  CANL		  |   5        | 
|3			    |  CANH     |		11       | 
|5		      |	CANH      |		12       | 
|6			    |  CANL     |		6        |
|8			    |  GND      |	  1        |


Once this is connected, plug the Arduino into the giraffe by ethernet and upload the sketch. Next, SSH into EON and edit /data/openpilot/common/fingerprints.py. Comment out the TOYOTA.RAV4 section and add a new fingerprint to the end of the Toyota fingerprints section:

```
  TOYOTA.RAV4: [{
    244: 8, 245: 8, 246: 8, 247: 8, 248: 8, 249: 8, 250: 8, 251: 8, 252: 8, 253: 8, 254: 8, 1279: 8
  }],
```

The whole fingerprint needs to be on ONE LINE so be mindful of that if you’re copy pasting. Note that you can comment out any Toyota and name this whatever you commented out. This is just to force OP to recognize the Arduino and force load the faked su routines.

Now you should be able to kill OP with control-C and relaunch with:
```
cd /data/openpilot
./launch_openpilot.sh | grep “fingerprinted”
```
Connect everything together and set the switches on the giraffe to 0010. Plug in the 12V power source to the barrel connector of the giraffe and you should now see “fingerprinted TOYOTA RAV4 2017” in the terminal. Openpilot should also start recording and tracking the radar. You’ll know if it worked if you see a big red triangle floating around onscreen. 
