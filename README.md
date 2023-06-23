# MatDis

First of all ...What is MatDis?

MatDis is a points counter in big.
You can hang it on the wall because it consits out of 6 big led matrices.
I use some noname from reichelt.at. But they are identical to the freetronics ones.
They are powered by a pretty big power supply because the thig draws current like crazy. (4A at 5V a single panel when each led is on🤯)
The panels are connected in serial via hub12 connectors and use the dmd interface.
The brain 🧠 of this system is a ESP32 (I need to lookup the exact model but it was some dev board from AZ-Delivery.)
The system uses 12 input buttons to controll it directly. 
Later there will be a app which connects via ble to the esp and can manipulate the points. (Until now only the esp part of the ble implementation is implemented. The app will come until fall)

Later i will provide more information on the hardware side.

Now you know. 😋
