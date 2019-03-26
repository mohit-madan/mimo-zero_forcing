figure();
itload qam/qam4_result_file.it;
h1 = semilogy(EbN0dB,ber,'*-r'); hold on

itload qam_fading/qam4f_result_file.it;
h2 = semilogy(EbN0dB,ber,'*-b'); hold on

itload qam_fading_correct/qam4fcc_result_file.it;
h3 = semilogy(EbN0dB,ber,'*-g'); hold on

set(gca,'fontname','times','fontsize',16);
xlabel('{\it E_b} / {\it N}_0 [dB]');
ylabel('BER')
title('QAM on an AWGN Channel');
legend([h1 h2 h3],'QAM-4','QAM-4-fad','QAM-4-fad-correct');
grid on;

figure();
itload qam/qam8_result_file.it;
h4 = semilogy(EbN0dB,ber,'*-y'); hold on

itload qam_fading/qam8f_result_file.it;
h5 = semilogy(EbN0dB,ber,'*-m'); hold on

itload qam_fading_correct/qam8fcc_result_file.it;
h6 = semilogy(EbN0dB,ber,'*-g'); hold on

set(gca,'fontname','times','fontsize',16);
xlabel('{\it E_b} / {\it N}_0 [dB]');
ylabel('BER')
title('QAM on an AWGN Channel');
legend([h4 h5 h6],'QAM-8','QAM-8-fad','QAM-8-fad-correct');
grid on;

figure();
itload qam/qam16_result_file.it;
h7 = semilogy(EbN0dB,ber,'*-o'); hold on

itload qam_fading/qam16f_result_file.it;
h8 = semilogy(EbN0dB,ber,'*-g'); hold on

itload qam_fading_correct/qam16fcc_result_file.it;
h9 = semilogy(EbN0dB,ber,'*-b'); hold on

set(gca,'fontname','times','fontsize',16);
xlabel('{\it E_b} / {\it N}_0 [dB]');
ylabel('BER')
title('QAM on an AWGN Channel');
legend([h7 h8 h9],'QAM-16','QAM-16-fad','QAM-16-fad-correct');
grid on;


