# AudioProgramming - Exercises
## Exercise 01
Using OpenAL, this exercise has to implement a basics _CAudioBuffer_, _CAudioSource_ and _CAudioListener_ classes to handle with audio files.
First of all, CAudioBuffer has the logic to read (only) **wav** files. Then it generates a OpenAL buffer which can be used in _CAudioSource_. To read a **wav** file use:
``
CAudioBuffer::Load(filename);
``
This returns a pointer to new audio buffer which must be use to create a CAudioSource instance. To destroy this buffer use:
``
CAudioBuffer::Destroy(audioBuffer);
``
## Exercise 02 - WIP
