#include <itpp/itcomm.h>
#include <cmath>
#include <itpp/stat/misc_stat.h>
using namespace itpp;
using std::cout;
using std::endl;

int main()
{

	int t_size = 4;
	double tol = -1.0, snr = 10.0; 
	cmat Hs, u, v, I;
	vec sigma,Inversion_capacity, y, cdf;
	it_file file;
	eye(t_size, I);


	Inversion_capacity.set_size(500, false);
	
	RNG_randomize();
	for(int i=0;i<500;i++){
		Hs = randn_c(t_size,t_size);
		svd(Hs, u, sigma, v);
		Inversion_capacity(i) = log2(real(det(I + (snr/energy(sigma)) * I)));
		}
	cout << "Saving results to inv_capacity.it" << endl;
	file.open("inv_capacity.it");
	file << Name("inv_capacity") << Inversion_capacity;
	file.close();	
	return 0;	
}

