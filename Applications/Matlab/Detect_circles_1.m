read_location = 'image.png';
save_location = 'Matlab_image.jpg';

%open & show image
I=imread(read_location);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%covert to binary & show
Binary = im2bw(I,0.45);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%create a filter          
filter =  fspecial('gaussian',5,1.2);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%apply the filter & invert the binary image
Binary = imcomplement(Binary);
cfiltereed = imfilter(Binary,filter);
[centers, radii] = imfindcircles(imcomplement(cfiltereed),[2 3],'ObjectPolarity','dark','Sensitivity',1);
[r,c,d] = size(I);
temp = zeros(r,c,d);
[r,c]=size(centers);
% round(centers)
for i=1: r
   temp(round(centers(i,2)),round(centers(i,1)),:) = [255,255,255];
   
end

imwrite(uint8(temp),save_location);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



