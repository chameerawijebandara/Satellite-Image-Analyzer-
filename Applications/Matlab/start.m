clear all;
close all;
%open & show image
I=imread('C:\Users\Dell\Desktop\Tree_project\image1.jpg');
figure,imshow(I);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%covert to binary & show
Binary = im2bw(I,0.45);
figure,imshow(Binary);
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
round(centers)
for i=1: r
   J(round(centers(i,2)),round(centers(i,1)),:) = [255,0,0];
   temp(round(centers(i,2)),round(centers(i,1)),:) = [255,255,255];
   k = imcrop(I,[round(centers(i,1))-3,round(centers(i,2))-3,6,6]);
   [rows,cols,d] = size(k);
   if(rows == 7 && cols == 7)
    img_count = img_count+1;
    str = sprintf('C:\\Users\\Dell\\Desktop\\Tree_project\\New folder\\MatLab\\%d.jpg',img_count);
    imwrite(k,str);
   end
end
figure,imshow(J);viscircles(centers,radii);

imwrite(uint8(temp),'C:\Users\Dell\Desktop\Tree_project\Matlab_image.jpg');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%show result
figure,imshow(cfiltereed);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



%mark the margin of trees in a new matrix
[r,c,d]=size(cfiltereed);
disp([r,c,d]);
margin = zeros(r,c);
outimage = zeros(r,c);
s=0;
for i=1:c-69
    t=0;
    for j=1:r-69
        s = sum(sum(cfiltereed(j:j+69,i:i+69)));
        if (s>1000)&&(t==0)
            t=1;
            margin(j,i) = 1;
        end

        if (s<1000)&&(t==1)
            t=0;
            margin(j+69,i) = 1;
        end
        
    end
end
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%call recurse show result- recurse will turn a white area in to a single pixel
set(0,'RecursionLimit',1000);
for i=2:c
    for j=4:r-3
        if(cfiltereed(j,i)==1)
            [cfiltereed,e] = recurse(cfiltereed,i,j,0);
              if(e==0)
                cfiltereed(j,i) = 1;
                outimage(j-3:j+3,i-1) = 1;
                I(j-3:j+3,i-1,1) = 255;
              end
        end
    end
end
cfiltereed = outimage;
figure,imshow(cfiltereed);
figure,imshow(I);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%create a rgb image correspond to previouse image
temp = zeros(r,c,3);
for i=1:c
    for j=1:r
        temp(j,i,1:3) = [255*cfiltereed(j,i),255*cfiltereed(j,i),255*cfiltereed(j,i)];
    end
end
% imwrite(uint8(temp),'C:\Users\Dell\Desktop\Tree_project\Matlab_image.jpg');
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%mark the margin using 'margin' matrix in red colour & show result
for i=1:c-5
    for j=1:r
        if(margin(j,i)==1)
            temp(j,i,1:3) = [255,0,0];
            temp(j,i+1,1:3) = [255,0,0];
        end
    end
end
% figure,imshow(temp);
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



