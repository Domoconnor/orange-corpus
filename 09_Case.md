

##Manufacture / Casing 

[Back to Contents](#contents)

###Initial Research

The project required us to have hardware in the real world meaning that it has to be able to survive in the environment that it is deployed in. We couldn't simply deploy the electronics because they would get damaged. Therefor we have to house all of our pieces of hardware in some form of casing.

There are a few ways to make cases, they include making a custom 3D model of the object and sending it to companies to either be 3D printed, a process where plastic is melted and printed in layers to form the intended 3 dimensional object. Alternatively, injection moulding, a process where a mould is made of the object intended to be created then melted plastic fills the negative space in the mould leaving the object when it has hardened. 

Injection moulding creates a rigid plastic shell when hardened as the piece comes from liquid plastic that hardens into one piece whereas 3D printed pieces can be more brittle as the plastic dries on when each layer is added meaning it can leave pores on the final product.

There are companies that offer custom 3D printing and injection moulding such as [Shapeways](http://www.shapeways.com/) (3D printing) and [Protolabs](http://www.protolabs.co.uk/) (3D printing and injection moulding). The main issues with these places is the cost and time it would take to get an object back. We would have to design the object we want created, each piece is individually quoted, it would be created and we would have to wait for it to arrive. In the case of injection moulding Protolabs have a minimum of 25 parts from one mould, meaning it would be more expensive than 3D printing. If there was a mistake in a 3D model we would have wasted time and money and still have to print another one.

Although, The Shed has specific software for 3D modelling and a 3D printer that we can use for prototyping and final printing of our cases. It is possible to quickly print a prototype and test a design multiple times and print a final when we are happy with it. 

####Conclusion

We decided to use the Sheds facilities to create our cases. It will be much more cost efficient as we do not have to pay for each individual print and the turn around of each piece is much quick as we do not have to wait for it to be posted.

###Hub Case

####Description

The Hub case is 3D printed. It was designed to hold the Raspberry Pi in place through the use of screws and nuts. It is also designed in a manner that made it easy to open incase there were any problems while the hub was deployed. The case comes in two parts, the lid and the base.

The case is meant to be easily modifiable. So that if there are any changes that need to be made it is easy enough to change the 3D model and print off a new one that fits the purpose better.

*Base*

The base is made to be 2mm thick on the longer sides for strength and rigidity. It was made to be slightly bigger than the Raspberry Pi model B+ (5mm in every direction but the one with the ethernet connection). It has holes in the bottom big enough for 2.5mm fixings to fit through both the case and the board using nuts to hold it in place so that the board is secure inside.

There are two grooves on the longer sides of the base, inside the base, that allow the lid to click into place.

PICTURE OF THE BASE 

*Lid* 

The lid is designed to be reversible for ease of use. The longer sides of the lid has sections that sit inside the base. These sections are as long as the inside of the base so that it does not slide around when fitted. These extruded sections have further extruded lines that click into the grooves on the base. To remove the lid squeeze the sides and pull off. It was designed in this way for ease of access.

PICTURE OF THE LID

####Previous Work

####Base - Iteration 1 - Initial Version.

The FRDM K64F board had no technical specifications that could be found meaning we did not have the measurements for it. Therefore it had to be measured by eye using rulers and electronic calipers. 

INSERT INITIAL SKETCH

As this is the fist time we would be 3D printing anything we had no reference for how strong the result would be. We decided to measure the thickness of the calipers box as that seemed to be quite a strong (2.5mm).

We decided to model the bottom half of the case first. This was done because it was the smaller of the two pieces of the case, we could reprint a new one quickly if there was anything wrong with this one. We wanted the board to be secure in the case so the we designed it in a way that the base, lid and board had holes that lined up so 3mm fixings could be screwed through all three and secured together.

When designing the case the idea was to have part of the edge extrude further than the rest to create a lip so that the lid could sit inside. 

#####Outcomes of iteration

We 3D printed our first object, learnt how to use the software properly.

INSERT PICTURE OF PRINTED CASE

####Base - Iteration 2 - Changing the size and some positioning

#####Issues with Previous Iteration

After printing the first iteration we found that the base was slightly too tight for the board, the position of the cutout for the usb and ethernet ports were not big enough and one of the holes was out by ≈2mm.

#####Outcomes of Iteration

We reprinted the base of the case with the adjustments specified by the problems with the previous iteration. 2.5mm was added around all edges to make the board fit better, the cutout was made bigger so that usb and ethernet cables would fit and the distance for the hole was remeasured and moved by 2mm.

INSERT PICTURE OF MODEL, LINK TO IPT AND PHOTO

####Base - Iteration 3 - Moving the hole

#####Issues with Previous Iteration

The hole was still out by ≈2mm. Also the prints were taking longer than expected so we decided we should reduce it, in an attempt to keep the strength but reduce printing time and the cutout for the cables was now a little too big.

#####Outcomes of Iteration

We reprinted the base moving the hole by 2mm and reducing the thickness of the bottom of the base by 1mm. We made hole smaller for the cable by 3mm.

INSERT PICTURE OF MODEL, LINK TO IPT AND PHOTO

####Lid - Iteration 1 - Initial version

The idea behind the lid is that there are structures inside that line up with the holes in the base and the board that sit on top of the board to hold it down when the case is fixed together. These structures start by coming out of the side of the case by 45 degrees until it reaches 8.5mm to the rectangles that the fixings will go into, these are because of the way the lid will be printed. It will be printed upside down, they remove overhang because the 3D printer cant print on to blank space.

Also, the lid has to be tall enough for the FRDM board, the shield and an XBee to fit inside. The lid also had to have a cut out in it big enough for a power cable to fit and an ethernet cable.

#####Outcomes of iteration

The first iteration of the lid was printed. 

INSERT PICTURE OF MODEL, LINK TO IPT AND PHOTO

####Lid - Iteration 2 - Rounding the corners

#####Issues with Previous Iteration

we found that it didn't fit in its intended base as the corners that were printed were too tight. This is because in Base - Iteration 3 there were some plastic artefacts (misprints) left from its printing.

A problem arose when the lid was tested, putting the board in with the shield on as well was not considered. Although the height was, the added size of the shield meant that it did not fit in the gap between the structures inside that were meant to hold the board in place.

#####Outcomes of iteration

We reprinted the lid, rounding the corners that would sit inside Base - Iteration 3. And, because the hole was still ≈1mm out for the fixing it was moved by 1mm.

We decided not to remove the structures because we did not really need the shield, we could wire the XBee in directly.

INSERT PICTURE OF MODEL, LINK TO IPT AND PHOTO

####Base - Iteration 4 - moving the hole again

#####Issues with Previous Iteration

The hole was still out by ≈1mm. Although fixing still fit so this is just if we want to reprint to make the fit better.

#####Outcomes of the Iteration

The design for the base is created but we haven't printed it. It would fit with Lid - Iteration 2.

INSERT PICTURE OF MODEL, LINK TO IPT

####Base - Iteration 5 - Raspberry Pi Version 1

The board we are using for the hub changed to a Raspberry Pi Model B+. Unlike the FRDM board the Raspberry Pi is well documented and has [dimensions](https://www.raspberrypi.org/documentation/hardware/raspberrypi/mechanical/Raspberry-Pi-B-Plus-V1.2-Mechanical-Drawing.pdf) available.

The case has holes in the base big enough for 2.5mm fixings and nuts to hold the board in place, and section cut out of one side for the ethernet and usb ports. It has slits in the side for the lid to lock into.

#####Outcomes of Iteration

The first version of the base was printed.

INSERT PICTURE OF MODEL, LINK TO IPT AND PHOTO

####Lid - Iteration 3 - Raspberry Pi Version 1

The lid was designed to sit on top of the base with two extruding parts on the longer sides of the case, with parts on them that clip into holes in the inside of the base.

#####Outcomes of Iteration

The first version of the lid was printed.

INSERT PICTURE OF MODEL, LINK TO IPT AND PHOTO

####Base - Iteration 6 - Adding power cutout

#####Issues with Previous Iteration

When the base was printed it was realised that a cut out for the power cable was not present. Also that the walls were slightly too thin, they were not sturdy enough to hold the inserts form the lid that were meant to clip inside.

#####Outcomes of Iteration

The base was reprinted with a cutout for the power cable and the walls were made thicker.

INSERT PICTURE OF MODEL, LINK TO IPT

####Lid - Iteration 4 - Made to match base

#####Issues with Previous Iteration

There were no issues as such, this is just so that the wall thickness matches with the new base so the edges sit flush.

#####Outcomes of Iteration

The lid was reprinted with the walls made thicker to match the base.

INSERT PICTURE OF MODEL, LINK TO IPT

###Sensor Case

####Description

The sensor case is 3D printed to hold the sensor components. It needs to 

####Previous Work

#####Iteration 1 - Version 1

The case for the sensor came

###Clock Case
####Description
####Previous Work
#####Iteration 1
