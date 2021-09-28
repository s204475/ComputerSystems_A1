%Lesson3 4 - Filtering

%The file Image1.mat contains a synthetic image created to understand the basic
%operations erosion and dilation. 

load Image1.mat
imagesc(Image1)
imagegrid(gca,size(Image1));
colormap(gca,hot);
