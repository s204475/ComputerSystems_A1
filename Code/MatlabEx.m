realCell = imread('C:\Users\Dreun\OneDrive\Documents\GitHub\ComputerSystems_A1\Code\samples\easy\1EASYout.bmp');

imtool(realCell);

cellAr = [0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0;
    0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0;
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0;
    0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0;
    0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0;
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1;
    0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0;
    0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0;
    0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0;
    0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0;
    0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0;
    0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0];

%cell = imbinarize(cellAr);

%imshow(cell)

padCell = padarray(cellAr,[21 21],0,'both');

padIm = imbinarize(padCell);

imshow(padCell);

%1/(8 +12+ 15 +17 +19 +21 +23 +23 +23+ 23+ 23 +23 +23 +22+ 20 +19 +18 +16 +16+ 14+ 10+ 4)