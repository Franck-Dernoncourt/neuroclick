Description:
NeuroClick is a program that emulates mouse clicks with eye blinks 
why using the NeuroSky MindWave headset. http://neurosky.com/
//
Main author: Franck Dernoncourt <http://francky.me>
NeuroClick home page: http://francky.me/software.php#Neuroclick2012
Version: 0.2 (20120721)
//
Eye blink detection accuracy:
Ca. 90% accurate, due to the NeuroSky MindWave API which misses around 10% 
of eye blinks. Such a good accuracy is perhaps due to the fact that I place
the sensor very close to my left eye, virtually on my eyebrow. Picture: 
http://img694.imageshack.us/img694/1027/20120705005354.jpg. 
//
What if I don't want to click but I need to blink ? 
* Most of the time the mouse cursor is placed on a neutral position so 
  it does not matter if you click;
* For Neurosky to maximize eyeblink detection you have to blink strongly.
//
Compatibility: 
Tested on Windows 7 x64 with multiscreen. It should work on any Windows.
Note that <windows.h> is used to emulate mouse clicks, this code will not
compile on operating systems other than Windows.
//
//
Copyright (C) 2012:               
              - Franck Dernoncourt <http://francky.me>
              - Neurosky team <http://neurosky.com>
This program is licensed under the Creative Commons
Attribution-Noncommercial-No Derivative Works 3.0 Unported license
<http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode>
//
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
Ideas to investigate:
* Being able to drag and drop would be great. However I am definitely not sure whether the eye blinking detection's accuracy and frequency would allow a smooth drag-and-drop.
* How bad is it to blink as many times as we use mouse clicks?
* Distinguishing left-click from right-click is currently impossible due to the fact that there is only one sensor, which mostly detects the left blinking (seems the left eye is the closest to the sensor).
* Is there any way to avoid that the program eats 100% CPU of a core? (apart from using Sleep())
* I find the headset quite incomfortable (it hurts my forehead) even though I find it not excessively intrusive. Please add your voice to the poll http://www.linkedin.com/groups/How-comfortable-is-NeuroSky-MindWave-3572341.S.130985046?view=&gid=3572341&type=member&item=130985046&trk=NUS_DISC_Q-ttle !
//
Any feedback/comments/ideas are welcome! --> franck.dernoncourt@gmail.com