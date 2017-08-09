RD /S /Q out
MD out
MD out\bin
MD out\bin\bin
MD out\res

COPY /B Project\Release\LaserTest.exe out\bin\bin

C:\Factory\DevTools\SemiRelease.exe Music.txt       out out\res\Music_       ..\..\res\Music_
C:\Factory\DevTools\SemiRelease.exe Picture.txt     out out\res\Picture_     ..\..\res\Picture_
C:\Factory\DevTools\SemiRelease.exe SoundEffect.txt out out\res\SoundEffect_ ..\..\res\SoundEffect_

PAUSE
