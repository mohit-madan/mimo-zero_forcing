#include <itpp/itcomm.h>
using namespace itpp;
//These lines are needed for use of cout and endl
using std::cout;
using std::endl;
int main()
{

  int i, Number_of_bits;
  double Ec, Eb;
  vec EbN0dB, EbN0, N0, noise_variance, bit_error_rate, fade; //vec is a vector containing double
  bvec transmitted_bits, received_bits;                 //bvec is a vector containing bits
  cvec transmitted_symbols, received_symbols, fade_c;           //cvec is a vector containing double_complex

  //Declarations of classes:
  QAM qam;                       //The QPSK modulator class
  qam.set_M(8);
  AWGN_Channel awgn_channel;     //The AWGN channel class
  it_file ff;                    //For saving the results to file
  BERC berc;                     //Used to count the bit errors
  Real_Timer tt;                 //The timer used to measure the execution time
  //Reset and start the timer:
  tt.tic();
  //Init:
  Ec = 1.0;                      //The transmitted energy per QPSK symbol is 1.
  Eb = Ec / 3.0;                 //The transmitted energy per bit is 0.5.
  EbN0dB = linspace(0.0, 9.0, 10); //Simulate for 10 Eb/N0 values from 0 to 9 dB.
  EbN0 = inv_dB(EbN0dB);         //Calculate Eb/N0 in a linear scale instead of dB.
  N0 = Eb * pow(EbN0, -1.0);     //N0 is the variance of the (complex valued) noise.
  //Number_of_bits = 100000;       //One hundred thousand bits is transmitted for each Eb/N0 value
  Number_of_bits = 99999;
  //Declarations of scalars and vectors:
  TDL_Channel my_channel; 
  // The normalized Doppler frequency is set to 0.1
  double norm_dopp = 0.1;
  my_channel.set_norm_doppler(norm_dopp);
  // Generate nrof_samples of the fading process and store them in ch_coeffs
  // matrix
  int nrof_samples = Number_of_bits/3;
  cmat ch_coeffs;
  my_channel.generate(nrof_samples, ch_coeffs);


  //Allocate storage space for the result vector.
  //The "false" argument means "Do not copy the old content of the vector to the new storage area."
  bit_error_rate.set_size(EbN0dB.length(), false);
  //Randomize the random number generators in it++:
  RNG_randomize();
  //Iterate over all EbN0dB values:
  for (i = 0; i < EbN0dB.length(); i++) {
  //for (i = 0; i < 1; i++) {
    //Show how the simulation progresses:
    cout << "Now simulating Eb/N0 value number " << i + 1 << " of " << EbN0dB.length() << endl;
    //Generate a vector of random bits to transmit:
    transmitted_bits = randb(Number_of_bits);
    
    fade_c = to_cvec(randray(nrof_samples)); //bpsk
    
    //Modulate the bits to QPSK symbols:
    transmitted_symbols = qam.modulate_bits(transmitted_bits);
    for(int j=0;j < nrof_samples;j++){
      transmitted_symbols(j) = transmitted_symbols(j) * fade_c(j);
    }

    //transmitted_symbols = fade * transmitted_symbols;
    //Set the noise variance of the AWGN channel:
    awgn_channel.set_noise(N0(i));
    //Run the transmited symbols through the channel using the () operator:
    received_symbols = awgn_channel(transmitted_symbols);
    
   for(int j=0;j < nrof_samples;j++){
     received_symbols(j) = received_symbols(j) / fade_c(j);
   }
 
    //Demodulate the received QPSK symbols into received bits:
    received_bits = qam.demodulate_bits(received_symbols);

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
  cout << "Saving results to ./qam8fcc_result_file.it" << endl;

  cout << endl;
  //Save the results to file:
  ff.open("qam8fcc_result_file.it"); 

  ff << Name("EbN0dB") << EbN0dB;
  ff << Name("ber") << bit_error_rate;
  ff.close();
  //Exit program:
  return 0;
}

