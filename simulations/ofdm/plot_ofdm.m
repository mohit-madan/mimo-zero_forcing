itload ../qam/qam4_result_file.it;
h1 = semilogy(EbN0dB,ber,'*-r'); hold on

itload ../qam_fading_correct/qam4fcc_result_file.it;
h2 = semilogy(EbN0dB,ber,'*-b'); hold on

itload qam4ofdm_result_file.it;
h3 = semilogy(EbN0dB,ber,'*-g'); hold on

set(gca,'fontname','times','fontsize',16);
xlabel('{\it E_b} / {\it N}_0 [dB]');
ylabel('BER')
title('QAM on an AWGN Channel');
legend([h1 h2 h3],'QAM-4','QAM-4-fadc','QAM-4-ofdm');
grid on;