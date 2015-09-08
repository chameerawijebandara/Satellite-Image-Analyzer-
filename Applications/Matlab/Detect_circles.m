read_location = 'image.jpg';
save_location = 'Matlab_image.jpg';
%open & show image
I=imread(read_location);
figure,imshow(I);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%covert to binary & show
Binary = im2bw(I,0.45);
% figure,imshow(Binary);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%create a filter          
filter =  fspecial('gaussian',5,1.2);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%apply the filter & invert the binary image
Binary = imcomplement(Binary);
cfiltereed = imfilter(Binary,filter);
[centers, radii] = imfindcircles(imcomplement(cfiltereed),[2 3],'ObjectPolarity','dark','Sensitivity',1);
J = I;
[r,c,d] = size(I);
temp = zeros(r,c,d);
[r,c]=size(centers);
img_count = 0;
% round(centers)
for i=1: r
   J(round(centers(i,2)),round(centers(i,1)),:) = [255,0,0];
   temp(round(centers(i,2)),round(centers(i,1)),:) = [255,255,255];
   
end
figure,imshow(J);viscircles(centers,radii);

imwrite(uint8(temp),save_location);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%show result
figure,imshow(cfiltereed);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



