<style>
	.todo{ color:red }
</style>

#Orange Street

### <a name="sensor"></a>Sensor [cont.](#contents)
The sensor samples sound every minute. The microphone in the sensor starts collecting sound data every minute it produces data that represents a sine wave. The data is then put through an ADC (Analogue to Digital Converter) that amplifies the analogue data (sine wave) and removes any voltage noise. It is then analysed by the sensor, taking fifty points along the wave, in this minute time period, to find the amplitude of the wave (how loud the sound is).  

The sensor is comprised of multiple parts, [Microphone](#mic), [ADC](#adc), [Board](#board), [Clock](#clock), [Battery](#battery), [Case](#case).  
###### <a name="mic"></a>Microphone
###### <a name="adc"></a>ADC
###### <a name="board"></a>Board
###### <a name="clock"></a>Clock
###### <a name="battery"></a>Battery
###### <a name="case"></a>Case
The Case was designed in a way that was intended to aim our microphone at the noisy street and protect the electronics from the elements. It was 3D printed at a high fidelity (high infill of plastic) with a thickness of 3mm as not to allow water in through the printed plastic. It was then sanded and sprayed with a high fill primer to fill any pores left int the plastic left from the printing process. As the case had to be closed around the electronics of the sensor a seam was built in that was filled with a neoprene strip as to stop any water from getting through said seam.

#### Sensor Development/Iterations

Based on our [client interaction](#client-interaction) we decided that we had to make a device that measured the volume of the sound in Orange Street, collecting the data and sending it back to a server so that it is stored and can be accessed by the client to use.

The specification for the sensor meant that it had to accurately collect sound data, last for a reasonable amount of time (around a month) without being charged and be weatherproof.
