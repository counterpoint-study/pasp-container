#include<cmath>
#include<stk/FileWvOut.h>
#include<stk/Clarinet.h>
inline float mtof(unsigned char const note) {
    return 220 * exp2( ( note - 36 ) / 12.0 );
}
int main(int argc, char ** argv) {
    using namespace stk;
    
    // define SampleRate
    double const Fs = 16000;

    // initialize STK
    Stk::setRawwavePath("/usr/local/share/stk");
    Stk::setSampleRate(Fs);

    // Synthesize to wav file
    FileWvOut writer("output.wav", 1, FileWrite::FILE_WAV, FileWrite::STK_SINT16, Fs);

    // Prepare instruments
    Clarinet clarinet(220);

    // Synthesize routine
    for ( int k = 0, K = 10 * Fs ; k < K ; ++ k ) {

        // Programmed notes
        if ( k == 0 * Fs ) clarinet.noteOn(mtof(48), 0.5);
        else if ( k == 1 * Fs ) clarinet.noteOn(mtof(50), 0.5);
        else if ( k == 2 * Fs ) clarinet.noteOn(mtof(52), 0.5);
        else if ( k == 3 * Fs ) clarinet.noteOn(mtof(53), 0.5);
        else if ( k == 4 * Fs ) clarinet.noteOn(mtof(55), 0.5);
        else if ( k == 5 * Fs ) clarinet.noteOn(mtof(57), 0.5);
        else if ( k == 6 * Fs ) clarinet.noteOn(mtof(59), 0.5);
        else if ( k == 7 * Fs ) clarinet.noteOn(mtof(60), 0.5);
        else if ( k == 8 * Fs ) clarinet.controlChange(11, 22);
        
        // Generate output
        float const output = clarinet.tick();

        // Append into wavfile
        writer.tick(output);

    }

    // Exit
    return 0;
}