#include <iostream>
#include <portaudio.h>
#include "audio.h"
#include "autil.h"


using namespace std;


float volumeMultiplier = 1;


int audioCallback(const void *inputBuffer, void *outputBuffer,
                  unsigned long framesPerBuffer,
                  const PaStreamCallbackTimeInfo* timeInfo,
                  PaStreamCallbackFlags statusFlags,
                  void *paData)
{
    unsigned int i, j;
    float *in = (float*)inputBuffer;
    float *out = (float*)outputBuffer;
    PaData *data = (PaData*)paData;

    for (i = 1; i <= framesPerBuffer; i++)
    {
        for (j = 1; j <= data->channelCount; j++)
        {
            *out++ = *in++ * (volumeMultiplier);
        }
    }

    return 0;
}


int main()
{
    PaStream *stream;
    PaData data;
    PaStreamParameters inputParameters, outputParameters;
    int inputDevice, outputDevice, channelCount, sampleRate;

    
    Pa_Initialize();

    inputDevice = Pa_GetDefaultInputDevice();
    outputDevice = Pa_GetDefaultOutputDevice();
    channelCount = getChannelCount(inputDevice, outputDevice);
    setParams(&inputParameters, &outputParameters, inputDevice, outputDevice, channelCount);
    sampleRate = getSampleRate(&inputParameters, &outputParameters);

    data.channelCount = channelCount;

    Pa_OpenStream(&stream, &inputParameters, &outputParameters, sampleRate, paFramesPerBufferUnspecified, paNoFlag, audioCallback, &data);
    Pa_StartStream(stream);

    
    while (volumeMultiplier > 0)
    {
        cout << "Enter volume multiplier value (0 to exit): ";
        cin >> volumeMultiplier;
        cout << "Setting volume multiplier to " << volumeMultiplier << endl;
    }
    

    Pa_StopStream(stream);
    Pa_CloseStream(stream);
    Pa_Terminate();

    return 0;
}
