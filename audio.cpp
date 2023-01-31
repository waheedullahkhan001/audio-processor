#include <iostream>
#include <portaudio.h>
#include <soundtouch/SoundTouch.h>
#include "audio.h"
#include "autil.h"


using namespace std;
using namespace soundtouch;


SoundTouch soundTouch;

float pitchSemiTones   = -16;
float volumeMultiplier = 1.3;


int audioCallback(
                    const void                     *inputBuffer,
                    void                           *outputBuffer,
                    unsigned long                   framesPerBuffer,
                    const PaStreamCallbackTimeInfo *timeInfo,
                    PaStreamCallbackFlags           statusFlags,
                    void                           *paData
                )
{
    float  *in       = (float* ) inputBuffer;
    float  *out      = (float* ) outputBuffer;
    PaData *userData = (PaData*) paData;

    soundTouch.setSampleRate(1); // I found this to be working the best.
    soundTouch.setChannels(userData->channelCount);
    soundTouch.setPitchSemiTones(pitchSemiTones);

    soundTouch.putSamples(in, framesPerBuffer);
    soundTouch.receiveSamples(out, soundTouch.numSamples());

    for (int i = 0; i < soundTouch.numSamples(); i++)
    {
        for (int j = 0; j < userData->channelCount; j++)
        {
            *out++ = *out * volumeMultiplier;
        }
        
    }

    return 0;
}


int main()
{
    PaStream *stream;
    PaData    data;
    PaStreamParameters inputParameters, outputParameters;
    int inputDevice, outputDevice, channelCount, sampleRate, choice;

    
    Pa_Initialize();

    inputDevice  = Pa_GetDefaultInputDevice();
    outputDevice = Pa_GetDefaultOutputDevice();
    channelCount = getChannelCount(inputDevice, outputDevice);
    sampleRate   = getSampleRate(&inputParameters, &outputParameters);

    data.channelCount = channelCount;

    setParams(
        &inputParameters, 
        &outputParameters, 
        inputDevice, 
        outputDevice, 
        data.channelCount
    );

    Pa_OpenStream(
        &stream, 
        &inputParameters, 
        &outputParameters, 
        sampleRate, 
        paFramesPerBufferUnspecified, 
        paNoFlag, audioCallback, 
        &data
    );
    Pa_StartStream(stream);

    
    while (volumeMultiplier > 0)
    {
        cout << "0. Exit.\n";
        cout << "1. Volume Multiplier (Current: " << volumeMultiplier << ")\n";
        cout << "2. Pitch (in Semitones) (Current: " << pitchSemiTones << ")\n";
        cout << "^\tEnter your choice: ";
        cin  >> choice;

        if (choice == 0)
        {
            cout << "Exiting...\n";
            break;
        }
        else if (choice == 1)
        {
            cout << "Enter new value for volume multiplier: ";
            cin >> volumeMultiplier;
        }
        else if (choice == 2)
        {
            cout << "Enter new value for pitch: ";
            cin >> pitchSemiTones;
        }
        else
        {
            cout << "Please select a valid option." << endl;
        }
        
    }
    

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}
