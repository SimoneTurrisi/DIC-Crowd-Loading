%%% 'rename_images_DICe.m' %%%
% Program to rename images according to DICe software:
% * ex: 'image_0.tif'

clear
close all
clc

%% Load image list
startpath = 'F:\San Siro\Crowd Behaviour\Tesi_Nerea_Miguel\20191202_Test_SanSiro\20191202_SanSiro\EoSens Mini2'; % to be modified
folder_name = uigetdir(startpath,'Select folder containing images...');
imagelist = dir(folder_name);
imagelist(1:2) = [];
% nim = length(imagelist);
nim = 30;

% Folder where to save renamed images
savefold = 'F:\San Siro\Crowd Behaviour\Tesi_Nerea_Miguel\DICe\DICe Example\Input images\'; 

for ii=1:nim
    oldname = imagelist(ii).name;
    newname = ['image_',num2str(ii-1),'.tif']; % from 0 to nim-1
    I = imread([folder_name,'\',oldname]);
    imwrite(I,[savefold,newname]);    
end

%%
