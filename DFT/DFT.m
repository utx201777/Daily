%%
% 测试dft
function [] = testDFT()
    N =8;
    n = [0:1:N-1];
    xn = 0.5.^n;        % 指数信号
    
    I=imread('lenna.jpg');
    I=rgb2gray(I);
    I=im2double(I);
    figure(8);
    imshow(I);
    
    %imagefft();
    imageDFT2fft();
    %imageDFT2();
    %imageDFT();
    %DFTusefft(xn,n,N);  % 使用fft实现
    %DFT(xn,n,N);
    %testDTFT(xn,n,N);
end

%%
% 图像的二维DFT
% 对DFT进行分解，先按列进行FFT，然后按行FFT（使用内置的fft代替dft）
function [] = imageDFT2fft()
    I=imread('lenna.jpg');
    I=rgb2gray(I);
    I=im2double(I);
    [x,y] = size(I);
    Ax = ones(x,y);
    ans = ones(x,y);
    com = 0+1i;
    % 对每一列进行DFT  
    for m=1:y
        Ax(:,m) = fft(I(:,m));
    end
    % 对每一行进行DFT    
    for k=1:x
        ans(k,:) = fft(Ax(k,:));
    end
    F=fftshift(ans);
    F= abs(F);
    F=log(F+1);
    figure(7);
    imshow(F,[]);
end

%%
% 图像的二维DFT
% 对DFT进行分解，先按列进行DFT，然后按行DFT
function [] = imageDFT2()
    I=imread('lenna.jpg');
    I=rgb2gray(I);
    I=im2double(I);
    [x,y] = size(I);
    Ax = ones(x,y);
    ans = ones(x,y);
    com = 0+1i;
    % 对每一列进行DFT
    for k =1:x        
        for m=1:y
            sn =0;
            for n =1:x
                sn =sn + I(n,m)*exp(-com*2*pi*k*n/x);
            end
            Ax(k,m) = sn;
        end
    end
    % 对每一行进行DFT
    for l =1:y
        for k =1:x
            sn =0;
            for m=1:y
                sn = sn+Ax(k,m)*exp(-com*2*pi*l*m/y);
            end
            ans(k,l) = sn;
        end
    end    
    F=fftshift(ans);
    F= abs(F);
    F=log(F+1);
    figure(6);
    imshow(F,[]);
end

%%
% 图像的二维DFT
% 直接进行原始的二维DFT，四层循环
function [] = imageDFT()
    I=imread('lenna_s.jpg');
    I=rgb2gray(I);
    I=im2double(I);
    [x,y] = size(I);
    ans = ones(x,y);
    com = 0+1i;
    for u =1:x
        for v= 1:y
            sn =0;
            for i=1:x                
                for j=1:y
                    sn = sn+I(i,j)*exp(-com*2*pi*(u*i/x+v*j/y));
                end
            end
            ans(u,v) = sn;
        end
    end
    F=fftshift(ans);
    F= abs(F);
    F=log(F+1);
    figure(5);
    imshow(F,[]);
end

%%
% 图像的二维DFT
% 使用内置的fft2
function [] = imagefft()
    I=imread('lenna.jpg');
    I=rgb2gray(I);
    I=im2double(I);
    F=fft2(I);
    F=fftshift(F);
    F=abs(F);
    T=log(F+1);
    figure(4);
    imshow(T,[]);
end

%%
% 一维DFT
function [] = DFT(xn,n,N)
    Xk = zeros(1,N);    
    for k=1:N
        sn =0.0;
        for i=1:N
            sn = sn+xn(i)*exp(-j*2*pi*i*k/N);
        end
        Xk(k) = sn;
    end
    figure(2);
    %Xk=fft(xn,N);       % 傅立叶变换
    subplot(211);
    stem(n,xn);
    title('原信号');

    subplot(212);
    stem(n,abs(Xk));
    title('DFT')
end

%%
% 一维fft
function [] = DFTusefft(xn,n,N)
    figure(1);
    Xk=fft(xn,N);       % 傅立叶变换
    subplot(211);
    stem(n,xn);
    title('原信号');

    subplot(212);
    stem(n,abs(Xk));
    title('FFT变换')
end

%% 
% 一维dtft
function [] = testDTFT(xn,n,N)
    figure(3);
    w=[-800:1:800]*4*pi/800;     %频域共-800----+800 的长度（本应是无穷，高频分量很少，故省去）    
    w = [-N/2:1:N/2]*4*pi*2/N;
    X=xn*exp(-j*(n'*w));         %求dtft变换，采用原始定义的方法，对复指数分量求和而得
    subplot(211)
    stem(n,xn);
    title('原始信号(指数信号)');
    subplot(212);
    plot(w/pi,abs(X));
    title('DTFT变换')
end

