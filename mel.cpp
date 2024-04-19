#include <iostream>
#include <vector>
#include <complex>
#include <string>
#include <fstream>
#include </content/drive/MyDrive/LibrosaCpp-main/librosa/librosa.h>
#include <sndfile.h>

std::vector<float> loadaudio(const std::string& filepath)
{
    SNDFILE* audiofile;
    SF_INFO audiofileinfo;
    audiofile = sf_open(filepath.c_str(), SFM_READ, &audiofileinfo);

    if (!audiofile)
    {
        std::cout << "Failed to open audio file: " << filepath << std::endl;
        return std::vector<float>();
    }

    std::vector<float> audiodata(audiofileinfo.frames);
    sf_read_float(audiofile, audiodata.data(), audiofileinfo.frames);
    sf_close(audiofile);

    return audiodata;
}

int main()
{
    std::string audiofilepath = "/content/audio1.wav";
    std::vector<float> audiodata = loadaudio(audiofilepath);

    if (!audiodata.empty())
    {
        int samplerate = 16000;
        int nfft = 2048;
        int hoplength = 512;
        int nmels = 128;
        int fmin = 0;
        int fmax = samplerate ;

        std::vector<std::vector<float>> melSpectrogram = librosa::Feature::melspectrogram(audiodata, samplerate, nfft, hoplength, "hann", true, "reflect", 1.0f, nmels, fmin, fmax);
        std::ofstream outputfile("mel_spectrogram_cpp.txt");

        if (outputfile.is_open())
        {
            outputfile <<"("<< melSpectrogram.size() << ", " << melSpectrogram[0].size()<<")" << std::endl;
            outputfile.close();

            std::cout << "Mel spectrogram shape saved to mel_spectrogram_cpp.txt" << std::endl;
        }
        else
        {
            std::cout << "Failed to open the output file" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to load audio file: " << audiofilepath << std::endl;
    }

    return 0;
}
