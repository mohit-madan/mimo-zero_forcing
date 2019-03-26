#include <itpp/itcomm.h>
using namespace itpp;
using std::cout;
using std::endl;

/* order --hamm coding - modulate the bits into qam symbols - then ifft using ofdm function - channel fading using filter
 then fft using ofdm function - channel correction - demodulating the symbols to bits - hamm decoding */
int main()
{

  int i, Number_of_bits, inNfft, inNcp, inNupsample, paddedLength;
  double Ec, Eb;

  vec EbN0dB, EbN0, N0, noise_variance, bit_error_rate, fade; //vec is a vector containing double
  bvec transmitted_bits, received_bits,transmitted_bits_soft, received_bits_soft;                 //bvec is a vector containing bits
  cvec transmitted_symbols, h_vec, h_vec_ft, transmitted_symbols_pad, fade_c_pad, received_ofdm_symbols;           //cvec is a vector containing double_complex

  //Declarations of classes:
  QAM qam;                       //The QPSK modulator class
  qam.set_M(4);
  AWGN_Channel awgn_channel;     //The AWGN channel class
  Hamming_Code hamm(3);          // 7-4 hamming code constructor 
  OFDM ofdm;

  it_file ff;                    //For saving the results to file
  BERC berc;                     //Used to count the bit errors
  Real_Timer tt;                 //The timer used to measure the execution time
  //Reset and start the timer:
  tt.tic();
  //Init:
  const int one = 1;
  inNfft = 64;                   // size of FFT
  inNcp = 16;                     // size of cyclic prefix
  inNupsample = 1;               // default value
  Ec = 1.0;                      //The transmitted energy per QAM symbol is 1.
  Eb = Ec / 2.0;                 //The transmitted energy per bit is 0.5.
  EbN0dB = linspace(0.0, 9.0, 10.0);              //Simulate for 10 Eb/N0 values from 0 to 9 dB.
  EbN0 = inv_dB(EbN0dB);         //Calculate Eb/N0 in a linear scale instead of dB.
  N0 = Eb * pow(EbN0, -1.0);     //N0 is the variance of the (complex valued) noise.
  Number_of_bits = 64000;       //One hundred thousand bits is transmitted for each Eb/N0 value
  ofdm.set_parameters(inNfft, inNcp, inNupsample);
  //Declarations of scalars and vectors:
  
  int nrof_samples = Number_of_bits*7/(8*inNfft);

  
  //Allocate storage space for the result vector.
  //The "false" argument means "Do not copy the old content of the vector to the new storage area."
  bit_error_rate.set_size(EbN0dB.length(), false);
  //Randomize the random number generators in it++:
  RNG_randomize();
  h_vec = randn_c(4);	// h vector in odm // testing for size 2

  for (i = 0; i < EbN0dB.length(); i++) {
  // for (i = 0; i < 1; i++) {
    cvec transmitted_ofdm_symbols, received_symbols, received_symbols_new;
	
    //Show how the simulation progresses:
    cout << "Now simulating Eb/N0 value number " << i + 1 << " of " << EbN0dB.length() << endl;

    transmitted_bits = randb(Number_of_bits);
    transmitted_bits_soft = hamm.encode(transmitted_bits);

    //Modulate the bits to Qam symbols:
    transmitted_symbols = qam.modulate_bits(transmitted_bits_soft);
    transmitted_symbols = ofdm.modulate(transmitted_symbols);

    for(int j=0;j<nrof_samples;j++){
      transmitted_ofdm_symbols = concat(transmitted_ofdm_symbols,filter(h_vec, one, transmitted_symbols(j*(inNfft+inNcp), (j+1)*(inNfft+inNcp)-1)));      
    }
    
    //Set the noise variance of the AWGN channel:
    awgn_channel.set_noise(N0(i));
    //Run the transmited symbols through the channel using the () operator:
    received_ofdm_symbols = awgn_channel(transmitted_ofdm_symbols);

    received_symbols = ofdm.demodulate(received_ofdm_symbols);
    
    // equalization o the received ofdm symbols
    h_vec_ft = fft(h_vec, inNfft);	// n-point dft
    for(int j=0;j<nrof_samples;j++){
      received_symbols_new = concat(received_symbols_new, elem_div(received_symbols(j*inNfft, (j+1)*inNfft-1), h_vec_ft));
    }
    //Demodulate the received QPSK symbols into received bits:
    received_bits_soft = qam.demodulate_bits(received_symbols_new);
    received_bits = hamm.decode(received_bits_soft);

    //Calculate the bit error rate:
    berc.clear();                               //Clear the bit error rate counter
    berc.count(transmitted_bits, received_bits); //Count the bit errors
    bit_error_rate(i) = berc.get_errorrate();   //Save the estimated BER in the result vector
  }
  tt.toc();
  //Print the results:
  cout << endl;
  cout << "EbN0dB = " << EbN0dB << " [dB]" << endl;
  cout << "BER = " << bit_error_rate << endl;
  cout << "Saving results to ./qam4ofdm_result_file.it" << endl;

  cout << endl;
  //Save the results to file:
  ff.open("qam4ofdm_result_file.it"); 

  ff << Name("EbN0dB") << EbN0dB;
  ff << Name("ber") << bit_error_rate;
  ff.close();
  //Exit program:
  return 0;
}


