#define MAX_SAMPLE_RATE (48000)


struct PaData
{
    int channelCount;
};


void handleError(PaError err, std::string msg)
{
    if(err != paNoError)
    {
        std::cout << msg << std::endl;
        std::cout << "Error number: " << err << std::endl;
        std::cout << "Error message: " << Pa_GetErrorText(err) << std::endl;
    }

    exit(1);
}


void initPa()
{
    handleError(
        Pa_Initialize(), 
        "An error occured while initializing portaudio"
        );
}


void openStream(PaStream **stream, PaStreamParameters *inputParameters, PaStreamParameters *outputParameters, int sampleRate, PaStreamCallback callback, PaData *paData)
{
    handleError(
        Pa_OpenStream(
            stream, 
            inputParameters, outputParameters, 
            sampleRate, paFramesPerBufferUnspecified, 
            paNoFlag, callback, paData
            ), 
        "An error occured while opening the stream"
        );
}


void startStream(PaStream *stream)
{
    handleError(
        Pa_StartStream(stream), 
        "An error occured while starting the stream"
        );
}


void stopStream(PaStream *stream)
{
    handleError(
        Pa_StopStream(stream), 
        "An error occured while stopping the stream"
        );
}


void closeStream(PaStream *stream)
{
    handleError(
        Pa_CloseStream(stream), 
        "An error occured while closing the stream"
        );
}


void terminatePa()
{
    handleError(
        Pa_Terminate(), 
        "An error occured while terminating portaudio"
        );
}
