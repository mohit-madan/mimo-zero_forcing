itload inv_capacity.it;
itload bd_capacity.it;
itload bd2_capacity.it;
itload bd1user_capacity.it;

[q,s] = qqplot(inv_capacity, "unif", 0, 1);
s = max(s) + min(s) - s;  #to get the ccdf of the function instead of cdf
p1 = plot(s,q, '*-r'); hold on

[q,s] = qqplot(bd_capacity, "unif", 0, 1);
s = max(s) + min(s) - s;  #to get the ccdf of the function instead of cdf
p2 = plot(s,q, '*-b'); hold on

[q,s] = qqplot(bd2_capacity, "unif", 0, 1);
s = max(s) + min(s) - s;  #to get the ccdf of the function instead of cdf
p3 = plot(s,q, '*-g'); hold on

[q,s] = qqplot(bd1user_capacity, "unif", 0, 1);
s = max(s) + min(s) - s;  #to get the ccdf of the function instead of cdf
p4 = plot(s,q, '*-c'); hold on

ylabel("Probability Capacity > Abscissa");
xlabel("Capacity(bits/use)");
title("Capacity CCDFDS for nt = 4 at 10 dB SNR");
legend([p1 p2 p3 p4], "Inversion", "Block Diag.{1,1,1,1}x4", "Block Diag {2,2} x 4", "1 user");
grid on;