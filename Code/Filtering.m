%Filtering

f = [zeros(5,3),ones(5,2)];
h = ones(3,3);

g = imfilter(f,h);

%% Border Handling - Zero padding

im1 = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\Gaussian.png');
imshow(im1);

fsize = 5;
h = ones(fsize)/fsize^2;

meanim1 = imfilter(im1,h);

figure
subplot(3,2,1);
imshow(im1), colormap(gca,gray), axis image off;
title('Original image')
subplot(3,2,2);
imshow(meanim1), colormap(gca,gray), axis image off;
title('Filtered image, mean filter')
subplot(3,2,3);
imshow(meanim1), colormap(gca,hot), axis image off;
title('Hot')
subplot(3,2,4);
imshow(meanim1), colormap(gca,summer), axis image off;
title('Cyan')
subplot(3,2,5);
imshow(meanim1), colormap(gca,jet), axis image off;
title('Jet')
subplot(3,2,6);
imshow(meanim1), colormap(gca,pink), axis image off;
title('Pink')

%% Replicate ( mirror nearest pixel)

im1 = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\Gaussian.png');

fsize = 5;
h = ones(fsize)/fsize^2;

meanim2 = imfilter(im1,h, 'replicate');

figure
subplot(1,2,1);
imshow(im1), colormap(gca,gray), axis image off;
title('Original image')
subplot(1,2,2);
imshow(meanim2), colormap(gca,gray), axis image off;
title('Filtered image, mean filter using replicate')
%outside edges are a little sharper

%% Size of kernel filter

im1 = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\Gaussian.png');
imshow(im1);

meanim5 = imfilter(im1,ones(5)/5^2, 'replicate');
meanim10 = imfilter(im1,ones(10)/10^2, 'replicate');
meanim15 = imfilter(im1,ones(15)/15^2, 'replicate');

figure
subplot(2,2,1);
imshow(im1), colormap(gca,gray), axis image off;
title('Original image')
subplot(2,2,2);
imshow(meanim5), colormap(gca,gray), axis image off;
title('5x5 filter')
subplot(2,2,3);
imshow(meanim10), colormap(gca,gray), axis image off;
title('10x10 filter')
subplot(2,2,4);
imshow(meanim15), colormap(gca,gray), axis image off;
title('15x15 filter')

%The bigger the size of the filter, the more blurry the picture will be.
%The edges ( big crossovers in the picture) become harder to distinguish

%% Median filter

im1 = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\Gaussian.png');
imshow(im1);

meanim5 = imfilter(im1,ones(5)/5^2, 'replicate'); %mean filter
medim5 = medfilt2(im1, [5 5]); %median filter
medim10 = medfilt2(im1, [10 10]); %median filter
medim15 = medfilt2(im1, [15 15]); %median filter
medim20 = medfilt2(im1, [20 20]); %median filter


figure
subplot(2,3,1);
imshow(im1), colormap(gca,gray), axis image off;
title('Original image')
subplot(2,3,2);
imshow(meanim5), colormap(gca,gray), axis image off;
title('5x5 mean filter')
subplot(2,3,3);
imshow(medim5), colormap(gca,gray), axis image off;
title('5x5 median filter')
subplot(2,3,4);
imshow(medim10), colormap(gca,gray), axis image off;
title('10x10 median filter')
subplot(2,3,5);
imshow(medim15), colormap(gca,gray), axis image off;
title('15x15 median filter')
subplot(2,3,6);
imshow(medim20), colormap(gca,gray), axis image off;
title('20x20 median filter')

%A small mean filter is very effective at removing noise.
%A larger mean filter makes the image blurry and makes the border creep
%into the image

%% Both mean and median

im1 = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\SaltPepper.png');
imshow(im1);

h = ones(fsize)/fsize^2;

meanThenMed = medfilt2(imfilter(im1,ones(5)/5^2, 'replicate')); %mean filter
med = medfilt2(im1, [5 5]);
medThenMean = imfilter(med,ones(5)/5^2, 'replicate'); %median filter

meanThenMed3 = medfilt2(medfilt2(medfilt2(imfilter(im1,ones(5)/5^2, 'replicate')))); %mean filter

figure
subplot(2,3,1);
imshow(im1), colormap(gca,gray), axis image off;
title('Original image')
subplot(2,3,2);
imshow(meanThenMed), colormap(gca,gray), axis image off;
title('Mean then median')
subplot(2,3,3);
imshow(medThenMean), colormap(gca,gray), axis image off;
title('Median then mean')
subplot(2,3,4);
imshow(medfilt2(im1)), colormap(gca,gray), axis image off;
title('Median')
subplot(2,3,5);
imshow(imfilter(im1,ones(5)/5^2,'replicate')), colormap(gca,gray), axis image off;
title('Mean')
subplot(2,3,6);
imshow(meanThenMed3), colormap(gca,gray), axis image off;
title('Mean then meadian*3')

%Mean basically ruins the picture :(

%% fspecial
im1 = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\SaltPepper.png');
imshow(im1);

averageFilter = fspecial('average',5);

fsize = 5;
h = ones(fsize)/fsize^2;

fspecialIm = imfilter(im1,averageFilter);
meanIm = imfilter(im1,h);
fspecialimsize15 = imfilter(im1,fspecial('average',15));


figure
subplot(1,4,1);
imshow(im1), colormap(gca,gray), axis image off;
title('Original image')
subplot(1,4,2);
imshow(fspecialIm), colormap(gca,gray), axis image off;
title('fSpecial')
subplot(1,4,3);
imshow(meanIm), colormap(gca,gray), axis image off;
title('Imfilter with h')
subplot(1,4,4);
imshow(fspecialimsize15), colormap(gca,gray), axis image off;
title('fSpceial 15x15')

%% Edge detection

CT = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\ElbowCTSlice.png');

CTprewitt = imfilter(CT,fspecial('prewitt'));
CTsobel = imfilter(CT,fspecial('sobel'));

figure
subplot(2,3,1);
imshow(CT,[]), colormap(gca,gray), axis image off;
title('Original image')
subplot(2,3,2);
imshow(CTprewitt,[]), colormap(gca,gray), axis image off;
title('Prewity 3x3')
subplot(2,3,3);
imshow(CTsobel,[]), colormap(gca,gray), axis image off;
title('Sobel 3x3')
subplot(2,3,4);
imshow(CTprewitt,[]), colormap(gca,jet), axis image off;
title('Prewity 3x3')
subplot(2,3,5);
imshow(CTsobel,[]), colormap(gca,jet), axis image off;
title('Sobel 3x3')

%% rotate the kernel 


CT = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\ElbowCTSlice.png');

CTprewitt = imfilter(CT,fspecial('prewitt'));
CTsobel = imfilter(CT,fspecial('sobel'));
CTprewittInverted = imfilter(CT,-fspecial('prewitt')); %using - to turn around
CTsobelInverted = imfilter(CT,-fspecial('sobel'));
CTprewittVertical = imfilter(CT,fspecial('prewitt')'); %using ' to transpose
CTsobelVertical = imfilter(CT,-fspecial('sobel')');

figure
subplot(5,2,1);
imshow(CT,[]), colormap(gca,gray), axis image off;
title('Original image')
subplot(5,2,3);
imshow(CTprewitt,[]), colormap(gca,gray), axis image off;
title('Prewity 3x3')
subplot(5,2,4);
imshow(CTsobel,[]), colormap(gca,gray), axis image off;
title('Sobel 3x3')
subplot(5,2,5);
imshow(CTprewittInverted,[]), colormap(gca,gray), axis image off;
title('Prewity 3x3 rotated')
subplot(5,2,6);
imshow(CTsobelInverted,[]), colormap(gca,gray), axis image off;
title('Sobel 3x3 rotated')
subplot(5,2,7);
imshow(CTprewittVertical,[]), colormap(gca,gray), axis image off;
title('Prewity 3x3 rotated')
subplot(5,2,8);
imshow(CTsobelVertical,[]), colormap(gca,gray), axis image off;
title('Sobel 3x3 rotated')

%% Mean and median then edge filtering

CT = imread('C:\Users\Dreun\Google Drive\DTU\Billedanalyse\Data\ElbowCTSlice.png');

CTmean = imfilter(CT,fspecial('average',5));
CTmeansobel = imfilter(CTmean,fspecial('sobel'));

CTmedian = medfilt2(CT,[5 5]);
CTmediansobel = imfilter(CTmedian,fspecial('sobel'));

figure
subplot(2,3,1);
imshow(CT,[]), colormap(gca,gray), axis image off;
title('Original image')
subplot(2,3,2);
imshow(CTmean,[]), colormap(gca,gray), axis image off;
title('Mean image')
subplot(2,3,3);
imshow(CTmeansobel,[]), colormap(gca,gray), axis image off;
title('Sobel after mean')
subplot(2,3,4);
imshow(CT,[]), colormap(gca,gray), axis image off;
title('Original image')
subplot(2,3,5);
imshow(CTmedian,[]), colormap(gca,gray), axis image off;
title('Median image')
subplot(2,3,6);
imshow(CTmediansobel,[]), colormap(gca,gray), axis image off;
title('Sobel after median')

% This almoist removes the unclear (hard to detect) edge

