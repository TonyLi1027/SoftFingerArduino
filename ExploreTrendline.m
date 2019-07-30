clear;
clc;
M = fopen('web_cam1.csv');
data = textscan(M,'%d %d %d %d','Delimiter',',');
out1 = data{1};
out2 = data{2};
out3 = data{3};
m = 1;

for v = 6.0:5.0:size(out2)
    out4(m,1) = out1(v);
    out4(m,2) = out2(v);
    out4(m,3) = out3(v);
    m = m + 1;
end
plot(out4(:,2));