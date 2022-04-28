
%% 
nc=1; % to iniciate
number_deformed_images=9;  % number of deformed images

for nc=1:number_deformed_images
%% Input Parameters
step_dic = 6; % DIC step

%% Save images in folder required by DICe analysis
inputfold = 'Input images'; % folder containing original images to be analysed
DICefold = 'DICe images'; % folder containing images for analysis with DICe
mkdir('solution') % folder to store DICe results (.txt)
mkdir('Mat files') % folder to store results (.mat)

% Reference image
I = imread([inputfold,'\image_',num2str(nc-1),'.tif']); 
imwrite(I,[DICefold,'\reference.tif']); 
% Deformed image
I = imread([inputfold,'\image_',num2str(nc),'.tif']); 
imwrite(I,[DICefold,'\deformed.tif']); 

%% Run DICe
[status,outcmd] = system('"C:\Program Files (x86)\Digital Image Correlation Engine\dice.exe" -i input.xml -v -t');
if status == 1
    disp('ERRORE DIC ABORTED')
end

[v,u,X,Y] = DICe_results_reader_complete(nc,step_dic);


end


