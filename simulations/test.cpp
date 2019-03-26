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
  bvec transmitted_bits, received_bits,transmitted_bits_soft, received_bits_soft;                 //bvec is a vector containing bits
  cvec transmitted_symbols, transmitted_symbols_pad, h_vec, fade_c_pad, received_ofdm_symbols, transmitted_ofdm_symbols, a,b;           //cvec is a vector containing double_complex
  const int one = 1;
  int inNfft = 4;                   // size of FFT
  int inNcp = 3;                     // size of cyclic prefix
  int inNupsample = 1;               // default value
 
  cvec random;
  //Declarations of classes:
  QAM qam;                       //The QPSK modulator class
  qam.set_M(4);
  AWGN_Channel awgn_channel;     //The AWGN channel class
  Hamming_Code hamm(3);          // 7-4 hamming code constructor 
  OFDM ofdm;
 
  ofdm.set_parameters(inNfft, inNcp, inNupsample);
  a = randn_c(8);
  cout << a.get(0,0);
  // h_vec = randn_c(2); // h vector in odm // testing for size 2
  // cout << "hvec : " << h_vec << "\n\n";
  // cout << "input : "<< a << "\n\n";

  // a = ofdm.modulate(a);
  // cout << "after ofdm" << a << "\n\n";

  // for(int i =0;i<2;i++){
  //     transmitted_symbols = concat(transmitted_symbols, filter(h_vec, one, a(i*7, (i+1)*7-1)));  
  // }
  
  // a = ofdm.demodulate(transmitted_symbols);
  // cout<< "fft of the output" << a << "\n\n";
  // // cout << fft(h_vec,4);
  //   for(int j=0;j<2;j++){
  //     b = concat(b, elem_div(a(j*4, (j+1)*4-1),fft(h_vec,4)));
  //   }
  // cout << "output" << b;


  // //Generate a vector of random bits to transmit:
  // transmitted_bits = randb(8);

    
  // transmitted_symbols = qam.modulate_bits(transmitted_bits);
  // cout << transmitted_symbols<< "\n";
  // transmitted_symbols = ofdm.modulate(transmitted_symbols);

  // transmitted_ofdm_symbols = filter(h_vec, one, transmitted_symbols);
  // // transmitted_ofdm_symbols = ma_filter.operator(transmitted_symbols);
  // cout << transmitted_symbols << "\n";
  // cout << transmitted_ofdm_symbols << "\n"; 

  return 0;
}
