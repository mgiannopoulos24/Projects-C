# Project Wavproc

The `wavproc.c` program which will read with getchar from the input audio data that following the wav standard described above and perform some processing on that data. Exactly what processing your program will perform will be determined by the value of a symbolic MODE constant that you set in it. The requested treatments,depending on the value of MODE are:

* MODE 1<br>
The program should check if the data read follows the wav standard that
previously described and print the relevant audio information. i.e.

  - size of file (in bytes)
  - size of format chunk 
  - WAVE type format
  - mono/stereo
  - sample rate
  - bytes per second
  - block alignment
  - bits/sample
  - size of data chunk

* MODE 2<br>
This mode transfers to the output, with the help of the putchar function, the audio data, having doubled
its playback speed, without altering the samples that make up the sampled sound.

* MODE 3<br>
This mode has a similar function to the previous section, where the sound at the input will be transferred to the output at twice the playback speed. 
Presumably, the time playback time will be doubled, since the samples that make up the sampled sound will be once again be transferred unaltered.

* MODE 4<br>
Τhis mode transfers to the output, with the help of the putchar function, the data of only the left channel of the audio, 
in case the input audio is stereo. If the input sound is mono, no signal is produced, but simply the single channel of the input.

* MODE 5<br>
With this mode the output will be the right channel of the input, in case of stereo sound at the input, or the single channel itself, in case of mono sound.

* MODE 6<br>
This mode switches to the output, with the help of the putchar function, the sound of the input to the output, but with reduced its intensity to 1/8 of the original.

* MODE 7<br>
This mode implements an audio generation function. It **does not read any data from the input** (stdin), but instead produces valid WAV audio data to the output (stdout), based on the following mathematical formula:
  
<center>

$f(t)=my \cdot sin(2\pi f_c t - m_i \cdot sin (2\pi f_m t))$

</center>
  
The arguments are:

| Parameter	| Description |
|-------------|-------------|
| dur	| Duration of the sound in seconds (float). |
| sr	| The Sample Rate (used as the `SampleRate` in the WAV header). |
| fm, fc	| The modulator and carrier frequencies in the formula (float). |
| mi, mv	| The modulation index and the maximum volume/amplitude (where π is the symbolic constant `M_PI` defined using `math.h`). |

The sound produced is Mono (`NumChannels` = 1) and is represented by 2 bytes per sample (`BitsPerSample` = 16).

**Note:** This project is the 2nd assignment of Introduction to Programming 2020-21 (Κ04) course of DIT NKUA.