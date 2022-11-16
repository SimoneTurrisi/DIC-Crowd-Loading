%%% 'rename_images_DICe.m' %%%
% Program to rename images according to DICe software:
% * ex: 'image_0.tif'

clear
close all
clc

% Author: Simone Turrisi, 2022

%% Load image list
startpath = cd;
folder_name = uigetdir(startpath,'Select folder containing images...');
imagelist = dir(folder_name);
imagelist(1:2) = [];
nim = length(imagelist);
savefold = 'Input images';  % folder where to save renamed images

for ii = 1:nim
    oldname = imagelist(ii).name;
    newname = ['image_',num2str(ii-1),'.tif']; % from 0 to nim-1
    I = imread([folder_name,'\',oldname]);
    imwrite(I,[savefold,newname]);    
end

%%
