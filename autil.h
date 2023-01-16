int getChannelCount(int inputDevice, int outputDevice)
{
    const PaDeviceInfo *inputDeviceInfo = Pa_GetDeviceInfo(inputDevice);
    const PaDeviceInfo *outputDeviceInfo = Pa_GetDeviceInfo(outputDevice);
    int channelCount = inputDeviceInfo->maxInputChannels;

    if(outputDeviceInfo->maxOutputChannels < channelCount) {
        channelCount = outputDeviceInfo->maxOutputChannels;
    }

    return channelCount;
}


void setParams(PaStreamParameters *inputParameters, PaStreamParameters *outputParameters, int inputDevice, int outputDevice, int channelCount) {
    const PaDeviceInfo *inputDeviceInfo = Pa_GetDeviceInfo(inputDevice);
    const PaDeviceInfo *outputDeviceInfo = Pa_GetDeviceInfo(outputDevice);

    inputParameters->channelCount = channelCount;
    inputParameters->device = inputDevice;
    inputParameters->sampleFormat = paFloat32;
    inputParameters->suggestedLatency = inputDeviceInfo->defaultLowInputLatency ;
    inputParameters->hostApiSpecificStreamInfo = NULL;

    outputParameters->channelCount = channelCount;
    outputParameters->device = outputDevice;
    outputParameters->sampleFormat = paFloat32;
    outputParameters->suggestedLatency = outputDeviceInfo->defaultLowOutputLatency ;
    outputParameters->hostApiSpecificStreamInfo = NULL;
}


int getSampleRate(PaStreamParameters *inputParameters, PaStreamParameters *outputParameters) {
    int sampleRate = 44100;

    for(int i = 48000; i >= 1; i--) {
        if(Pa_IsFormatSupported(inputParameters, outputParameters, i) == paFormatIsSupported) {
            sampleRate = i;
            break;
        }
    }

    return sampleRate;
}