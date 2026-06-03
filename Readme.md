# QCollimator

I thought I would try and write a simple Collumator tool so I can use a cheap SV205 Web-Cam type camera to check the colimination on my GSO 6".

# QT Code

Actually the QT is not as bad as I was thinking, it is just a little trickly to get multiple widgets to compile (use full path,and be careful with Class names).

# Mac-isms

On a mac to see the available USB camera you type

     system_profiler SPCameraDataType

Which in my case yields

```text
Camera:

    SVBONY SV205:

      Model ID: UVC Camera VendorID_3034 ProductID_22656
      Unique ID: 0x1124300bda5880
```

Due to **Security** the Mac needs to be granted permission in 2 places - Info.plist ( So I have this file as a source file,and referenced in the CMakelists.txt), but it also needs the user to confirm they are allowing the camera to be used. 

Now this is a little more tricky, as it needs to be done in a careful manner. i.e. Do not connect to the camera until we have permission.... 

So the code goes

  - setupUi(this);
  - CameraPermission();
    - This just keeps checking until 1 of 2 possibilties
      - Granted - we then call the Widget creation and connection code
      - Denied - we give the user a message and throw our toys out of the pram. 
      
If you get a message looking like 

```text
QCollimate starting
qt.multimedia.ffmpeg: Using Qt multimedia with FFmpeg version 7.1.2 LGPL version 2.1 or later
Trying to use  ""
```

No suitable video Camera can be found on your system.
