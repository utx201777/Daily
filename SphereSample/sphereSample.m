%%
% 生成球面上均匀采样的点

function [] = sphereSample()

data = [];
N =20;
fi = (sqrt(5)-1)/2;
for i =1:N
    z = (2*i-1)/N -1;
    x = sqrt(1-z*z) * cos(2 *pi *i*fi);
    y = sqrt(1-z*z) * sin(2 *pi *i*fi);
    d = [x,y,z];
    data = [data;d];
end
scatter3(data(:,1),data(:,2),data(:,3),'filled')