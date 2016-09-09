# Turbidity sensor prototype

## Background

There are various approaches [1] to depth measurement -- float switches, arrays of open wires, optical and sonar distance sensors, etc.  One simple approach is to leverage the dielectric properties of water by making a capacitive measurement.  

The simple picture is: the time taken to charge and discharge a capacitor when applying a given voltage is proportional to its capacitance, and its capacitance is proportional to the dielectric constant of the material around it.  So, setting up a circuit that allows a capacitor to charge and discharge to a fixed voltage V, and measuring the time taken for this charge/discharge cycle to occur (or, equivalently, the frequency of this charge/discharge process), can be considered a measure of the amount of local dielectric.  In the case of a capacitor submerged in liquid, this dielectric value will grow in linear proportion to the amount of the capacitor submerged in the liquid; and thus the frequency will be directly related to the liquid level:

<img src="digikey_capacitive_sensing.png">

_Source: http://www.digikey.com/en/articles/techzone/2011/sep/liquid-level-sensing-is-key-technology-for-todays-systems---part-1_

## Circuit

## Bill of Materials

## Schematic 

<img src="pics/riffle_depth_schem_simple.png">

## Diagram for Riffle Protoboard

<img src="pics/riffle_depth_diagram.png">

## Calibration Methods

## Research Notes on Public Lab

## References

1. Digikey's guide to depth measurement techniques: http://www.digikey.com/en/articles/techzone/2011/sep/liquid-level-sensing-is-key-technology-for-todays-systems---part-1
2. Using light sensors and a ping pong ball: http://howmuchsnow.com/waterlevel/
e

------


Links to research on capacitive sensors -- thread with dan beavers
Link to Scott Eustis research note https://publiclab.org/notes/eustatic/05-21-2016/riffing-on-the-riffle-for-a-depth-sensor-update-from-2014
Evaluation material
Ways of calibrating
Dan Beaver’s alternative proposal: https://publiclab.org/notes/danbeavers/05-18-2016/depth-sensor-proposal
Depth sensor workshop in NOLA
https://publiclab.org/notes/stevie/06-06-2016/reflecting-on-the-depth-sensor-build
https://publiclab.org/wiki/depth-flood-sensing-in-new-orleans
https://publiclab.org/notes/stevie/05-04-2016/depth-sensor-build
Original workshop: https://publiclab.org/notes/laurenrae/11-24-2014/don-explains-the-theory-behind-the-depth-sensor-for-the-riffle
Nice explanation of principle: http://njhurst.com/electronics/watersensor/
Vegetronix: https://www.vegetronix.com/Products/AquaPlumb/
REALLY good review of issues w/ capacitive depth sensor: http://www.umbc.edu/cuere/BaltimoreWTB/pdf/TM_2009_003.pdf
** grab page 21 bottom figure **
Issues w/ capacitive depth sensors: http://www.lionprecision.com/tech-library/technotes/cap-0020-sensor-theory.html
Various approaches to measuring depth: 
Github repo
Schematic
Protoboard layout
Code
Basic concept
Markdown doc → research note
History & Motivation
Road Salt
Flooding
Drought
Basic approaches
http://www.digikey.com/en/articles/techzone/2011/sep/liquid-level-sensing-is-key-technology-for-todays-systems---part-1
Optical, with ping pong ball: 
555 approach & history

