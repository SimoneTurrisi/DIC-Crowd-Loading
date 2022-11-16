%%% 'run_incremental_dic.m' %%%
% Main program to call DICe to run incremental digital image correlation

clear
close all
clc

% Author: Simone Turrisi, 2022

%% Initialize parameters
prompt = {'Number of images to process:','Enter DIC step (px):'};
dlgtitle = 'Input';
dims = [1 35];
definput = {'9','6'};
answer = inputdlg(prompt,dlgtitle,dims,definput);

n_im = str2double(answer{1,1}); % number of image to process
step_dic = str2double(answer{2,1}); %DIC step size as specified in 'input.xml'

%% Run analysis
mkdir('solution') % folder to store DICe results (.txt)
mkdir('mat files') % folder to store results (.mat) --> 

for nc = 1:n_im

% Save images in folder required by DICe analysis
inputfold = 'Input images'; % folder containing original images to be analysed
DICefold = 'DICe images'; % folder containing images for analysis with DICe

% Reference image
I = imread([inputfold,'\image_',num2str(nc-1),'.tif']); 
imwrite(I,[DICefold,'\reference.tif']); 
% Deformed image
I = imread([inputfold,'\image_',num2str(nc),'.tif']); 
imwrite(I,[DICefold,'\deformed.tif']); 

% Run incremental DIC
[status,outcmd] = system('"C:\Program Files (x86)\Digital Image Correlation Engine\dice.exe" -i input.xml -v -t');
if status == 1
    disp('ERRORE DIC ABORTED')
end

[v,u,X,Y] = DICe_results_reader_complete(nc,step_dic); % save results in .mat format (eventually modify parameters of interest)

end

%%
