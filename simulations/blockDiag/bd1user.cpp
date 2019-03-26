#include <itpp/itcomm.h>
#include <cmath>
#include <itpp/stat/misc_stat.h>
using namespace itpp;
using std::cout;
using std::endl;

int main()
{

  int snr = 10, L, null_rank, right_rank, t_size = 4;
  double tol = -1.0; 
  cmat Hs, u, v,u_j, v_j, Hsbar, right_null, right_vec, I;
  mat power_loading;
  vec s, s_j,bd_capacity, cdf;
  it_file file;
  eye(t_size, I);
  bd_capacity.set_size(500, false);
  RNG_randomize();

  // Block Diagnolisation, 1000 iterations {1,1,1,1} x 4 channel
  for(int i=0;i<500;i++){
	Hs = randn_c(4,t_size);
	vec sigma;
	cmat modul_mat;
	
	svd(Hs, u, s, v);	// only water filling in case of one user
	
	power_loading = diag(sqrt(waterfilling(s, snr)));		// calculating the power loading matrix using waterfilling
	bd_capacity(i) = log2(real(det(I + snr * Hs * power_loading * hermitian_transpose(Hs * power_loading))));
	}
	cout << "Saving results to bd1user_capacity.it" << endl;
	file.open("bd1user_capacity.it");
	file << Name("bd1user_capacity") << bd_capacity;
	file.close();	
	return 0;	
}

