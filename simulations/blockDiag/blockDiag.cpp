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
	for(int j=0;j<t_size;j++){
		Hsbar = Hs;
		Hsbar.del_row(j);
		svd(Hsbar, u, s, v);	
		null_rank =  rank(diag(s, 0), tol);									// rank of the singular value matrix
		right_null = v.get_cols(null_rank ,t_size-1);				//right null space
		svd(Hs.get_rows(j,j)*right_null, u_j, s_j, v_j);
		right_rank = rank(diag(s_j,0), tol);
		right_vec = v_j.get_cols(0, right_rank - 1);
		modul_mat = concat_horizontal(modul_mat, right_null * right_vec);
		sigma = concat(sigma ,s_j.get(0,rank(diag(s_j,0))-1));
	}
	power_loading = diag(sqrt(waterfilling(sigma, snr)));		// calculating the power loading matrix using waterfilling
	modul_mat = modul_mat * power_loading;
	bd_capacity(i) = log2(real(det(I + snr * Hs * modul_mat * hermitian_transpose(Hs * modul_mat))));
	}
	cout << "Saving results to bd_capacity.it" << endl;
	file.open("bd_capacity.it");
	file << Name("bd_capacity") << bd_capacity;
	file.close();	
	return 0;	
}